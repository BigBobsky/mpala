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

#include <gtkmm/window.h>
#include <gtkmm/notebook.h>

#include "livePage.hpp"
#include "landingPage.hpp"
#include "settingsPage.hpp"
#include "singleEntry.hpp"
#include "starEntry.hpp"
#include "IMUListener.hpp"
#include "ky-040-manager.hpp"
#include "ky-040-listener.hpp"
#include "mpalaConfig.hpp"
#include "starEntryListener.hpp"
#include "starTracker.hpp"

#ifndef MAINVIEW_HPP
#define MAINVIEW_HPP

namespace mpala {

    class MainView : public IMUListener,
    public ky040listener,
    public StarEntryListener,
    public Gtk::Window {
    public:

        MainView(mpalaConfig * config);

        virtual ~MainView();

        virtual void onSituationUpdate(std::vector<double>);

        virtual void onEncoderUpdate(ky040 * encoder, int position);

        virtual void onMeasure(StarEntry* entry, double axe1, double axe2);
        virtual void onMeasure(SingleEntry* entry, double axe1, double axe2);
        
    private:
        
        bool onTimerTick();

        mpalaConfig * _config;
        
        // JLT TODO : a passer en unique_ptr
        StarTracker * _tracker;

        //    Glib::RefPtr<Gtk::Notebook> _mainContainer;
        //    std::unique_ptr<Gtk::Notebook>  _mainContainer;
        Gtk::Notebook _mainContainer;
        LandingPage _landingPage;
        LivePage _livePage;
        SingleEntry _singlePage;
        StarEntry _entry1Page;
        StarEntry _entry2Page;
        SettingsPage _settingsPage;

        ky040 * _axe1;
        ky040 * _axe2;
        
        sigc::connection _timerConnection;
    };

};

#endif