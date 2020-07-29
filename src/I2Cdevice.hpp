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

#include "I2Cutils.hpp"
#include "I2Cbus.hpp"

#ifndef I2CDEVICE_HPP
#define I2CDEVICE_HPP

namespace mpala {

class I2CDevice {
  
public:
  I2CDevice(I2Cbus *, int  i2caddress);
  
  virtual void init() = 0;
  virtual void updateRawDatas() = 0;
  
  void open();
  
  void writeByte(i2c_byte);
  void writeByteReg8(int reg, i2c_byte);
  
  i2c_byte readByte();
  i2c_byte readByteReg8(int reg);
  i2c_uword_16 readWordReg16(int reg);

  void writeData(int n, i2c_byte *);
  
  int readData(int n, i2c_byte *);
  
  void close();
    
protected:
  int mI2Caddress;
  
  std::shared_ptr<I2Cbus> mBus;
  
  int mCurrentDescriptor;
};

};

#endif