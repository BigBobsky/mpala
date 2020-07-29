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

#ifndef KY040_MANAGER_HPP
#define KY040_MANAGER_HPP

#include <vector>


namespace mpala {

class ky040listener;

class ky040 {
    public:
        ky040(int pin1, int pin2);        

        int update();                
        int getPosition();
        
    private:

        int _pin1;
        int _pin2;
        volatile int _position;
        volatile int _lastEncoded;
};
    
class ky040manager {

    public:
  
        static ky040manager *getInstance();
        ky040 * addEncoder(int pin1, int pin2);
        
        // should not be public
        void    updateEncoders();
        void    setListener(ky040listener * listener);
        
    private:
        ky040manager();
        
        static ky040manager * _instance;
        
        std::list<ky040*> _encoders;
        
        ky040listener * _listener;
};

}

#endif