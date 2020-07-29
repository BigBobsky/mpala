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

#ifndef STARENTRY_LISTENER_HPP
#define STARENTRY_LISTENER_HPP

namespace mpala {

    class StarEntry;
    class SingleEntry;

    class StarEntryListener {
    public:

        // mesures en degres
        virtual void onMeasure(StarEntry * entry, double axe1, double axe2) = 0;

        virtual void onMeasure(SingleEntry * entry, double axe1, double axe2) = 0;

    };

};

#endif