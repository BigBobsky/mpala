
PI=pi@bigbobsky.dtdns.net
OPT="-P 5223"

mkdir pi_export
mkdir pi_export/include
mkdir pi_export/lib

scp $OPT -r $PI:/usr/include/gtkmm-3.0 pi_export/include
scp $OPT -r $PI:/usr/include/glibmm-2.4 pi_export/include
scp $OPT -r $PI:/usr/include/gdkmm-3.0 pi_export/include
scp $OPT -r $PI:/usr/include/gtk-3.0 pi_export/include
scp $OPT -r $PI:/usr/include/pango-1.0 pi_export/include
scp $OPT -r $PI:/usr/include/pangomm-1.4 pi_export/include
scp $OPT -r $PI:/usr/include/cairomm-1.0 pi_export/include
scp $OPT -r $PI:/usr/include/gio-unix-2.0/ pi_export/include
scp $OPT -r $PI:/usr/include/atk-1.0 pi_export/include
scp $OPT -r $PI:/usr/include/atkmm-1.6 pi_export/include
scp $OPT -r $PI:/usr/include/giomm-2.4 pi_export/include
scp $OPT -r $PI:/usr/include/cairo pi_export/include
scp $OPT -r $PI:/usr/include/fontconfig pi_export/include
scp $OPT -r $PI:/usr/include/gdk-pixbuf-2.0  pi_export/include
scp $OPT -r $PI:/usr/include/freetype2 pi_export/include
scp $OPT -r $PI:/usr/include/glib-2.0  pi_export/include
scp $OPT -r $PI:/usr/lib/arm-linux-gnueabihf/glib-2.0/include/* pi_export/include
scp $OPT -r $PI:/usr/lib/arm-linux-gnueabihf/glibmm-2.4/include/* pi_export/include
scp $OPT -r $PI:/usr/lib/arm-linux-gnueabihf/sigc++-2.0/include/* pi_export/include

scp $OPT -r $PI:/usr/lib/arm-linux-gnueabihf/pangomm-1.4/include/* pi_export/include
scp $OPT -r $PI:/usr/lib/arm-linux-gnueabihf/gdkmm-3.0/include/* pi_export/include
scp $OPT -r $PI:/usr/lib/arm-linux-gnueabihf/gtkmm-3.0/include/* pi_export/include

scp $OPT -r $PI:/usr/include/pixman-1 pi_export/include
scp $OPT -r $PI:/usr/include/sigc++-2.0 pi_export/include
scp $OPT -r $PI:/usr/include/libpng12 pi_export/include

scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libgtk*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libgdk*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libatk*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libatkmm*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/*libatkmm* pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libgio*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libpango*.so* pi_export/lib
scp $OPT -r  $PI:/usr/lib/libpangomm*.so* pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libcairo*.so* pi_export/lib
scp $OPT -r  $PI:/usr/lib/libcairo*.so* pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libgobject*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libglib*.so pi_export/lib
scp $OPT -r  $PI:/usr/lib/arm-linux-gnueabihf/libatspi*.so.* pi_export/lib
