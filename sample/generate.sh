#!/bin/sh

PROTOCOL=/usr/share/wayland/wayland.xml
WLCPPGEN=../wlcppgen.py
SRC_HPP=template/wlcpp.hpp.in
SRC_CPP=template/wlcpp.cpp.in
OUTPUT_PATH=generated

echo "generating file display.hpp"
$WLCPPGEN --src $SRC_HPP --dst $OUTPUT_PATH/display.hpp \
    --only wl_display \
    --include-guard _DISPLAY_HPP_ \
    --qualify-std-namespace \
    --ignore-events \
    $PROTOCOL

echo "generating file display.cpp"
$WLCPPGEN --src $SRC_CPP --dst $OUTPUT_PATH/display.cpp \
    --only wl_display \
    --header %c.hpp \
    --ignore-events \
    $PROTOCOL

patch -p1 -d generated < template/display.patch

INTERFACES=$($WLCPPGEN --list-interfaces --exclude wl_display $PROTOCOL)
for i in $INTERFACES
do
    CLASS=$($WLCPPGEN --list-classes --only $i $PROTOCOL)
    DST_HPP=${CLASS}.hpp
    DST_CPP=${CLASS}.cpp

    echo "generating file $DST_HPP"
    $WLCPPGEN --src $SRC_HPP --dst $OUTPUT_PATH/$DST_HPP \
        --only $i \
        --include-guard _%C_HPP_ \
        --qualify-std-namespace \
        $PROTOCOL

    echo "generating file $DST_CPP"
    $WLCPPGEN --src $SRC_CPP --dst $OUTPUT_PATH/$DST_CPP \
        --only $i \
        --header %c.hpp \
        $PROTOCOL
done

