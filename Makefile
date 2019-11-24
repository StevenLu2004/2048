SRC = src
BUILD = build

objects = $(BUILD)/2048.o

2048: $(objects)
	g++ -o 2048 $(objects)

$(BUILD)/2048.o: $(SRC)/2048.cpp $(SRC)/2048push.hpp $(SRC)/2048rand.hpp $(SRC)/2048render.hpp $(SRC)/altScreen.hpp $(SRC)/rawTerminal.hpp
	mkdir $(BUILD) || echo "failed to create ./$(BUILD)"
	g++ -c -o $(BUILD)/2048.o $(SRC)/2048.cpp

.PHONY: clean install

clean:
	rm -r build

install: 2048
	echo "Trying to elevate access level..."
	{ sudo cp -i 2048 /usr/local/bin/2048 ; } && { rm 2048 ; } ;
