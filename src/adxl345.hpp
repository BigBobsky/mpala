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

#include <memory>
#include <vector>

#include "I2Cbus.hpp"
#include "I2Cdevice.hpp"

#ifndef ADXL345_HPP
#define ADXL345_HPP

namespace mpala {

class adxl345 : public I2CDevice {

public:
  adxl345(I2Cbus *, unsigned int scale);
    
  virtual void init();
  virtual void updateRawDatas();
  
  void calibrate();
  
  double getPitch();
  double getRoll();
 
  std::vector<double> getVector();
  
private:
  i2c_byte _hx;
  i2c_byte _lx;
  i2c_byte _hy;
  i2c_byte _ly;
  i2c_byte _hz;
  i2c_byte _lz;
  
  unsigned int _scale;
  
  double _x;
  double _y;
  double _z;

  i2c_word_16 _x_offset;
  i2c_word_16 _y_offset;
  i2c_word_16 _z_offset;
  
  bool _calibrated;
  
  static const std::vector<float> SCALE_ARRAY;

  
  double distance(double x, double y);
  double Xrotation(double x, double y, double z);
  double Yrotation(double x, double y, double z);
  
};

};

#endif