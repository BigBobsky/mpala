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
#include <fstream>

#include "mpalaConfig.hpp"

namespace mpala {

    mpalaConfig::mpalaConfig() : 
                    axe1StepByDegree(1.0),
                    axe2StepByDegree(1.0),
                    axe1pinA(0),
                    axe1pinB(1),
                    axe2pinA(2),
                    axe2pinB(3)
    {
        

    }

    mpalaConfig::mpalaConfig(const std::string& fileName) : mpalaConfig() {

        this->_filename = fileName;
        std::ifstream is(fileName, std::ios::in);  
        
        if (is) {
            // TODO lecture
            
            is >> this->axe1pinA;
            is >> this->axe1pinB;
            is >> this->axe2pinA;
            is >> this->axe2pinB;
            is >> this->axe1StepByDegree;
            is >> this->axe2StepByDegree;
            
            is.close();
        } else {
            std::cerr << "error loading config file " << fileName << std::endl;
        }
        
    }
    
    void mpalaConfig::save() {
        this->save(this->_filename);
    }


    void mpalaConfig::save(const std::string& fileName) {

        this->_filename = fileName;
        std::ofstream os(fileName, std::ios::out | std::ios::trunc);
                
        if (os) {
            
            // TODO versionner le fichier
            // TODO JSON ou XML ?
            os << this->axe1pinA << std::endl;
            os << this->axe1pinB << std::endl;
            os << this->axe2pinA << std::endl;
            os << this->axe2pinB << std::endl;
            os << this->axe1StepByDegree << std::endl;
            os << this->axe2StepByDegree << std::endl;
            
            os.close();
        } else {
            std::cerr << "error saving config file " << fileName << std::endl;            
        }
        
    }


    mpalaConfig::~mpalaConfig() {
    }

}
