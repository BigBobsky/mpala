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
#include <gtkmm/button.h>

#include "starEntryListener.hpp"

#ifndef SINGLEENTRY_HPP
#define SINGLEENTRY_HPP

namespace mpala {

class SingleEntry : public Gtk::Box {
  
public:
  
    SingleEntry();
    
    void setListener(StarEntryListener * listener);
  
    void onEntryValidated();

    virtual ~SingleEntry();
  
    
private:

    Gtk::VBox box;
    
    Gtk::Frame frameAD;
    Gtk::HBox boxAD;
    
    Gtk::Frame frameDEC;
    Gtk::HBox boxDEC;
    

    Gtk::SpinButton adHours;
    Gtk::SpinButton adMinutes;
    Gtk::SpinButton adSeconds;

    Gtk::SpinButton decDegrees;
    Gtk::SpinButton decMinutes;
    Gtk::SpinButton decSeconds;
    
    
    Gtk::Label adLabel;
    Gtk::Label decLabel;
    
    Gtk::Button setButton;

    StarEntryListener * _listener;
    
};

};

#endif