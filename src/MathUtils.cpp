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

#include <iostream>
#include <math.h>
#include "MathUtils.hpp"

namespace mpala {

    const double MathUtils::PI = 3.14159265;

    std::vector<double> MathUtils::quaternion_multiply_vector(std::vector<double> & a, std::vector<double> & v) {
        std::vector<double> ret(3);
        if ((a.size() == 4) && (v.size() == 3)) {

            
            double num = a[1] * 2.0;
            double num2 = a[2] * 2.0;
            double num3 = a[3] * 2.0;
            double num4 = a[1] * num;
            double num5 = a[2] * num2;
            double num6 = a[3] * num3;
            double num7 = a[1] * num2;
            double num8 = a[1] * num3;
            double num9 = a[2] * num3;
     
            double num10 = a[0] * num;
            double num11 = a[0] * num2;
            double num12 = a[0] * num3;
     
            ret[0] = (1.0 - (num5 + num6)) * v[0] + (num7 - num12) * v[1] + (num8 + num11) * v[2];
            ret[1] = (num7 + num12) * v[0] + (1.0 - (num4 + num6)) * v[1] + (num9 - num10) * v[2];
            ret[2] = (num8 - num11) * v[0] + (num9 + num10) * v[1] + (1.0 - (num4 + num5)) * v[2];                        
            

        } else {
            // retourner quoi ???
        }

        return ret;
    }

    std::vector<double> MathUtils::quaternion_multiply(std::vector<double> & a, std::vector<double> & b) {
        std::vector<double> ret(4);
        if ((a.size() == 4) && (b.size() == 4)) {

            double aw, ax, ay, az;
            double bw, bx, by, bz;

            aw = a[0];
            ax = a[1];
            ay = a[2];
            az = a[3];
            bw = b[0];
            bx = b[1];
            by = b[2];
            bz = b[3];

            // std::cout << "multiply : " << aw << " " << ax << " " << ay << " " << az << std::endl;
            // std::cout << "multiply : " << bw << " " << bx << " " << by << " " << bz << std::endl;

            ret[0] = aw * bw - ax * bx - ay * by - az*bz;
            ret[1] = aw * bx + ax * bw + ay * bz - az*by;
            ret[2] = aw * by - ax * bz + ay * bw + az*bx;
            ret[3] = aw * bz + ax * by - ay * bx + az*bw;

        } else {
            // retourner quoi ???
        }

        return ret;
    }

    std::vector<double> MathUtils::vector_planar_projection(std::vector<double>& v, std::vector<double> p) {

        std::vector<double> ret(3);

        if ((v.size() == 3) && (p.size() == 3)) {
            // projection sur le vecteur normal

            // produit scalaire
            double a = (v[0] * p[0] + v[1] * p[1] + v[2] * p[2]);

            ret[0] = v[0] - a * p[0];
            ret[1] = v[1] - a * p[1];
            ret[2] = v[2] - a * p[2];

        } else {
            // erreur
        }


        return ret;

    }

    std::vector<double> MathUtils::quaternion_normalize(std::vector<double>& a) {
        std::vector<double> ret(4);

        double mag = ::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3]);

        ret[0] = a[0] / mag;
        ret[1] = a[1] / mag;
        ret[2] = a[2] / mag;
        ret[3] = a[3] / mag;

        return ret;
    }

    std::vector<double> MathUtils::quaternion_inverse(std::vector<double>& a) {
        std::vector<double> ret(4);

        ret[0] = a[0];
        ret[1] = -a[1];
        ret[2] = -a[2];
        ret[3] = -a[3];

        return ret;
    }

    std::vector<double> MathUtils::vector_normalize(std::vector<double>& a) {
        std::vector<double> ret(3);

        double mag = ::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);

        ret[0] = a[0] / mag;
        ret[1] = a[1] / mag;
        ret[2] = a[2] / mag;

        return ret;
    }

    double MathUtils::vector_norme(std::vector< double >& a) {
        double ret = 0.0;

        ret = ::sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);

        return ret;
    }

    std::vector< double > MathUtils::quaternion_from_axis_angle(std::vector< double >& a, double theta) {
        std::vector<double> ret(4);

        // std::cout << " quaternion_from_axis_angle  : " << a[0] << "," << a[1] << "," << a[2] << " : " << theta << std::endl; 

        double sin_half_theta = ::sin(theta / 2.0);
        // std::cout << " quaternion_from_axis_angle  : " << sin_half_theta << std::endl; 

        ret[0] = ::cos(theta / 2.0);
        ret[1] = a[0] * sin_half_theta;
        ret[2] = a[1] * sin_half_theta;
        ret[3] = a[2] * sin_half_theta;

        return ret;
    }

    std::vector< double > MathUtils::vector_cross(std::vector< double >& a, std::vector< double >& b) {
        std::vector<double> ret(3);

        ret[0] = a[1] * b[2] - a[2] * b[1];
        ret[1] = a[2] * b[0] - a[0] * b[2];
        ret[2] = a[0] * b[1] - a[1] * b[0];

        return ret;
    }

    std::vector<double> MathUtils::quaternion_from_rotation_matrix_rows(std::vector<double> row0, std::vector<double> row1, std::vector<double> row2) {

        std::vector<double> ret(4);
        double S, w, x, y, z;

        double trace = row0[0] + row1[1] + row2[2];

        //    std::cout << "from matrix rows trace : " << trace << std::endl;
        if (trace > row2[2]) {
            S = ::sqrt(1.0 + trace) * 2;
            w = 0.25 * S;
            x = (row2[1] - row1[2]) / S;
            y = (row0[2] - row2[0]) / S;
            z = (row1[0] - row0[1]) / S;
            //        std::cout << "from matrix rows : " << S << " " << w << " " << x << " " << y << " " << z << std::endl;

        } else if ((row0[0] < row1[1]) && (row0[0] < row2[2])) {
            S = sqrt(1.0 + row0[0] - row1[1] - row2[2]) * 2;
            w = (row2[1] - row1[2]) / S;
            x = 0.25 * S;
            y = (row0[1] + row1[0]) / S;
            z = (row0[2] + row2[0]) / S;
            //        std::cout << "from matrix rows 2 : " << S << " " << w << " " << x << " " << y << " " << z << std::endl;
        } else if (row1[1] < row2[2]) {
            S = sqrt(1.0 + row1[1] - row0[0] - row2[2]) * 2;
            w = (row0[2] - row2[0]) / S;
            x = (row0[1] + row1[0]) / S;
            y = 0.25 * S;
            z = (row1[2] + row2[1]) / S;
            //        std::cout << "from matrix rows 3: " << S << " " << w << " " << x << " " << y << " " << z << std::endl;

        } else {
            S = sqrt(1.0 + row2[2] - row0[0] - row1[1]) * 2;
            w = (row1[0] - row0[1]) / S;
            x = (row0[2] + row2[0]) / S;
            y = (row1[2] + row2[1]) / S;
            z = 0.25 * S;
            //        std::cout << "from matrix rows 4 : " << S << " " << w << " " << x << " " << y << " " << z << std::endl;
        }

        ret[0] = w;
        ret[1] = x;
        ret[2] = y;
        ret[3] = z;

        return ret;

    }

    std::vector<double> MathUtils::quaternion_rotation_from_vectors(std::vector<double>& u, std::vector<double>& v) {

        std::vector<double> ret(4);

        if ((u.size() == 3) && (v.size() == 3)) {

            std::vector<double> l = vector_cross(u, v);
            std::cout << "lx/ly/lz = " << l[0] << " / " << l[1] << " / " << l[2] << std::endl;

            
            // vecteur directeur de la rotation q2
            double q2x = l[0];
            double q2y = l[1];
            double q2z = l[2];

            double dot_v = u[0] * v[0] + u[1] * v[1] + u[2] * v[2];

            double k2 = sqrt((v[0] * v[0] + v[1] * v[1] + v[2] * v[2]) * (u[0] * u[0] + u[1] * u[1] + u[2] * u[2]));

            double q2w =  dot_v + k2;
            
            double N2 = sqrt(q2w * q2w + q2x * q2x + q2y * q2y + q2z * q2z);
            
            q2w = q2w / N2;
            q2x = q2x / N2;
            q2y = q2y / N2;
            q2z = q2z / N2;

            ret[0] = q2w;
            ret[1] = q2x;
            ret[2] = q2y;
            ret[3] = q2z;
        } else {
            std::cout << "error : no rotation " << std::endl;

        }

        return ret;
    }

    std::vector<double> MathUtils::quaternion_to_euler_angles(std::vector<double>& a) {

        std::vector<double> ret(3);

        double w = a[0];
        double x = a[1];
        double y = a[2];
        double z = a[3];

        double w2 = w*w;
        double x2 = x*x;
        double y2 = y*y;
        double z2 = z*z;

        ret[0] = ::atan2(2.0 * (x * y + z * w), w2 + x2 - y2 - z2);
        ret[1] = ::asin(2.0 * (w * y - x * z) / (w2 + x2 + y2 + z2));
        ret[2] = ::atan2(2.0 * (y * z + x * w), w2 - x2 - y2 + z2);

        return ret;
    }

}
