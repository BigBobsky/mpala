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
 
    CTRL_REG1 = 0x20
    CTRL_REG2 = 0x21
    CTRL_REG3 = 0x22
    CTRL_REG4 = 0x23
    CTRL_REG5 = 0x24

    GYRO_START_BLOCK = 0x28
    GYRO_XOUT_H = 0x28
    GYRO_XOUT_L = 0x29
    GYRO_YOUT_H = 0x2a
    GYRO_YOUT_L = 0x2b
    GYRO_ZOUT_H = 0x2c
    GYRO_ZOUT_L = 0x2d

    FS_250 = 250
    FS_500 = 500
    FS_2000 = 2000

    FS_250_SCALE = 8.75 / 1000  # milli degrees per second page 10 of the datasheet
    FS_500_SCALE = 17.50 / 1000  # milli degrees per second page 10 of the datasheet
    FS_2000_SCALE = 70.00 / 1000  # milli degrees per second page 10 of the datasheet


    GYRO_SCALE = { FS_250 : [FS_250_SCALE, 0], FS_500 : [FS_500_SCALE, 1], FS_2000 : [FS_2000_SCALE, 10] }
 */

#include <iostream>
#include <cmath>
#include <unistd.h>

#include "l3g4200d.hpp"
#include "MathUtils.hpp"


namespace mpala {
  
const std::vector<float> l3g4200d::SCALE_ARRAY = { 8.75, 17.5, 70.0 }; // en milliemes
      
const std::vector<i2c_byte> l3g4200d::SCALE_MAPPING = { 0, 1, 10 };
    
l3g4200d::l3g4200d(I2Cbus *mBus, unsigned int scale) : I2CDevice(mBus, 0x69), _scale(scale), _calibrated(false) {

 
}

void l3g4200d::init()
{
  
  /*
   CTRL_REG1 = 0x20
    CTRL_REG2 = 0x21
    CTRL_REG3 = 0x22
    CTRL_REG4 = 0x23
    CTRL_REG5 = 0x24

   */
  unsigned int scale = _scale;
  
  _x_offset = 0;
  _y_offset = 0;
  _z_offset = 0;

  
  i2c_byte conf_reg1 = 0b00001111; // wake up et 3 axes
  i2c_byte conf_reg4 = (0 << 6) || (l3g4200d::SCALE_MAPPING[_scale] << 4)  ; // big endian et scale
      
  this->open();
  
//  std::cout << "setting resister 1 to " << conf_reg1 << std::endl;
//  std::cout << "setting resister 2 to " << conf_reg4 << std::endl;
  this->writeByteReg8(0x20, conf_reg1);
  this->writeByteReg8(0x23, conf_reg4);
}

void l3g4200d::updateRawDatas()
{
  this->_lx = this->readByteReg8(0x28);
  this->_hx = this->readByteReg8(0x29);
  this->_ly = this->readByteReg8(0x2a);
  this->_hy = this->readByteReg8(0x2b);
  this->_lz = this->readByteReg8(0x2c);
  this->_hz = this->readByteReg8(0x2d);


  this->_x = (MathUtils::PI / 180) * (I2Cutils::signed_complement(this->_hx, this->_lx) - this->_x_offset) * l3g4200d::SCALE_ARRAY[_scale] / 1000;
  this->_y = (MathUtils::PI / 180) * (I2Cutils::signed_complement(this->_hy, this->_ly) - this->_y_offset) * l3g4200d::SCALE_ARRAY[_scale] / 1000;
  this->_z = (MathUtils::PI / 180) * (I2Cutils::signed_complement(this->_hz, this->_lz) - this->_z_offset) * l3g4200d::SCALE_ARRAY[_scale] / 1000;
/*  
  this->_x = (I2Cutils::signed_complement(this->_hx, this->_lx) - this->_x_offset );
  this->_y = (I2Cutils::signed_complement(this->_hy, this->_ly) - this->_y_offset);
  this->_z = (I2Cutils::signed_complement(this->_hz, this->_lz) - this->_z_offset );
*/  
//  std::cout << "update gyro : " << _x << " , " << _y << " , " << _z << std::endl;
//  std::cout << "offset gyro : " << this->_x_offset << " , " << this->_y_offset << " , " << this->_z_offset << std::endl;
}

void l3g4200d::calibrate()
{

  double _x_min = 0;
  double _y_min = 0;
  double _z_min = 0;

  double _x_max = 0;
  double _y_max = 0;
  double _z_max = 0;
  
  _x_offset = 0;
  _y_offset = 0;
  _z_offset = 0;
  
  _calibrated = false;
  
  int i;  
  
  for (i = 0; i < 500; i++) {
    
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

std::vector< double > l3g4200d::getVector()
{
  std::vector<double> ret(3);
  
 
  
  ret[0] =  _x;
  ret[1] =  _y;
  ret[2] =  _z;
  
  return ret;
}



}