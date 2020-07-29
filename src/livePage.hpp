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

#include <memory>

#include <glibmm-2.4/glibmm.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/frame.h>
#include <gtkmm/spinbutton.h>

#ifndef LIVEPAGE_HPP
#define LIVEPAGE_HPP

namespace mpala {

class LivePage : public Gtk::Box {
  
public:
  
    LivePage();
  
    virtual ~LivePage();
  
    void updateAxe1Position(double degrees);
    
    void updateAxe2Position(double degrees);    
    
//    void updateTime();    

private:

    double _axe1position;
    double _axe2position;
    
    Gtk::VBox box;
    
    Gtk::Frame frameAD;
    Gtk::HBox boxAD;
    
    Gtk::Frame frameDEC;
    Gtk::HBox boxDEC;

    Gtk::Label adFormatedLabel;
    Gtk::Label decFormatedLabel;

    Gtk::SpinButton adHours;
    Gtk::SpinButton adMinutes;
    Gtk::SpinButton adSeconds;

    Gtk::SpinButton decDegrees;
    Gtk::SpinButton decMinutes;
    Gtk::SpinButton decSeconds;
    
    
    Gtk::Label adLabel;
    Gtk::Label decLabel;
    
    Glib::Dispatcher _dispatcher;
    
    void _updateAxePositions();
    
};

};

#endif