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
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>

#include "gy80.hpp"
#include "MathUtils.hpp"

extern "C" {
#include "MadgwickAHRS.h"    
//#include "MahonyAHRS.h"
}


namespace mpala {

GY80::GY80(I2Cbus *bus)
{
   
    std::cout << "initialize gy80 on bus " << bus->getId() << std::endl;
    this->mCompass = std::shared_ptr<hmc5883l>(new hmc5883l(bus, 1));
    this->mAccelerometer = std::shared_ptr<adxl345>(new adxl345(bus, 0));
    this->mGyroscope = std::shared_ptr<l3g4200d>(new l3g4200d(bus, 0));
    this->mBarometer = std::shared_ptr<bmp085>(new bmp085(bus, 1));

    this->_last_gyro_time = 0;
    
}

void GY80::init()
{

  this->mCompass->init();
  this->mAccelerometer->init();
  this->mGyroscope->init();
  this->mBarometer->init();

  // wait 200 ms before reading first values
  ::usleep(200);
  this->mCompass->updateRawDatas();
  this->mAccelerometer->updateRawDatas();
  this->mGyroscope->updateRawDatas();
  this->mBarometer->updateRawDatas();

  this->mStartQuaternion = this->acc_mag_quaternion();
  this->mAccMagQuaternion = this->mStartQuaternion;
  this->mHybridQuaternion = this->mStartQuaternion;
  this->mCurrentGyroQuaternion = this->mStartQuaternion;
  
//  
//  std::cout << "start quaternion w : " << this->mStartQuaternion[0] << std::endl;
//  std::cout << "start quaternion x : " << this->mStartQuaternion[1] << std::endl;
//  std::cout << "start quaternion y : " << this->mStartQuaternion[2] << std::endl;
//  std::cout << "start quaternion z : " << this->mStartQuaternion[3] << std::endl;
}

void GY80::calibrate()
{
    // TODO : add other calibration
    std::cout << "starting calibration" << std::endl;
    //this->mCompass->calibrate();
    //this->mAccelerometer->calibrate();
    //this->mGyroscope->calibrate();
    //this->mBarometer->calibrate();
    std::cout << "ending calibration" << std::endl;

}

void GY80::update()
{
  this->mCompass->updateRawDatas();
  this->mAccelerometer->updateRawDatas();
  this->mGyroscope->updateRawDatas();
  this->mBarometer->updateRawDatas();

  std::vector<double> v_gyro = this->mGyroscope->getVector();
  std::vector<double> v_mag = this->mCompass->getVector();
  std::vector<double> v_acc = this->mAccelerometer->getVector();
  
  
  double gx = v_gyro[0];
  double gy = v_gyro[1]; 
  double gz = v_gyro[2]; 
  double ax = v_acc[0];
  double ay = v_acc[1];
  double az = v_acc[2];
  double mx = v_mag[0];
  double my = v_mag[1];
  double mz = v_mag[2];

  /*
  std::cout << "madg gyr input : " << gx << " , " << gy << " , " << gz << std::endl;
  std::cout << "madg acc input : " << ax << " , " << ay << " , " << az << std::endl;
  std::cout << "madg mag input : " << mx << " , " << my << " , " << mz << std::endl;
*/
  
  std::vector<double> v_rotation = MathUtils::vector_normalize(v_gyro);
  double rot_mag = MathUtils::vector_norme(v_gyro);

  struct timeval tp;
  ::gettimeofday(&tp, NULL);
  long int t = tp.tv_sec * 1000 + tp.tv_usec / 1000;

  long int delta_t = t - this->_last_gyro_time;

  float dt_sec = delta_t / 1000.0f;
  
  
  //::MadgwickAHRSupdate(gx,gy,gz,ax,ay,az,mx,my,mz, 0.01f, 1, dt_sec);
  //::MahonyAHRSupdate(gx,gy,gz,ax,ay,az,mx,my,mz);
  
  //std::cout << "madg filtered output : " << dt_sec << " , " << q0 << " , " << q1 << " , " << q2 << " , " << q3 << std::endl;

  this->_last_gyro_time = t;

//  std::cout << "dtime = " << delta_t << std::endl;

  if (delta_t < 20) {
    return;
  }

//  std::cout << "time = " << t << std::endl;

  std::vector<double> q_rotation = MathUtils::quaternion_from_axis_angle(v_rotation, rot_mag * delta_t / 1000); // par sec => /1000

  this->mCurrentGyroQuaternion = MathUtils::quaternion_multiply(this->mCurrentGyroQuaternion, q_rotation);
  this->mHybridQuaternion = MathUtils::quaternion_multiply(this->mHybridQuaternion, q_rotation);
  
  /*
      std::cout << "rotation quat # w : " << q_rotation[0]
              << " # x : " << q_rotation[1]
              << " # y : " << q_rotation[2]
              << " # z : " << q_rotation[3]
              << std::endl;

            std::cout << "gyro quat # w : " << this->mCurrentGyroQuaternion[0]
              << " # x : " << this->mCurrentGyroQuaternion[1]
              << " # y : " << this->mCurrentGyroQuaternion[2]
              << " # z : " << this->mCurrentGyroQuaternion[3]
              << std::endl;

    */
  this->mAccMagQuaternion = this->acc_mag_quaternion();

  
  
  if ((MathUtils::vector_norme(v_acc) - 1.0) < 0.3) {
      
    std::vector<double> v_down = v_acc;
    v_down[0] = - v_down[0];
    v_down[1] = - v_down[1];
    v_down[2] = - v_down[2];

    std::vector<double> v_east = MathUtils::vector_cross(v_down, v_mag);
    std::vector<double> v_north = MathUtils::vector_cross(v_east, v_down);

    v_down = MathUtils::vector_normalize(v_down);
    v_east = MathUtils::vector_normalize(v_east);
    v_north = MathUtils::vector_normalize(v_north);
    
    std::vector<double> q_mag_acc = MathUtils::quaternion_from_rotation_matrix_rows(v_north, v_east, v_down);
    
    this->mHybridQuaternion[0] = 0.02*q_mag_acc[0] + 0.98*this->mHybridQuaternion[0];
    this->mHybridQuaternion[1] = 0.02*q_mag_acc[1] + 0.98*this->mHybridQuaternion[1];
    this->mHybridQuaternion[2] = 0.02*q_mag_acc[2] + 0.98*this->mHybridQuaternion[2];
    this->mHybridQuaternion[3] = 0.02*q_mag_acc[3] + 0.98*this->mHybridQuaternion[3];
    
    
    
  }

/*
  std::cout << "normalized rotation = " << v_rotation[0] << std::endl;
  std::cout << "normalized rotation = " << v_rotation[1] << std::endl;
  std::cout << "normalized rotation = " << v_rotation[2] << std::endl;

  std::cout << "q rotation w = " << q_rotation[0] << std::endl;
  std::cout << "q rotation x = " << q_rotation[1] << std::endl;
  std::cout << "q rotation y = " << q_rotation[2] << std::endl;
  std::cout << "q rotation z = " << q_rotation[3] << std::endl;

  std::cout << " gyro  qw = " << this->mCurrentGyroQuaternion[0] << std::endl;
  std::cout << " gyro  qx = " << this->mCurrentGyroQuaternion[1] << std::endl;
  std::cout << " gyro  qy = " << this->mCurrentGyroQuaternion[2] << std::endl;
  std::cout << " gyro  qz = " << this->mCurrentGyroQuaternion[3] << std::endl;

  std::cout << "hybride  w = " << this->mHybridQuaternion[0] << std::endl;
  std::cout << "hybride  x = " << this->mHybridQuaternion[1] << std::endl;
  std::cout << "hybride  y = " << this->mHybridQuaternion[2] << std::endl;
  std::cout << "hybride  z = " << this  ->mHybridQuaternion[3] << std::endl;
*/

}

std::vector< double > GY80::acc_mag_quaternion()
{
  std::vector<double> ret;

  std::vector<double> v_down = this->mAccelerometer->getVector();
  std::vector<double> v_up(3);
  v_up[0] = - v_down[0];
  v_up[1] = - v_down[1];  
  v_up[2] = - v_down[2];
  
  v_up = MathUtils::vector_normalize(v_up);

  std::vector<double> v_mag = this->mCompass->getVector();

//  v_mag = MathUtils::vector_normalize(v_mag);

  std::vector<double> v_east = MathUtils::vector_cross(v_up, v_mag);
  std::vector<double> v_north = MathUtils::vector_cross(v_east, v_up);

  // v_east = MathUtils::vector_normalize(v_east);
 // v_north = MathUtils::vector_normalize(v_north);

  
  std::cout << "v_up x = " << v_up[0] << std::endl;
  std::cout << "v_up y = " << v_up[1] << std::endl;
  std::cout << "v_up z = " << v_up[2] << std::endl;
  
  std::cout << "v_mag x = " << v_mag[0] << std::endl;
  std::cout << "v_mag y = " << v_mag[1] << std::endl;
  std::cout << "v_mag z = " << v_mag[2] << std::endl;

  /*
  std::cout << "v_east x = " << v_east[0] << std::endl;
  std::cout << "v_east y = " << v_east[1] << std::endl;
  std::cout << "v_east z = " << v_east[2] << std::endl;

  std::cout << "v_north x = " << v_north[0] << std::endl;
  std::cout << "v_north y = " << v_north[1] << std::endl;
  std::cout << "v_north z = " << v_north[2] << std::endl;
*/
  v_east = MathUtils::vector_normalize(v_east);
  v_north = MathUtils::vector_normalize(v_north);

  ret = MathUtils::quaternion_from_rotation_matrix_rows(v_north, v_east, v_up);
/*
  std::cout << "acc_mag_quaternion w = " << ret[0] << std::endl;
  std::cout << "acc_mag_quaternion x = " << ret[1] << std::endl;
  std::cout << "acc_mag_quaternion y = " << ret[2] << std::endl;
  std::cout << "acc_mag_quaternion z = " << ret[3] << std::endl;
*/
  return ret;
}


std::vector< double > GY80::getHybridQuaternion() {
    return this->mHybridQuaternion;
}

std::vector< double > GY80::getHybridAngles() {
    return MathUtils::quaternion_to_euler_angles(this->mHybridQuaternion);
}

std::vector<double> GY80::getAccMagQuaternion() {
    return this->mAccMagQuaternion;
}

std::vector<double> GY80::getAccMagAngles() {
    std::vector<double> ret(3);
    
    ret = MathUtils::quaternion_to_euler_angles(this->mAccMagQuaternion);
    
    return ret;
}

std::vector<double> GY80::getCompensatedAngles() {
    std::vector<double> ret(3);

    ret = this->getAccMagAngles();
    
    ret[0] = this->mCompass->getCompensatedBearing(ret[1], ret[2]);
    
    return ret;    
}

GY80::~GY80()
{
  // check scoped ptr
}

}
