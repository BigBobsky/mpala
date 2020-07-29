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
#include <list>
#include <ctime>

#include <gtkmm/window.h>
#include <gtkmm/notebook.h>

#include "livePage.hpp"
#include "landingPage.hpp"
#include "settingsPage.hpp"
#include "starEntry.hpp"
#include "IMUListener.hpp"
#include "ky-040-manager.hpp"
#include "ky-040-listener.hpp"
#include "mpalaConfig.hpp"

#ifndef STARTRACKER_HPP
#define STARTRACKER_HPP

namespace mpala {

class StarTracker {
  
public:
  
    static const double PI;
    // static const double SIDERAL_SECONDS_TO_SECONDS;
    
    StarTracker(mpalaConfig * config);
  
    virtual ~StarTracker();
  
    // pos en degres
    void addStarWithCurrentTime(double axe1, double axe2);
    
    void addSingleStarWithCurrentTime(double axe1, double axe2);
    
    bool isReady();
    
    // pos en degres
    void updateAxe1(double pos);
    void updateAxe2(double pos);

//    void updateTime();
    
    // coords en degres
    std::vector<double> getStarPositionFromCurrentLocalPosition();
    
    mpalaConfig * config() {return _config;};
    
private:

    mpalaConfig * _config;
    
    bool _refOK;

    
    std::vector<double> _q;
    
    
    
    std::vector<double> _stars_local_coords; // radians
    std::vector<double> _ref_local_coords; // radians
    
    // at this time, algorithm works with two reported stars only
    std::vector<std::time_t> _stars_ref_time;
    
    std::vector<double> _stars_local_axe1; // radians
    std::vector<double> _stars_local_axe2; // radians
    std::vector<double> _stars_real_axe1; // radians
    std::vector<double> _stars_real_axe2; // radians

    // mode single star
    std::time_t _single_star_ref_time;
    double _single_star_real_dec; // radians
    double _single_star_real_ad; // radians
    double _single_star_local_dec; // radians
    double _single_star_local_ad; // radians

    double _single_delta_dec; // radians
    double _single_delta_ad; // radians

    bool _has_single_ref;
    
    // coords en radians
    std::vector<double> getStarPositionFromLocalPosition(std::vector<double> localCoords);
    void computeRef();
};

};

#endif