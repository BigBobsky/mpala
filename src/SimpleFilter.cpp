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
#include <vector>
#include <list>
#include "SimpleFilter.hpp"

namespace mpala {

    SimpleFilter::SimpleFilter(int dataSize, double timeWindowMS) :
    _timeWindowMS(timeWindowMS),
    _currentMeasureWindow(0.0),
    _dataSize(dataSize),
    _measureTimes(0),
    _measures(0) {

    }

    std::vector<double> SimpleFilter::newMeasure(std::vector<double> m, double dt) {

        std::vector<double> ret(_dataSize);

        if (m.size() == _dataSize) {
            this->_measures.push_back(m);
            this->_measureTimes.push_back(dt);
            this->_currentMeasureWindow += dt;
        } else {
            std::cout << "invalide data" << std::endl;
        }

        std::list< std::vector<double> >::iterator it;
        std::list<double>::iterator it_time;

        if (this->_currentMeasureWindow > this->_timeWindowMS) {

            it_time = this->_measureTimes.begin();
            it = this->_measures.begin();
            double t = 0.0;

            while (it != this->_measures.end()) {
                if (this->_currentMeasureWindow > this->_timeWindowMS) {
                    this->_currentMeasureWindow -= *it_time;
                    it = this->_measures.erase(it);
                    it_time = this->_measureTimes.erase(it_time);
                } else {
                    for (int i = 0; i < _dataSize; i++) {
                        ret[i] += (*it)[i];
                    }
                }

                it++;
                it_time++;

            }

        }

        ret [0] = ret[0] / this->_measures.size();
        ret [1] = ret[1] / this->_measures.size();
        ret [2] = ret[2] / this->_measures.size();


        return ret;

    }


}
