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

#include "I2Cutils.hpp"

#ifndef I2CBUS_HPP
#define I2CBUS_HPP

namespace mpala {

class I2Cbus {
  
public:
  I2Cbus(int busnumber);
  
  int getDescriptor();
  int getId();
  
private:
  
  int mBusNumber;
  
};

};

#endif