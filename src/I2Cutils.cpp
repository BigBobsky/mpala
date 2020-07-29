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

#include <iostream>

#include "I2Cutils.hpp"

namespace mpala {

i2c_uword_16 I2Cutils::twos_complement(i2c_byte high, i2c_byte low)
{
      
    i2c_uword_16 ret = high;        
    ret = (ret << 8) + low;
    
    if (ret >= 0x8000) {   
        ret = -((0xffff - ret) + 1);
    }

    return ret;
}



i2c_word_16 I2Cutils::signed_complement(i2c_byte high, i2c_byte low)
{
    i2c_word_16 ret;
      
    uint16_t s = unsigned_word(high, low);
    
    if (s >= 0x8000) {
      
//      std::cout << "signed : " << s << std::endl;
//      std::cout << "signed min : " << 0xffff << std::endl;
      ret = -((0xffff - s) + 1);
    
           
//      std::cout << "signed ret : " << ret << std::endl;

    } else {
//      std::cout << "usigned : " << s << std::endl;
      ret = s;
    }

    return ret;
}

i2c_uword_16 I2Cutils::unsigned_word(i2c_byte high, i2c_byte low)
{
      
    i2c_uword_16 ret = high << 8;
        
    ret = ret + low;

    return ret;
}

}
