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

/*
 * Used constants
 
    CALIB_BLOCK_ADDRESS = 0xAA
    CALIB_BLOCK_SIZE = 22


 */

#include <iostream>
#include <cmath>
#include <unistd.h>

#include "bmp085.hpp"


namespace mpala {
  

bmp085::bmp085(I2Cbus *mBus, unsigned int oss) : I2CDevice(mBus, 0x77), _oss(oss), _calibrated(false) {

 
}

void bmp085::init()
{
  
/*
 *         self.bus = bus
 *         self.address = address
 *         self.name = name
 *
 *         self.calibration = I2CUtils.i2c_read_block(bus, address, BMP085.CALIB_BLOCK_ADDRESS, BMP085.CALIB_BLOCK_SIZE)
 *         self.oss = oss
 *         self.temp_wait_period = 0.004
 *         self.pressure_wait_period = 0.0255  # Conversion time
 *
 * */  
  unsigned int oss = this->_oss;
  
  this->open();
/* 
  this->writeByteReg8(0, conf_a);
  this->writeByteReg8(1, conf_b);
  this->writeByteReg8(2, 0x00); // sampling mode 0
*/
  
}

void bmp085::updateRawDatas()
{
/* 
        # The sensor has a block of factory set calibration values we need to read
        # these are then used in a length calculation to get the temperature and pressure
        # copy these into convenience variables
        ac1 = self.get_word(self.calibration, 0, True)
        ac2 = self.get_word(self.calibration, 2, True)
        ac3 = self.get_word(self.calibration, 4, True)
        ac4 = self.get_word(self.calibration, 6, False)
        ac5 = self.get_word(self.calibration, 8, False)
        ac6 = self.get_word(self.calibration, 10, False)
        b1 = self.get_word(self.calibration, 12, True)
        b2 = self.get_word(self.calibration, 14, True)
        mb = self.get_word(self.calibration, 16, True)
        mc = self.get_word(self.calibration, 18, True)
        md = self.get_word(self.calibration, 20, True)
        oss = self.oss

        # This code is a direct translation from the datasheet
        # and should be optimised for real world use

        # Read raw temperature
        I2CUtils.i2c_write_byte(self.bus, self.address, 0xF4, 0x2E)  # Tell the sensor to take a temperature reading
        time.sleep(self.temp_wait_period)  # Wait for the conversion to take place
        temp_raw = I2CUtils.i2c_read_word_signed(self.bus, self.address, 0xF6)

        I2CUtils.i2c_write_byte(self.bus, self.address, 0xF4, 0x34 + (self.oss << 6))  # Tell the sensor to take a pressure reading
        time.sleep(self.pressure_wait_period)  # Wait for the conversion to take place
        pressure_raw = ((I2CUtils.i2c_read_byte(self.bus, self.address, 0xF6) << 16) \
                     + (I2CUtils.i2c_read_byte(self.bus, self.address, 0xF7) << 8) \
                     + (I2CUtils.i2c_read_byte(self.bus, self.address, 0xF8))) >> (8 - self.oss)


        # Calculate temperature
        x1 = ((temp_raw - ac6) * ac5) / 32768
        x2 = (mc * 2048) / (x1 + md)
        b5 = x1 + x2
        t = (b5 + 8) / 16

        # Now calculate the pressure
        b6 = b5 - 4000
        x1 = (b2 * (b6 * b6 >> 12)) >> 11
        x2 = ac2 * b6 >> 11
        x3 = x1 + x2
        b3 = (((ac1 * 4 + x3) << oss) + 2) >> 2

        x1 = (ac3 * b6) >> 13
        x2 = (b1 * (b6 * b6 >> 12)) >> 16
        x3 = ((x1 + x2) + 2) >> 2
        b4 = ac4 * (x3 + 32768) >> 15

        b7 = (pressure_raw - b3) * (50000 >> oss)
        if (b7 < 0x80000000):
            p = (b7 * 2) / b4
        else:
            p = (b7 / b4) * 2
        x1 = (p >> 8) * (p >> 8)
        x1 = (x1 * 3038) >> 16
        x2 = (-7357 * p) >> 16
        p = p + ((x1 + x2 + 3791) >> 4)
        return(t / 10., p / 100.)
*/ 
  //std::cout << "axes : " << _x << " , " << _y << " , " << _z << std::endl;
}


void bmp085::calibrate()
{

  _calibrated = true;
  
}


}
