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
#include <iostream>
#include <gtkmm/button.h>

#include "labels.hpp"
#include "settingsPage.hpp"
#include "starTracker.hpp"


namespace mpala {

    SettingsPage::SettingsPage() : Gtk::Box(), _tracker(0) {
        
        std::cout << "SettingsPage created" << std::endl;

        _setAxe1MinButton.set_label(LABEL_SET_AXE1_MIN);
        _setAxe1MaxButton.set_label(LABEL_SET_AXE1_MAX);
        _setAxe2MinButton.set_label(LABEL_SET_AXE2_MIN);
        _setAxe2MaxButton.set_label(LABEL_SET_AXE2_MAX);
        
        _boxAxe1.pack_start(_setAxe1MinButton);
        _boxAxe1.pack_start(_setAxe1MaxButton);
        _boxAxe2.pack_start(_setAxe2MinButton);
        _boxAxe2.pack_start(_setAxe2MaxButton);
           
        _setAxe1MinButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onDecMinSet));
        _setAxe1MaxButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onDecMaxSet));
        _setAxe2MinButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onRAMinSet));
        _setAxe2MaxButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onRAMaxSet));

        _startButton.set_label(LABEL_START_CONF);
        _testButton.set_label(LABEL_TEST);
        _exitButton.set_label(LABEL_EXIT);
        _saveButton.set_label(LABEL_SAVE_CONF);

        _saveButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onSaveButton));

        
        _box.pack_start(this->_startButton);
        
        _box.pack_start(this->_boxAxe1);
        _box.pack_start(this->_boxAxe2);
        
//        _box.pack_start(this->_testButton);
        _box.pack_start(this->_saveButton);
        _box.pack_start(this->_exitButton);
        
        
//        _testButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onTestButton));
        _exitButton.signal_clicked().connect(sigc::mem_fun(*this, &SettingsPage::onExitButton));
        
        this->pack_end(this->_box);
        

    }
    
    void SettingsPage::setAxeEncoders(ky040* dec, ky040* ra) {
        this->_ra_axe = ra;
        this->_dec_axe = dec;
    }

    
    void SettingsPage::onDecMinSet() {
        this->_decMin = this->_dec_axe->getPosition();
        std::cout << "############## set dec min " << this->_decMin << std::endl;
    }
    
    void SettingsPage::onDecMaxSet() {
        this->_decMax = this->_dec_axe->getPosition();
        std::cout << "############## set dec max " << this->_decMax << std::endl;
    }

    void SettingsPage::onRAMinSet() {
        this->_raMin = this->_ra_axe->getPosition();
        std::cout << "############## set ra min " << this->_raMin << std::endl;
    }
    
    void SettingsPage::onRAMaxSet() {
        this->_raMax = this->_ra_axe->getPosition();
        std::cout << "############## set ra max " << this->_raMax << std::endl;
    }

    void SettingsPage::setTracker(StarTracker*tracker) {
        this->_tracker = tracker;
    }

    void SettingsPage::onSaveButton() {
        
        this->_tracker->config()->axe1StepByDegree = (_decMax - _decMin) / 180.0;
        this->_tracker->config()->axe2StepByDegree = (_raMax - _raMin) / 180.0;

        std::cout << "############## set degs 1 =  " << this->_tracker->config()->axe1StepByDegree << std::endl;
        std::cout << "############## set degs 2 =  " << this->_tracker->config()->axe2StepByDegree << std::endl;

        this->_tracker->config()->save();
        
    }

    void SettingsPage::onExitButton() {
        exit(0);
    }

    void SettingsPage::onTestButton() {
        
        if (this->_tracker != 0) {
            
            // axe 1 => DEC
            // axe 2 => RA
            this->_tracker->updateAxe1(0.0);
            this->_tracker->updateAxe2(0.0);
            
            this->_tracker->addStarWithCurrentTime(0.0, 45.0);

            this->_tracker->updateAxe1(0.0);
            this->_tracker->updateAxe2(45.0);
            
            this->_tracker->addStarWithCurrentTime(0.0, 90.0);
            
        }
        
    }
    
    SettingsPage::~SettingsPage() {
        std::cout << "SettingsPage destroyed" << std::endl;
    }

}
