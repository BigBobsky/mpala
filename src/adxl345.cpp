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
 
    POWER_CTL = 0x2d
    DATA_FORMAT = 0x31
    FIFO_CTL = 0x38

    AFS_2g = 0
    AFS_4g = 1
    AFS_8g = 2
    AFS_16g = 3

    ACCEL_START_BLOCK = 0x32
    ACCEL_XOUT_H = 1
    ACCEL_XOUT_L = 0
    ACCEL_YOUT_H = 3
    ACCEL_YOUT_L = 2
    ACCEL_ZOUT_H = 5
    ACCEL_ZOUT_L = 4

    ACCEL_SCALE = 0.004 # Always set to this as we are using FULL_RES
 */

#include <iostream>
#include <cmath>
#include <unistd.h>

#include "adxl345.hpp"

namespace mpala {
  
#define AFS_2g 0
#define AFS_4g 1
#define AFS_8g 2
#define AFS_16g 3
    
const std::vector<float> adxl345::SCALE_ARRAY = { 0.004 };

adxl345::adxl345(I2Cbus *mBus, unsigned int scale) : I2CDevice(mBus, 0x53), _scale(scale), _calibrated(false) {

 
}

void adxl345::init()
{
  
  _x_offset = 0;
  _y_offset = 0;
  _z_offset = 0;

  this->open();
  
  
//  std::cout << "power up and init accel" << std::endl;
  
  i2c_byte param = 0b00001000;
  this->writeByteReg8(0x2d, param); // power ctl
  
  param = 1 << 3 | _scale;  
  this->writeByteReg8(0x31, param); // data format
  
  param = 0b00000000;
  this->writeByteReg8(0x38, param); // disable fifo ctl
  
}

void adxl345::updateRawDatas()
{

    this->_lx = this->readByteReg8(0x32);
    this->_hx = this->readByteReg8(0x33);
    this->_ly = this->readByteReg8(0x34);
    this->_hy = this->readByteReg8(0x35);
    this->_lz = this->readByteReg8(0x36);
    this->_hz = this->readByteReg8(0x37);

//    std::cout << "accelerometre  raw x : " << (int)_lx << " , " << (int)_ly << std::endl;
//    std::cout << "accelerometre  raw x comp : " << I2Cutils::signed_complement(this->_hx, this->_lx) << std::endl;
    
    this->_x = (I2Cutils::signed_complement(this->_hx, this->_lx) - this->_x_offset) * SCALE_ARRAY[_scale];
    this->_y = (I2Cutils::signed_complement(this->_hy, this->_ly) - this->_y_offset) * SCALE_ARRAY[_scale];
    this->_z = (I2Cutils::signed_complement(this->_hz, this->_lz) - this->_z_offset) * SCALE_ARRAY[_scale];

//    std::cout << "accelerometre  : " << _x << " , " << _y << " , " << _z << std::endl;
}

void adxl345::calibrate()
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

//  std::cout << "calibration result : " << _x_offset << " , " << _y_offset << " , " << _z_offset << std::endl;
//  std::cout << "calibration result x : " << _x_min << " , " << _x_max << std::endl;
//  std::cout << "calibration result y : " << _y_min << " , " << _y_max << std::endl;
//  std::cout << "calibration result z : " << _z_min << " , " << _z_max << std::endl;
  
  _calibrated = true;
  
}

double adxl345::getPitch()
{
  double ret = this->Xrotation(_x,_y,_z);
  return ret;
}

double adxl345::getRoll()
{
  double ret = this->Yrotation(_x,_y,_z);
  return ret;
}


double adxl345::distance(double x, double y) {

  double ret = ::sqrt(x * x + y * y);
  
  return ret;
  
}

double adxl345::Xrotation(double x, double y, double z) {

  double ret = ::atan2(y, this->distance(x, z));
  
  return ret;
  
}

double adxl345::Yrotation(double x, double y, double z)  {

  double ret = - ::atan2(x, this->distance(y, z));
  
  return ret;
  
}

std::vector< double > adxl345::getVector()
{
  std::vector<double> ret(3);
  
  ret[0] =  _x;
  ret[1] =  _y;
  ret[2] =  _z;
  
  return ret;
}


}