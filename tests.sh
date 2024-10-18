#!/bin/bash

echo test with no args
./cub3D
if [ $? != 1 ]; then
    echo failed
    exit 1
fi

echo test with too many args
./cub3D maps/example.cub maps/map.cub
if [ $? != 1 ]; then
    echo failed
    exit 1
fi