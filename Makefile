COMPILER=g++
OPTIONS=-std=c++17 -lmariadbcpp -lhttpserver

all: server

server:
	$(COMPILER) mysql_select.cpp server.cpp -o server $(OPTIONS)

clean:
	rm -f server
