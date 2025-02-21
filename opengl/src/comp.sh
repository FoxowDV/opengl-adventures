#!/bin/sh
g++ -std=c++20 -o output main.cpp glad.c shader.cpp stb_image.cpp -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl 
./output
