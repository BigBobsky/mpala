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
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <iostream>
#include <memory>

#include "src/mpalaApp.hpp"
#include "src/mainView.hpp"
#include <wiringPi/wiringPi.h>

using namespace mpala;

int main(int argc, char **argv) {

    mpalaApp * app = mpalaApp::getInstance();
    
    app->run(argc,argv);
    
    while (true) {
        ::usleep(1000);
    }
    

#ifdef USE_IMU
    std::shared_ptr<I2Cbus> bus(new I2Cbus(1));

    GY80 * gy = new GY80(bus.get());

    gy->init();
    gy->calibrate();

    std::string input;
    std::cout << "enter current HH:mm,DD:mm" << std::endl;

    std::getline(std::cin, input);

    SimpleFilter * filter = new SimpleFilter(3, 3000.0);
    while (true) {

        gy->update();


        //        std::vector<double> amangles = gy->getAccMagAngles();
        std::vector<double> amangles = gy->getCompensatedAngles();

        std::vector<double> filteredAngles = filter->newMeasure(amangles, 100.0);

        std::cout << "######### filteredAngles yaw : " << 180.0 * filteredAngles[0] / MathUtils::PI
                << "# pitch : " << 180.0 * filteredAngles[1] / MathUtils::PI
                << "# roll : " << 180.0 * filteredAngles[2] / MathUtils::PI
                << std::endl;


        ::usleep(100000);
    }
#endif


    return 0;
}

