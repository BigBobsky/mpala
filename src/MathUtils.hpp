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

#ifndef MATHUTILS_HPP
#define MATHUTILS_HPP


#include <vector>

namespace mpala {

class MathUtils {
  public:
    
    static const double PI;
    
    static std::vector<double> quaternion_multiply(std::vector<double> & a, std::vector<double> & b);
    static std::vector<double> quaternion_multiply_vector(std::vector<double> & a, std::vector<double> & b);

    static std::vector<double> quaternion_normalize(std::vector<double> & a);
    static std::vector<double> quaternion_inverse(std::vector<double> & a);
    static std::vector<double> quaternion_rotation_from_vectors(std::vector<double> & u, std::vector<double> & v);
     
    static std::vector<double> quaternion_from_axis_angle(std::vector<double> & a, double theta);

    static std::vector<double> quaternion_to_euler_angles(std::vector<double> & a);

    static std::vector<double> quaternion_from_rotation_matrix_rows(std::vector<double> row0,
                                                                    std::vector<double> row1,
                                                                    std::vector<double> row2);

    static std::vector<double> vector_normalize(std::vector<double>& a);
    static std::vector<double> vector_planar_projection(std::vector<double> &v, std::vector<double> p);

    static double vector_norme(std::vector<double>& a);
    
    static std::vector<double> vector_cross(std::vector<double>& a, std::vector<double>& b);

};

};
#endif