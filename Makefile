static: libgeranode.a

libgeranode.a: geranode.o
	ar rcs $@ $^

geranode.o: geranode.cpp geranode.hpp
	g++ -c $< -o $@

clean:
	rm geranode.o libgeranode.a

install:
	sudo cp libgeranode.a /usr/local/lib/ && sudo cp geranode.hpp /usr/local/include/

all:
	make && make install && make clean