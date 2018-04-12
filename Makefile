#
# Makefile
# zhangyule, 2018-03-27 10:35
#

all:
	g++ -g -lgtest -lglog -lpthread -std=c++11 -o test_main test_main.cpp parsers_test.cpp type_ops_test.cpp table_test.cpp

# vim:ft=make
#
