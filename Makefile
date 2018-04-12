#
# Makefile
# zhangyule, 2018-03-27 10:35
#

all:
	g++ -g -lgtest -lglog -lpthread -std=c++11 -o test_main test/test_main.cpp test/parsers_test.cpp test/type_ops_test.cpp test/table_test.cpp
	g++ -c test/trait_test.cpp

# vim:ft=make
#
example:
	g++ -g -std=c++11 -o example -L./ demo/easy_table_example.cpp

clean:
	rm example
