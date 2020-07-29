noinst_LIBRARIES = libmpala.a
libmpala_a_CPPFLAGS = -std=c++0x -I$(top_srcdir)/fusion \
                      -I@RPI_ROOT@/usr/include/gtkmm-3.0 \
                      -I@RPI_ROOT@/usr/include/gdkmm-3.0 \
                      -I@RPI_ROOT@/usr/include/sigc++-2.0 \
                      -I@RPI_ROOT@/usr/include/pangomm-1.4 \
                      -I@RPI_ROOT@/usr/include/pango-1.0 \
                      -I@RPI_ROOT@/usr/include/cairomm-1.0 \
                      -I@RPI_ROOT@/usr/include/cairo \
                      -I@RPI_ROOT@/usr/include/freetype2 \
                      -I@RPI_ROOT@/usr/include/glib-2.0 \
                      -I@RPI_ROOT@/usr/include/ \
                      -I@RPI_ROOT@/usr/include/gdk-pixbuf-2.0 \
                      -I@RPI_ROOT@/usr/include/atkmm-1.6 \
                      -I@RPI_ROOT@/usr/include/gtk-3.0 \
                      -I@RPI_ROOT@/usr/include/atk-1.0 \
                      -I@RPI_ROOT@/usr/include/giomm-2.4 \
                      -I@RPI_ROOT@/usr/lib/arm-linux-gnueabihf/glibmm-2.4/include \
                      -I@RPI_ROOT@/usr/lib/arm-linux-gnueabihf/sigc++-2.0/include \
                      -I@RPI_ROOT@/usr/lib/arm-linux-gnueabihf/gtkmm-3.0/include \
                      -I@RPI_ROOT@/usr/lib/arm-linux-gnueabihf/gdkmm-3.0/include \
                      -I@RPI_ROOT@/usr/lib/arm-linux-gnueabihf/glib-2.0/include \
                      -I@RPI_ROOT@/usr/lib/pangomm-1.4/include \
                      -I@RPI_ROOT@/usr/include/glibmm-2.4

libmpala_a_SOURCES = gy80.cpp \
                     I2Cdevice.cpp \
                     I2Cbus.cpp \
                     I2Cutils.cpp \
                     hmc5883l.cpp \
                     adxl345.cpp \
                     bmp085.cpp \
                     l3g4200d.cpp \
		     ky-040-manager.cpp \
		     mpalaConfig.cpp \
                     MathUtils.cpp \
                     SimpleFilter.cpp \
                     livePage.cpp \
                     starEntry.cpp \
                     singleEntry.cpp \
                     settingsPage.cpp \
                     landingPage.cpp \
                     starTracker.cpp \
                     mpalaApp.cpp \
                     mainView.cpp
