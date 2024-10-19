#!/bin/bash

echo test with no args
./cub3D
if [ $? != 1 ]; then
    echo failed
    exit 1
fi

echo ----------
echo test with too many args
./cub3D maps/example.cub maps/map.cub
if [ $? != 1 ]; then
    echo failed
    exit 1
fi

for file in maps/valid/*; do
    echo ----------
    echo testsing $file
    ./cub3D "$file" &
    pid=$!
    sleep 1
    if kill -0 $pid 2>/dev/null; then
        echo "cub3D is still running after 1 second. Terminating..."
        kill $pid
        wait $pid
        EXIT_CODE=$?
        echo "Success"
    else
        wait $pid
        EXIT_CODE=$?
        echo "\ncub3D exited with exit code: $EXIT_CODE"
        # exit code 2 is for mlx errors, they are expected in gh actions
        if $EXIT_CODE != 2; then
            exit 1
        echo "Success"
    fi
done

for file in maps/invalid/*; do
    echo ----------
    echo testsing $file
    ./cub3D "$file" &
    pid=$!
    sleep 1
    if kill -0 $pid 2>/dev/null; then
        echo "cub3D is still running after 1 second. Terminating..."
        kill $pid
        wait $pid
        EXIT_CODE=$?
        echo "cub3D shouldn't be running with invalid map"
        exit 1
    else
        wait $pid
        EXIT_CODE=$?
        echo "cub3D exited with exit code: $EXIT_CODE"
        if $EXIT_CODE != 1; then
            echo "wrong exit code"
            exit 1
        fi
        echo "Success"
    fi
done
