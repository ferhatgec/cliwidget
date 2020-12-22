#!/bin/sh

c++ -std=c++17 -DBRANCH=1 -lstdc++fs  example.cpp -o ex && ./ex
