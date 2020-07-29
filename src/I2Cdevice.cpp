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

#include <fcntl.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

#include <wiringPi/wiringPiI2C.h>

#include <iostream>

#include "I2Cdevice.hpp"

namespace mpala {

#define USE_WIRINGPI
  
I2CDevice::I2CDevice(I2Cbus * bus, int i2caddress) : mBus(bus), mI2Caddress(i2caddress)
{

  
}

void I2CDevice::open()
{
#ifdef USE_WIRINGPI
  
  std::cout << "using wiring pi !" << std::endl;
  
  this->mCurrentDescriptor = ::wiringPiI2CSetup(this->mI2Caddress);
  
  if (this->mCurrentDescriptor < 0) {
    std::cout << "unable to access i2c device " << this->mI2Caddress << std::endl;
  }  
#else
  this->mCurrentDescriptor = this->mBus->getDescriptor();
  if (ioctl(this->mCurrentDescriptor, I2C_SLAVE, this->mI2Caddress) < 0) {
    std::cout << "unable to access i2c device " << this->mI2Caddress << std::endl;
  }
#endif

}


void I2CDevice::writeByte(i2c_byte buf)
{
#ifdef USE_WIRINGPI
  ::wiringPiI2CWrite(this->mCurrentDescriptor, buf);
#else
  this->writeData(1, &buf);
#endif
  
}

void I2CDevice::writeByteReg8(int reg, i2c_byte buf)
{
#ifdef USE_WIRINGPI
  ::wiringPiI2CWriteReg8(this->mCurrentDescriptor, reg, buf);
#else
  
#endif
  
}

void I2CDevice::writeData(int n, i2c_byte*buf)
{
  if (this->mCurrentDescriptor >= 0) {
    if ((::write(this->mCurrentDescriptor, buf, n)) != n) {
      std::cout << "error writing data to i2c device " << this->mI2Caddress << std::endl;       
    }
  } else {
    std::cout << "i2c device " << this->mI2Caddress << " closed" << std::endl;
  }
}

i2c_byte I2CDevice::readByte()
{
  i2c_byte ret;
  
  this->readData(1, &ret);
  
  return ret;
}

i2c_byte I2CDevice::readByteReg8(int reg)
{
  i2c_byte ret;
  
  if (this->mCurrentDescriptor >= 0) {
    ret = ::wiringPiI2CReadReg8(this->mCurrentDescriptor, reg);
  }
  
  return ret;
}

i2c_uword_16 I2CDevice::readWordReg16(int reg) {
  i2c_uword_16 ret;
  
  if (this->mCurrentDescriptor >= 0) {
    ret = ::wiringPiI2CReadReg16(this->mCurrentDescriptor, reg);
  }
  
  return ret;
}

int I2CDevice::readData(int n, i2c_byte * buf)
{
    if (this->mCurrentDescriptor >= 0) {

      if (read(this->mCurrentDescriptor, buf, n) != n) {
	std::cout << "error reading data from i2c device " << this->mI2Caddress << std::endl;       
      } else {
	/*
	unsigned char highByte = buf[2];
	unsigned char lowByte = buf[3];
	unsigned int result = (highByte <<8) + lowByte;			// Calculate bearing as a word value
	printf("Software v: %u \n",buf[0]);
	printf("Bearing as byte: %u \n",buf[1]);
	printf("Bearing as decimal: %u.%u\n",result/10, result%10); // display bearing with decimal place
	*/
      }
  } else {
      std::cout << "i2c device " << this->mI2Caddress << " closed" << std::endl;
  }

}

void I2CDevice::close()
{
  ::close(this->mCurrentDescriptor);
  this->mCurrentDescriptor = -1;
}

}
