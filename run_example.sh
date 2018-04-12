#! /bin/sh
#
# run_example.sh
# Copyright (C) 2018 zhangyule <zyl2336709@gmail.com>
#
# Distributed under terms of the MIT license.
#


make clean
make example
cat data/test.txt | ./example
