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

#include <gtkmm/box.h>
#include <gtkmm/button.h>

#include "ky-040-manager.hpp"


#ifndef SETTINGSPAGE_HPP
#define SETTINGSPAGE_HPP

namespace mpala {

class SettingsPage : public Gtk::Box {
  
public:
  
    SettingsPage();
    
    void setTracker(class StarTracker *);
  
    virtual ~SettingsPage();
  
    void setAxeEncoders(ky040 * dec, ky040 * ra);
    
    
private:

    Gtk::VBox _box;
    
    
    Gtk::HBox _boxAxe1;
    Gtk::Button _setAxe1MinButton;
    Gtk::Button _setAxe1MaxButton;
    Gtk::HBox _boxAxe2;
    Gtk::Button _setAxe2MinButton;
    Gtk::Button _setAxe2MaxButton;

    Gtk::Button _startButton;    
    Gtk::Button _testButton;    
    Gtk::Button _saveButton;
    Gtk::Button _exitButton;    
    
    int _decMin;
    int _decMax;
    int _raMin;
    int _raMax;
    
    ky040 * _ra_axe;
    ky040 * _dec_axe;
    
    class StarTracker * _tracker;
    
    void onTestButton();
    void onExitButton();

    void onDecMinSet();
    void onDecMaxSet();
    void onRAMinSet();
    void onRAMaxSet();

    void onSaveButton();

};

};

#endif