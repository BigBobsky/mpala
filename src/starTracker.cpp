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
#include <ctime>
#include <iostream>

#include "starTracker.hpp"
#include "MathUtils.hpp"

namespace mpala {

    const double StarTracker::PI = 3.14159265358979323846;

    StarTracker::StarTracker(mpalaConfig * config) : _config(config), _refOK(false), _stars_local_coords(2), _has_single_ref(false) {

    };

    StarTracker::~StarTracker() {

    };
    
    void StarTracker::addSingleStarWithCurrentTime(double axe1, double axe2) {

        std::cout << "StarTracker::addSingleStarWithCurrentTime"  << std::endl;

        this->_single_star_real_dec = axe1 * PI / 180.0;
        this->_single_star_real_ad = axe2 * PI / 180.0;
        this->_single_star_local_dec = _stars_local_coords[0];
        this->_single_star_local_ad = _stars_local_coords[1];
        this->_single_star_ref_time = std::time(0);
        
        std::vector<double> pos = this->getStarPositionFromLocalPosition(_stars_local_coords);
        
        this->_single_delta_dec = - this->_single_star_real_dec + pos[0];
        this->_single_delta_ad = - this->_single_star_real_ad + pos[1];
        
        this->_has_single_ref = true;

    }


    void StarTracker::addStarWithCurrentTime(double axe1, double axe2) {
        _stars_local_axe1.push_back(_stars_local_coords[0]);
        _stars_real_axe1.push_back(axe1 * PI / 180.0);
        _stars_local_axe2.push_back(_stars_local_coords[1]);
        _stars_real_axe2.push_back(axe2 * PI / 180.0);

        std::time_t t = std::time(0);

        _stars_ref_time.push_back(t);

        if (_stars_ref_time.size() >= 2) {
            std::cout << "computing new referencial" << _stars_ref_time.size() << std::endl;

            computeRef();
        }

    }

//    void StarTracker::updateTime() {
//
//    }

    bool StarTracker::isReady() {
        bool ret = false;

        if ((_stars_ref_time.size() >= 2) && (_refOK == true)) {
            ret = true;
            std::cout << "tracker ready" << std::endl;
        }

        return ret;
    }

    void StarTracker::updateAxe1(double pos) {
        _stars_local_coords[0] = pos * PI / 180.0;
    }

    void StarTracker::updateAxe2(double pos) {
        _stars_local_coords[1] = pos * PI / 180.0;
    }

    // degres
    std::vector<double> StarTracker::getStarPositionFromCurrentLocalPosition() {
        
        std::vector<double> ret = getStarPositionFromLocalPosition(_stars_local_coords);
        
        ret[0] = ret[0] * 180.0 / PI;
        ret[1] = ret[1] * 180.0 / PI;            
        
        return ret;
    }

    // radians in et out
    std::vector<double> StarTracker::getStarPositionFromLocalPosition(std::vector<double> localCoords) {

        // TODO : traiter la date
        std::vector<double> ret(2);

        if (this->isReady()) {

            std::cout << "ready : no delta applied : " << this->_single_delta_dec << " / " << this->_single_delta_ad << std::endl;

            // JLT TODO apply delta t
            ret = _stars_local_coords;

        } else {

            if (this->_has_single_ref) {

                std::time_t t = std::time(0);
                double deltaRadians = (t - this->_single_star_ref_time) * PI / (12 * 3600 - 120); 

                std::cout << "delta applied : " << this->_single_delta_dec << " / " << this->_single_delta_ad << std::endl;
                ret[0] = _stars_local_coords[0] + this->_single_delta_dec;
                ret[1] = _stars_local_coords[1] + this->_single_delta_ad + deltaRadians;
                
            } else {
                std::cout << "not ready but no delta applied : " << this->_single_delta_dec << " / " << this->_single_delta_ad << std::endl;

                ret = _stars_local_coords;                
            }
        }

        return ret;
    }

    void StarTracker::computeRef() {                  
      
//        http://robokitchen.tumblr.com/post/67060392720/finding-a-rotation-quaternion-from-two-pairs-of-vectors        
        
//        If this does not meet the requirements of your own application try to google Wabha's problem.

        

        std::vector<double> u0(3);
        u0[0] = cos(_stars_real_axe1[0])*cos(_stars_real_axe2[0]);
        u0[1] = sin(_stars_real_axe1[0])*cos(_stars_real_axe2[0]);
        u0[2] = sin(_stars_real_axe2[0]);

        std::vector<double> v0(3);
        v0[0] = cos(_stars_real_axe1[1])*cos(_stars_real_axe2[1]);
        v0[1] = sin(_stars_real_axe1[1])*cos(_stars_real_axe2[1]);
        v0[2] = sin(_stars_real_axe2[1]);

        // vecteur monture
        std::vector<double> u2(3);
        u2[0] = cos(_stars_local_axe1[0])*cos(_stars_local_axe2[0]);
        u2[1] = sin(_stars_local_axe1[0])*cos(_stars_local_axe2[0]);
        u2[2] = sin(_stars_local_axe2[0]);
        
        std::vector<double> v2(3);
        v2[0] = cos(_stars_local_axe1[1])*cos(_stars_local_axe2[1]);
        v2[1] = sin(_stars_local_axe1[1])*cos(_stars_local_axe2[1]);
        v2[2] = sin(_stars_local_axe2[1]);


//        Quaternion q2 = Quaternion::fromTwoVectors(u0, u2);
        std::vector<double> q2 = MathUtils::quaternion_rotation_from_vectors(u0, u2);
        std::cout << "q2 = " << q2[0] << " / " << q2[1] << " / " << q2[2] << " / " << q2[3] << std::endl;


//        Vector v1 = v2.rotate(q2.conjugate());
        // inverse de q2
        std::vector<double> q2i = MathUtils::quaternion_inverse(q2);
        std::cout << "q2i = " << q2i[0] << " / " << q2i[1] << " / " << q2i[2] << " / " << q2i[3] << std::endl;

        // calcul de v1
        std::vector<double> v1 = MathUtils::quaternion_multiply_vector(q2i, v2);
        std::cout << "v1 = " << v1[0] << " / " << v1[1] << " / " << v1[2] << std::endl;

    
        // projections sur le plan perp a u0
//        Vector v0_proj = v0.projectPlane(u0);
        std::vector<double> v0p = MathUtils::vector_planar_projection(v0, u0);
        std::cout << "v0p = " << v0p[0] << " / " << v0p[1] << " / " << v0p[2] << std::endl;
//        Vector v1_proj = v1.projectPlane(u0);
        std::vector<double> v1p = MathUtils::vector_planar_projection(v1, u0);
        std::cout << "v1p = " << v1p[0] << " / " << v1p[1] << " / " << v1p[2] << std::endl;

//        Quaternion q1 = Quaternion::fromTwoVectors(v0_proj, v1_proj);
        std::vector<double> q1 = MathUtils::quaternion_rotation_from_vectors(v0p, v1p);

//        return (q2 * q1).normalized();
        // composition des deux rotations
        std::vector<double> q = MathUtils::quaternion_multiply(q2, q1);

        q = MathUtils::quaternion_normalize(q);
        
        std::cout << "qw/qx/qy/qz = " << q[0] << " / " << q[1] << " / " << q[2] << " / " << q[3] << std::endl;

        std::vector<double> testQ2U2 = MathUtils::quaternion_multiply_vector(q2, u0);
        std::cout << "U2 Q2 = " << testQ2U2[0] << " / " << testQ2U2[1] << " / " << testQ2U2[2] << std::endl;
        std::vector<double> testQ2V2 = MathUtils::quaternion_multiply_vector(q2, v0);
        std::cout << "V2 Q2 = " << testQ2V2[0] << " / " << testQ2V2[1] << " / " << testQ2V2[2] << std::endl;


        std::cout << "u0 = " << u0[0] << " / " << u0[1] << " / " << u0[2] << std::endl;
        std::cout << "v0 = " << v0[0] << " / " << v0[1] << " / " << v0[2] << std::endl;
        std::cout << "u2 = " << u2[0] << " / " << u2[1] << " / " << u2[2] << std::endl;
        std::cout << "v2 = " << v2[0] << " / " << v2[1] << " / " << v2[2] << std::endl;

        std::vector<double> testU2 = MathUtils::quaternion_multiply_vector(q, u0);
        std::cout << "U2 = " << testU2[0] << " / " << testU2[1] << " / " << testU2[2] << std::endl;
        std::vector<double> testV2 = MathUtils::quaternion_multiply_vector(q, v0);
        std::cout << "V2 = " << testV2[0] << " / " << testV2[1] << " / " << testV2[2] << std::endl;

        
        this->_q = q;
        this->_refOK = true;
    }

}
