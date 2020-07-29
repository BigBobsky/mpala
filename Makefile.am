bin_PROGRAMS = mpala
mpala_SOURCES = main.cpp
mpala_CPPFLAGS = -std=c++0x \
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

               # -L$(top_srcdir)/pi_export/lib/

mpala_LDADD = src/libmpala.a fusion/libfusion.a \
		-L@RPI_ROOT@/usr/lib/arm-linux-gnueabihf \
		-L@RPI_ROOT@/lib/arm-linux-gnueabihf \
		-L@RPI_ROOT@/usr/lib/ \
               -lgtkmm-3.0 \
	       -lpangomm-1.4 \
               -lgdkmm-3.0 \
               -lsigc-2.0 \
               -lgdk-3 \
               -lgtk-3 \
               -lglibmm-2.4 \
               -latkmm-1.6 \
               -lwiringPi -lpthread -lrt -lpcre



mpala_LDFLAGS =  \
             -Wl,-rpath-link=@RPI_ROOT@/usr/lib/arm-linux-gnueabihf \
	     -Wl,-rpath-link=@RPI_ROOT@/lib/arm-linux-gnueabihf \
	     -Wl,-rpath-link=@RPI_ROOT@/usr/lib/ \
             -Wl,-rpath=/usr/lib/arm-linux-gnueabihf \
	     -Wl,-rpath=/lib/arm-linux-gnueabihf \
	     -Wl,-rpath=/usr/lib/

SUBDIRS = src fusion
