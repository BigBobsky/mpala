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

#include "labels.hpp"

#include "singleEntry.hpp"

namespace mpala {

    SingleEntry::SingleEntry() :
            Gtk::Box(),
            _listener(0) {

        std::cout << "SingleEntry page created" << std::endl;

        frameAD.set_label(LABEL_AD);
        frameDEC.set_label(LABEL_DEC);

        frameAD.set_border_width(2);
        frameDEC.set_border_width(2);

        adHours.set_digits(0);
        adHours.set_increments(1.0, 3.0);
        adHours.set_range(0, 23);
        boxAD.pack_start(adHours);

        adMinutes.set_digits(0);
        adMinutes.set_increments(1.0, 10.0);
        adMinutes.set_range(0, 59);
        boxAD.pack_start(adMinutes);

        adSeconds.set_digits(0);
        adSeconds.set_increments(1.0, 10.0);
        adSeconds.set_range(0, 59);
        boxAD.pack_start(adSeconds);

        decDegrees.set_digits(0);
        decDegrees.set_increments(1.0, 10.0);        
        decDegrees.set_range(-90, 90);
        boxDEC.pack_start(decDegrees);

        decMinutes.set_digits(0);
        decMinutes.set_increments(1.0, 10.0);        
        decMinutes.set_range(-59, 59);
        boxDEC.pack_start(decMinutes);

        decSeconds.set_digits(0);
        decSeconds.set_increments(1.0, 10.0);        
        decSeconds.set_range(-59, 59);
        boxDEC.pack_start(decSeconds);

        frameAD.add(boxAD);
        frameDEC.add(boxDEC);

        box.pack_start(frameAD);
        box.pack_start(frameDEC);
 
        setButton.set_label(LABEL_VALIDATE);
        setButton.signal_clicked().connect(sigc::mem_fun(*this, &SingleEntry::onEntryValidated));
        
        
        box.pack_end(setButton);
        
        // set vega values
        decDegrees.set_value(38);
        decMinutes.set_value(47);
        decSeconds.set_value(1);
                
        adHours.set_value(18);
        adMinutes.set_value(36);
        adSeconds.set_value(56);
        
        this->pack_end(box);

    }

    void SingleEntry::setListener(StarEntryListener* listener) {
        this->_listener = listener;
    }


    void SingleEntry::onEntryValidated() {
        std::cout << "new single entry registered" << std::endl;
        if (_listener != 0) {
            int d;
            int m;
            int s;
            
            double ra;
            double dec;
            
            // dec to degrees
            d = (int)decDegrees.get_value();
            m = ::abs((int)decMinutes.get_value());
            s = ::abs((int)decSeconds.get_value());
            
            dec = (double)d + (double)m / 60.0 + (double)s / 3600.0;
            
            std::cout << "dec degrees = " << dec << std::endl;
            
            d = (int)(adHours.get_value() * 360.0 / 24.0);
            m = ::abs((int)(adMinutes.get_value() * 360.0 / 24.0));
            s = ::abs((int)(adSeconds.get_value() * 360.0 / 24.0));
            ra = (double)d + (double)m / 60.0 + (double)s / 3600.0;
            _listener->onMeasure(this, ra, dec);                           
            std::cout << "ra degrees = " << ra << std::endl;
        }
    }
    
    SingleEntry::~SingleEntry() {
        std::cout << "StarEntry page destroyed" << std::endl;
    }

}
