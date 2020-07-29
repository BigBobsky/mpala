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

#include "I2Cbus.hpp"
#include "hmc5883l.hpp"
#include "bmp085.hpp"
#include "l3g4200d.hpp"
#include "adxl345.hpp"

#ifndef GY80_HPP
#define GY80_HPP

namespace mpala {

class GY80 {
  
public:
  GY80(I2Cbus *);
  
  void init(); 
  
  void update();
  
  void calibrate();
  
  std::vector<double> getHybridQuaternion();
  std::vector<double> getHybridAngles();

  std::vector<double> getGyroQuaternion();
  std::vector<double> getGyroAngles();

  std::vector<double> getAccMagQuaternion();
  std::vector<double> getAccMagAngles();

  std::vector<double> getCompensatedAngles();
  
  virtual ~GY80();

private:  
  std::shared_ptr<hmc5883l> mCompass;
  std::shared_ptr<adxl345> mAccelerometer;
  std::shared_ptr<l3g4200d> mGyroscope;
  std::shared_ptr<bmp085> mBarometer;
  
  long int  _last_gyro_time;
  
  std::vector<double> mCurrentGyroQuaternion; 
  std::vector<double> mHybridQuaternion; 
  std::vector<double> mAccMagQuaternion; 
  std::vector<double> mStartQuaternion; 
  
  
  std::vector<double> acc_mag_quaternion();
  
};

};

#endif