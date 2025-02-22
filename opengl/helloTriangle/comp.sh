#!/bin/sh
g++ -std=c++20 -o output main.cpp glad.c -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
./output
