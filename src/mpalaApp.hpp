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

#ifndef MPALAAPP_HPP
#define	MPALAAPP_HPP

#include <gtkmm.h>

#include "mpalaConfig.hpp"

namespace mpala {

class mpalaApp {

    public:
        static mpalaApp * getInstance();
        
        void run(int argc, char **argv);
        
        void saveConfig();
        
        void exit();
    
    private:
    
        static mpalaApp * _instance;
        
        static const std::string _currentConfigFileName;
        static const std::string _loadedConfigFileName;
        
        mpalaConfig _currentConfig;
        
        mpalaApp();
        
        Glib::RefPtr<Gtk::Application> _app;
    
};

};


#endif	/* MPALAAPP_HPP */

