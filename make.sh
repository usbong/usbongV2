#!/bin/bash

# Usbong (version 2.0) System
#
# C/C++ Computer Language and Simple Directmedia Layer (SDL) + SDL Image
#
# Compile and Link Multiple Source Files
#
# @company: USBONG
# @author: SYSON, MICHAEL B.
# @date created: 20211111
# @last updated: 20220125; from 20220122
# @website address: http://www.usbong.ph
#Tugon
# Reference:
# 1) https://www3.ntu.edu.sg/home/ehchua/programming/cpp/gcc_make.html;
# last accessed: 20211111

outputDirectory="./output"

#if directory does NOT yet exist
if [ ! -d "$outputDirectory" ]; then
	mkdir ./output
fi

#note: sequence

g++ -c mainLinux.cpp
g++ -c MyDynamicObject.cpp
g++ -c Ipis.cpp
g++ -c Unit.cpp
g++ -c Sdlwav.cpp
g++ -c Font.cpp
g++ -c Text.cpp
g++ -c Level2D.cpp
g++ -c UsbongUtils.cpp

g++ -pthread -o ./output/UsbongV2Linux mainLinux.o MyDynamicObject.o Ipis.o Unit.o Sdlwav.o Font.o Text.o Level2D.o UsbongUtils.o -lSDL2 -lSDL2_image -lSDL2_mixer
