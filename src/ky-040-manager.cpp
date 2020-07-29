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
    Creation date : 05/11/14
 */

#include <iostream>
#include <vector>

#include <wiringPi/wiringPi.h>
#include <list>

#include "ky-040-manager.hpp"
#include "ky-040-listener.hpp"

namespace mpala {

    // encoder global manager : 16 encoders max
    static const int MAX_KY040_NUMBER = 16;

    static const int KY040_UPDATE_LOCK = 123;

    ky040manager * ky040manager::_instance = 0;

    void onKY040interuption() {

        ky040manager::getInstance()->updateEncoders();

    }

    ky040manager * ky040manager::getInstance() {
        if (_instance == 0) {
            _instance = new ky040manager();
        }

        return _instance;
    }

    ky040manager::ky040manager() : _encoders() {

    }

    void ky040manager::updateEncoders() {

        piLock(KY040_UPDATE_LOCK);

        std::list<ky040*>::iterator it = _encoders.begin();

        int cpt = 0;
        while (it != _encoders.end()) {
            (*it)->update();

            cpt++;

            //std::cout << "##### position for encoder " << cpt << " : " << (*it)->getPosition() << std::endl;
            
            if (this->_listener != 0) {
                this->_listener->onEncoderUpdate((*it), (*it)->getPosition());
            }

            it++;
        }

        piUnlock(KY040_UPDATE_LOCK);
        

    }

    ky040* ky040manager::addEncoder(int pin1, int pin2) {
        ky040 * ret = 0;

        std::cout << "adding encoder on pins " << pin1 << " , " << pin2 << std::endl;
        
        if (_encoders.size() < MAX_KY040_NUMBER) {
            ret = new ky040(pin1, pin2);
            _encoders.push_back(ret);
        }

        return ret;
    }

    ky040::ky040(int pin1, int pin2) :
    _pin1(pin1),
    _pin2(pin2),
    _position(0) {


        pinMode(_pin1, INPUT);
        pinMode(_pin2, INPUT);

        pullUpDnControl(_pin1, PUD_UP);
        pullUpDnControl(_pin2, PUD_UP);

        wiringPiISR(_pin1, INT_EDGE_BOTH, &onKY040interuption);
        wiringPiISR(_pin2, INT_EDGE_BOTH, &onKY040interuption);
        //std::cout << "init encoder : " << _pin1 << " , " << _pin2 << std::endl;

    }

    int ky040::update() {
        int MSB = digitalRead(_pin1);
        int LSB = digitalRead(_pin2);

        int encoded = (MSB << 1) | LSB;
        int sum = (_lastEncoded << 2) | encoded;

        if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) _position++;
        if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) _position--;

        _lastEncoded = encoded;
        //        std::cout << "######### value for  : " << _position << std::endl;
    }

    void ky040manager::setListener(ky040listener * listener) {
        _listener = listener;
    }

    int ky040::getPosition() {
        return _position;
    }

}
