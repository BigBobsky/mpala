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

#ifndef I2CUTILS_HPP
#define I2CUTILS_HPP

typedef unsigned char i2c_byte;
typedef uint16_t i2c_uword_16;
typedef int16_t i2c_word_16;

namespace mpala {

class I2Cutils {
  public:
        
    static i2c_uword_16 twos_complement(i2c_byte high, i2c_byte low);
    static i2c_word_16 signed_complement(i2c_byte high, i2c_byte low);
    static i2c_uword_16 unsigned_word(i2c_byte high, i2c_byte low);

};

};
#endif