#!/usr/bin/env bash

clean()
{
    rm -rf build
    rm -rf babel_client
    rm -rf babel_server
}

compil()
{
    mkdir build && cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake –build .
    make
}

execute()
{
    ./bin/babel
}

if [[ $1 == "clean" ]]; then
    clean
elif [[ $1 == "re" ]]; then
    clean
    compil
    #execute
else
    compil
    #execute
fi
