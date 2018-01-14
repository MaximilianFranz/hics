#!/usr/bin/env bash
# build the project

make --jobs $NUM_THREADS
sudo make install
