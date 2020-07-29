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

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>

#include <iostream>
#include <sstream>
#include <string>

#include "I2Cbus.hpp"

namespace mpala {

I2Cbus::I2Cbus(int busnumber) : mBusNumber(busnumber)
{
  std::cout << "I2C bus defined with number " << this->mBusNumber << std::endl;
}

int I2Cbus::getId()
{
  return mBusNumber;
}

int I2Cbus::getDescriptor()
{
  int ret = -1;
  
  std::ostringstream stringStream;
  stringStream << "/dev/i2c-" << mBusNumber;
  std::string filename = stringStream.str();

  ret = open(filename.c_str(), O_RDWR);
  
  return ret;
}

}