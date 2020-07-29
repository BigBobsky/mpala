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

#ifndef L3G4200D_HPP
#define L3G4200D_HPP

namespace mpala {

class l3g4200d : public I2CDevice {

public:
  l3g4200d(I2Cbus *, unsigned int scale);
    
  virtual void init();
  
  void updateRawDatas();
  
  void calibrate();
  
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

  double _x_offset;
  double _y_offset;
  double _z_offset;
  
  bool _calibrated;
  
  static const std::vector<float> SCALE_ARRAY;
  static const std::vector<i2c_byte> SCALE_MAPPING;

  
};

};

#endif