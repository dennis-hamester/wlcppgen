#!/bin/sh

../wlcppgen.py --src template/wlcpp.hpp.in --dst wlcpp.hpp \
    --exclude wl_display \
    --qualify-std-namespace \
    /usr/share/wayland/wayland.xml

../wlcppgen.py --src template/wlcpp.cpp.in --dst wlcpp.cpp \
    --exclude wl_display \
    /usr/share/wayland/wayland.xml

../wlcppgen.py --src template/wlcpp.hpp.in --dst display.hpp \
    --only wl_display \
    --ignore-events \
    --include-guard=_WLCPP_DISPLAY_ \
    --qualify-std-namespace \
    /usr/share/wayland/wayland.xml

../wlcppgen.py --src template/wlcpp.cpp.in --dst display.cpp \
    --only wl_display \
    --header display.hpp \
    --ignore-events \
    /usr/share/wayland/wayland.xml

patch -p1 < template/display.patch

