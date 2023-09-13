all: build clean

build:
	g++ main.cpp parse_lexeme.cpp -o ex && ./ex

clean:
	rm ex
