all: build clean

build:
	g++ dz.cpp parse_lexeme.cpp -o ex && ./ex

clean:
	rm ex
