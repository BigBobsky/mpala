/*
    This file is part of MPALA.

    MPALA is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MPALA is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MPALA.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
    Author : Jean-Luc TRESSET
    Contact : bigbobsky@gmail.com
    Creation date : 09/09/14
*/

/*
 * Used constants
 
    CONF_REG_A = 0
    CONF_REG_B = 1
    MODE_REG = 2
    DATA_START_BLOCK = 3
    DATA_XOUT_H = 0
    DATA_XOUT_L = 1
    DATA_ZOUT_H = 2
    DATA_ZOUT_L = 3
    DATA_YOUT_H = 4
    DATA_YOUT_L = 5

    SAMPLE_RATE = { 0 : 0.75, 1 : 1.5, 2 : 3, 3 : 7.5, 4 : 15, 5 : 30, 6 : 75, 7 :-1 }

    SAMPLE_MODE = { 0 : "CONTINUOUS", 1 : "SINGLE", 2 : "IDLE", 3 : "IDLE" }

    GAIN_SCALE = {
                    0 : [ 0.88, 1370, 0.73 ],
                    1 : [ 1.30, 1090, 0.92 ],
                    2 : [ 1.90, 820, 1.22 ],
                    3 : [ 2.50, 660, 1.52 ],
                    4 : [ 4.00, 440, 2.27 ],
                    5 : [ 4.70, 390, 2.56 ],
                    6 : [ 5.60, 330, 3.03 ],
                    7 : [ 8.10, 230, 4.35 ]


 */

#include <iostream>
#include <cmath>
#include <unistd.h>

#include "I2Cutils.hpp"
#include "MathUtils.hpp"
#include "hmc5883l.hpp"



namespace mpala {
  
const std::vector< std::vector<float> > hmc5883l::GAIN_ARRAY = {	

      { 0.88, 1370, 0.73 },
      { 1.30, 1090, 0.92 },
      { 1.90, 820, 1.22 },
      { 4.00, 440, 2.27 },
      { 4.70, 390, 2.56 },
      { 5.60, 330, 3.03 },
      { 8.10, 230, 4.35 }
      
    };
    
const std::vector<float> hmc5883l::RATE_ARRAY = { 0.75, 1.5, 3, 7.5, 15.0, 30.0, 75.0, -1.0 };

hmc5883l::hmc5883l(I2Cbus *mBus, unsigned int gain) : I2CDevice(mBus, 0x1e), _gain(gain), _calibrated(false) {

 
}

void hmc5883l::init()
{
  
  
  int sample = 3;
  int rate = 4;
  unsigned int gain = _gain;
  
  this->_x_offset = 0;
  this->_y_offset = 0;
  this->_z_offset = 0;
  
  i2c_byte conf_a = (sample << 5) + (rate << 2);
  i2c_byte conf_b = (gain << 5);
      
  this->open();
  
  std::cout << "setting A resister to " << conf_a << std::endl;
  std::cout << "setting B resister to " << conf_b << std::endl;
  this->writeByteReg8(0, conf_a);
  this->writeByteReg8(1, conf_b);
  this->writeByteReg8(2, 0x00); // sampling mode 0
  
  
  /*
  unsigned char buf[3];
  buf[0] = 0b01110000;
  buf[1] = 0b00100000;
  buf[2] = 0b00000000;
  
  */
  /*
   *
   *
   *
   *    CONF_REG_A = 0
    CONF_REG_B = 1
    MODE_REG = 2
    DATA_START_BLOCK = 3
    DATA_XOUT_H = 0
    DATA_XOUT_L = 1
    DATA_ZOUT_H = 2
    DATA_ZOUT_L = 3
    DATA_YOUT_H = 4
    DATA_YOUT_L = 5
    
    
        GAIN_SCALE = {
                    0 : [ 0.88, 1370, 0.73 ],
                    1 : [ 1.30, 1090, 0.92 ],
                    2 : [ 1.90, 820, 1.22 ],
                    3 : [ 2.50, 660, 1.52 ],
                    4 : [ 4.00, 440, 2.27 ],
                    5 : [ 4.70, 390, 2.56 ],
                    6 : [ 5.60, 330, 3.03 ],
                    7 : [ 8.10, 230, 4.35 ]
                 }



   *     SAMPLE_RATE = { 0 : 0.75, 1 : 1.5, 2 : 3, 3 : 7.5, 4 : 15, 5 : 30, 6 : 75, 7 :-1 }

    SAMPLE_MODE = { 0 : "CONTINUOUS", 1 : "SINGLE", 2 : "IDLE", 3 : "IDLE" }

          # Set the number of samples
        conf_a = (samples <<	 5) + (rate << 2)
        I2CUtils.i2c_write_byte(self.bus, self.address, HMC5883L.CONF_REG_A, conf_a)

        # Set the gain
        conf_b = gain << 5
        I2CUtils.i2c_write_byte(self.bus, self.address, HMC5883L.CONF_REG_B, conf_b)

        # Set the operation mode
        I2CUtils.i2c_write_byte(self.bus, self.address, HMC5883L.MODE_REG, self.sampling_mode)

        self.raw_data = [0, 0, 0, 0, 0, 0]

        # Now read all the values as the first read after a gain change returns the old value
        self.read_raw_data()

    def read_raw_data(self):
        '''
        Read the raw data from the sensor, scale it appropriately and store for later use
        '''
        self.raw_data = I2CUtils.i2c_read_block(self.bus, self.address, HMC5883L.DATA_START_BLOCK, 6)
        self.raw_x = I2CUtils.twos_compliment(self.raw_data[HMC5883L.DATA_XOUT_H], self.raw_data[HMC5883L.DATA_XOUT_L]) - self.x_offset
        self.raw_y = I2CUtils.twos_compliment(self.raw_data[HMC5883L.DATA_YOUT_H], self.raw_data[HMC5883L.DATA_YOUT_L]) - self.y_offset
        self.raw_z = I2CUtils.twos_compliment(self.raw_data[HMC5883L.DATA_ZOUT_H], self.raw_data[HMC5883L.DATA_ZOUT_L]) - self.z_offset

        self.scaled_x = self.raw_x * HMC5883L.GAIN_SCALE[self.gain][2]
        self.scaled_y = self.raw_y * HMC5883L.GAIN_SCALE[self.gain][2]
        self.scaled_z = self.raw_z * HMC5883L.GAIN_SCALE[self.gain][2]


  */
  /*
  this->writeData(3, buf);
  */
}

void hmc5883l::updateRawDatas()
{
  this->_hx = this->readByteReg8(3);
  this->_lx = this->readByteReg8(4);
  this->_hz = this->readByteReg8(5);
  this->_lz = this->readByteReg8(6);
  this->_hy = this->readByteReg8(7);
  this->_ly = this->readByteReg8(8);
  
  
  // 2 = bug ou pas ?
  

  this->_x = (I2Cutils::signed_complement(this->_hx, this->_lx) - this->_x_offset) * hmc5883l::GAIN_ARRAY[_gain][2];
  this->_y = (I2Cutils::signed_complement(this->_hy, this->_ly) - this->_y_offset) * hmc5883l::GAIN_ARRAY[_gain][2];
  this->_z = (I2Cutils::signed_complement(this->_hz, this->_lz) - this->_z_offset) * hmc5883l::GAIN_ARRAY[_gain][2];
}


double hmc5883l::getBearing()
{
  double ret;
  
  ret = ::atan2(_x, _y);
  
  if (ret < 0) {
    ret = ret + MathUtils::PI;
  }
  
  return ret;
}

double hmc5883l::getCompensatedBearing(double pitch, double roll)
{
  double ret;
  
  double cos_pitch = ::cos(pitch);
  double sin_pitch = ::sin(pitch);
  double cos_roll = ::cos(roll);
  double sin_roll = ::sin(roll);
  
  /*
   * Xh = XM * cos(Pitch) + ZM * sin(Pitch)
   * Yh = XM * sin(Roll) * sin(Pitch) + YM * cos(Roll) – ZM * sin(Roll) * cos(Pitch)
   */
  double Xh = (_x * cos_pitch) + (_z * sin_pitch);
  double Yh = (_x * sin_roll * sin_pitch) + (_y * cos_roll) - (_z * sin_roll * cos_pitch);

  std::cout << "########### Xh = " << Xh << " Yh = " << Yh << std::endl; 
  ret = ::atan2(Yh, Xh);

  return ret;
}

void hmc5883l::calibrate()
{

  unsigned int _x_min = 0;
  unsigned int _y_min = 0;
  unsigned int _z_min = 0;

  unsigned int _x_max = 0;
  unsigned int _y_max = 0;
  unsigned int _z_max = 0;
  
  _x_offset = 0;
  _y_offset = 0;
  _z_offset = 0;
  
  _calibrated = false;
  
  int i;  
  
  for (i = 0; i < 5000; i++) {
    
    this->updateRawDatas();
    
    (_x < _x_min) ? _x_min = _x : 0 == 0;
    (_y < _y_min) ? _y_min = _y : 0 == 0;
    (_z < _z_min) ? _z_min = _z : 0 == 0;
    
    (_x > _x_max) ? _x_max = _x : 0 == 0;
    (_y > _y_max) ? _y_max = _y : 0 == 0;
    (_z > _z_max) ? _z_max = _z : 0 == 0;
    
    usleep(100);
    
  }
  
  _x_offset = (_x_max - _x_min) / 2;
  _y_offset = (_y_max - _y_min) / 2;
  _z_offset = (_z_max - _z_min) / 2;

  std::cout << "calibration result : " << _x_offset << " , " << _y_offset << " , " << _z_offset << std::endl;
  std::cout << "calibration result x : " << _x_min << " , " << _x_max << std::endl;
  std::cout << "calibration result y : " << _y_min << " , " << _y_max << std::endl;
  std::cout << "calibration result z : " << _z_min << " , " << _z_max << std::endl;
  
  _calibrated = true;
  
}

std::vector< double > hmc5883l::getVector()
{
  std::vector<double> ret(3);
  
  ret[0] =  _x;
  ret[1] =  _y;
  ret[2] =  _z;
  
  return ret;
}


}