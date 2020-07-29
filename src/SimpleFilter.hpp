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

#ifndef SIMPLEFILTER_HPP
#define SIMPLEFILTER_HPP


#include <list>
#include <vector>

namespace mpala {

class SimpleFilter {
  
public:
  
    SimpleFilter(int dataSize, double timeWindowMS);
   
    std::vector<double> newMeasure(std::vector<double> m, double dt);
    
private:
    
    double _timeWindowMS;
    double _currentMeasureWindow;
    int _dataSize;
    

    std::list< double > _measureTimes;
    std::list< std::vector< double > > _measures;
    
};

};

#endif