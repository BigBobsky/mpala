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
#include <gtkmm/label.h>
#include <gtkmm/window.h>
#include <bits/unique_ptr.h>

#include "gtkmm/notebook.h"

#include "mainView.hpp"
#include "starEntryListener.hpp"

namespace mpala {

    MainView::MainView(mpalaConfig * config) : Gtk::Window(), _config(config) {

        //        _mainContainer = std::unique_ptr<Gtk::Notebook>(new Gtk::Notebook());

        this->set_decorated(false);
        _mainContainer.set_show_tabs(true);

//        Gtk::Label * welcomeLabel = Gtk::manage(new Gtk::Label("Welcome"));
//        _mainContainer.append_page(_landingPage, *welcomeLabel);

        Gtk::Label * liveLabel = Gtk::manage(new Gtk::Label("Live"));
        _mainContainer.append_page(_livePage, *liveLabel);

        Gtk::Label * singleLabel = Gtk::manage(new Gtk::Label("Single"));
        _mainContainer.append_page(_singlePage, *singleLabel);

        Gtk::Label * firstLabel = Gtk::manage(new Gtk::Label("First"));
        _mainContainer.append_page(_entry1Page, *firstLabel);

        Gtk::Label * secondLabel = Gtk::manage(new Gtk::Label("Second"));
        _mainContainer.append_page(_entry2Page, *secondLabel);

        Gtk::Label * settingsLabel = Gtk::manage(new Gtk::Label("Settings"));
        _mainContainer.append_page(_settingsPage, *settingsLabel);

        _singlePage.setListener(this);

        _entry1Page.setListener(this);
        _entry2Page.setListener(this);
        
        
        _timerConnection = Glib::signal_timeout().connect(sigc::mem_fun(*this, &MainView::onTimerTick), 1000);
        
        _mainContainer.show_all();

        this->add(_mainContainer);


        this->_axe1 = ky040manager::getInstance()->addEncoder(config->axe1pinA, config->axe1pinB);
        this->_axe2 = ky040manager::getInstance()->addEncoder(config->axe2pinA, config->axe2pinB);

        ky040manager::getInstance()->setListener(this);

        this->_tracker = new StarTracker(_config);
        
        this->_settingsPage.setTracker(this->_tracker);
        this->_settingsPage.setAxeEncoders(this->_axe1, this->_axe2);
        
    }
    
    bool MainView::onTimerTick() {
        std::cout << "MainView::onTimerTick" << std::endl;
        std::vector<double> rpos = _tracker->getStarPositionFromCurrentLocalPosition();            
        _livePage.updateAxe1Position(rpos[0]);        
        _livePage.updateAxe2Position(rpos[1]);       
        
        return true;
    }


    void MainView::onSituationUpdate(std::vector<double>) {
    }

    void MainView::onMeasure(StarEntry* entry, double axe1, double axe2) {
        std::cout << "new measure for entry " << entry << std::endl;
        // mesures en degres
        this->_tracker->addStarWithCurrentTime(axe1, axe2);

    }
    
    void MainView::onMeasure(SingleEntry* entry, double axe1, double axe2) {
        std::cout << "new single entry " << entry << std::endl;
        // mesures en degres
        this->_tracker->addSingleStarWithCurrentTime(axe1, axe2);

    }

    void MainView::onEncoderUpdate(ky040* encoder, int position) {

        if (encoder == this->_axe1) {
            std::cout << "steps axe 1 = " << position << " / " << _config->axe1StepByDegree << std::endl;
            double pos = position * (1.0 / _config->axe1StepByDegree);
            std::cout << "pos axe 1 = " << pos << std::endl;
            // mesures en degres
            _tracker->updateAxe1(pos);            
        } else if (encoder == this->_axe2) {
            std::cout << "steps axe 2 = " << position << std::endl;
            double pos = position * (1.0 / _config->axe2StepByDegree);
            std::cout << "pos axe 2 = " << pos << std::endl;
            // mesures en degres
            _tracker->updateAxe2(pos);
        }
        
        std::vector<double> rpos = _tracker->getStarPositionFromCurrentLocalPosition();            
        _livePage.updateAxe1Position(rpos[0]);        
        _livePage.updateAxe2Position(rpos[1]);        
    }

    MainView::~MainView() {
        // check scoped ptr
    }

}
