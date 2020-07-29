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
#include <sstream>
#include <cmath>
#include <iomanip> 

#include "wiringPi/wiringPi.h"

#include "labels.hpp"

#include "livePage.hpp"

#include "gtkmm/box.h"
#include "gtkmm/label.h"
#include "gtkmm/frame.h"


namespace mpala {

    LivePage::LivePage() : Gtk::Box() {

        std::cout << "live page created" << std::endl;

        frameAD.set_label(LABEL_AD);
        frameDEC.set_label(LABEL_DEC);

        frameAD.set_border_width(2);
        frameDEC.set_border_width(2);

        
        Pango::FontDescription font;

        font.set_family("Monospace");
        font.set_size(Pango::SCALE * 30);
        font.set_weight(Pango::WEIGHT_BOLD);

        adFormatedLabel.override_font(font);
        decFormatedLabel.override_font(font);
  
        boxAD.pack_start(adFormatedLabel);
        boxDEC.pack_start(decFormatedLabel);
        
//        adHours.set_digits(0);
//        adHours.set_range(0, 23);
//        boxAD.pack_start(adHours);
//
//        adMinutes.set_digits(0);
//        adMinutes.set_range(0, 59);
//        boxAD.pack_start(adMinutes);
//
//        adSeconds.set_digits(0);
//        adSeconds.set_range(0, 59);
//        boxAD.pack_start(adSeconds);
//
//        decDegrees.set_digits(0);
//        decDegrees.set_range(-90, 90);
//        boxDEC.pack_start(decDegrees);
//
//        decMinutes.set_digits(0);
//        decMinutes.set_range(-59, 59);
//        boxDEC.pack_start(decMinutes);
//
//        decSeconds.set_digits(0);
//        decSeconds.set_range(-59, 59);
//        boxDEC.pack_start(decSeconds);

        frameAD.add(boxAD);
        frameDEC.add(boxDEC);

        box.pack_start(frameAD);
        box.pack_start(frameDEC);
        this->pack_end(box);

        _dispatcher.connect(sigc::mem_fun(*this, &LivePage::_updateAxePositions));

    }

    LivePage::~LivePage() {
        std::cout << "live page destroyed" << std::endl;
    }

    void LivePage::updateAxe1Position(double degrees) {

        _axe1position = degrees;

        _dispatcher.emit();

    }

    void LivePage::updateAxe2Position(double degrees) {

        _axe2position = degrees;

        _dispatcher.emit();

    }

//    void LivePage::updateTime() {
//        
//        _dispatcher.emit();
//    }
//    
    void LivePage::_updateAxePositions() {

        // DEC
        int d = (int) _axe1position;
        decDegrees.set_value(d);

        std::string decText;
        std::string adText;
        
        std::stringstream decStream;;
        std::stringstream adStream;;
        
        if ((_axe1position < 0) && (d == 0)) {
            decStream << "-";
        }
        decStream << d << "°";
        
        double md = (_axe1position - (double) d) * 60;
        int m = (int) md;
        if (::abs(m) <= 59) {
            if ((d == 0) && (_axe1position < 0)) {
                decMinutes.set_value(m);
            } else {
                decMinutes.set_value(::abs(m));
            }

            decStream << std::setfill('0') << std::setw(2) << ::abs(m);
        }
        
        
        decStream << "'";

        
        double sd = (md - (double) m) * 60;
        int s = (int) sd;
        if (::abs(s) <= 59) {
            if ((m == 0) && (d == 0) && (_axe1position < 0)) {
                decSeconds.set_value(s);
            } else {
                decSeconds.set_value(::abs(s));
            }
           decStream << std::setfill('0') << std::setw(2) << ::abs(s);
        }
        

        decStream << "\"";

        std::cout << "############ " << decStream.str();
        
        // R.A.

        double dH = _axe2position * 24.0 / 360.0;
        
        
        if (dH < 0.0) {
            dH = 24.0 + dH;
        }
        int H = (int) (dH);
//        std::cout << "dH = " << dH << " H = " << H << std::endl;

        adHours.set_value(H);
        adStream << H << "h";

        double dM = (dH - (double) H) * 60;
        int M = (int) dM;
        if (M <= 59) {
            adMinutes.set_value(M);
            adStream << std::setfill('0') << std::setw(2) << M << "m";
        } else {
            adStream << std::setfill('0') << std::setw(2) << 0 << "m";            
        }

        double dS = (dM - (double) M) * 60;
        int S = (int) dS;
        if (S <= 59) {
            adSeconds.set_value(S);
            adStream << std::setfill('0') << std::setw(2) << S << "s";
        } else {            
            adStream << std::setfill('0') << std::setw(2) << 0 << "s";
        }

        
        decFormatedLabel.set_label(decStream.str());
        adFormatedLabel.set_label(adStream.str());
    }

}
