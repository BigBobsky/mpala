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
    Creation date : 27/08/15
*/

#include <wiringPi/wiringPi.h>
    
#include "mainView.hpp"
#include "mpalaApp.hpp"

namespace mpala {
    
    mpalaApp * mpalaApp::_instance = 0;
    const std::string mpalaApp::_currentConfigFileName("mpala.cnf");
    const std::string mpalaApp::_loadedConfigFileName("loaded_mpala.cnf");
    
    mpalaApp * mpalaApp::getInstance() {
        if (mpalaApp::_instance == 0) {
            mpalaApp::_instance = new mpalaApp();
        }

        return mpalaApp::_instance;        
    }

    mpalaApp::mpalaApp()  {
        wiringPiSetup();
    }

    void mpalaApp::run(int argc, char **argv) {
        
        this->_app = Gtk::Application::create(argc, argv, "org.bobsky.mpala");                
        
        mpalaConfig * config = new mpalaConfig(mpalaApp::_currentConfigFileName);
        
        // config.save(mpalaApp::_loadedConfigFileName);
        
        MainView view(config);

        view.set_default_size(320, 240);
        
        this->_app->run(view);
        
    }


};

