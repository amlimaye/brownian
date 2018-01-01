BUILD_DIR='.'
SRC_DIR='src'
includes=`python -m pybind11 --includes`

binary-debug:
	g++ -g -Wall -Wextra -Werror -c $(SRC_DIR)/potential.cxx -o $(BUILD_DIR)/potential.o -std=c++11
	g++ -g -Wall -Wextra -Werror -c $(SRC_DIR)/main.cxx -o $(BUILD_DIR)/main.o -std=c++11
	g++ $(BUILD_DIR)/main.o $(BUILD_DIR)/potential.o -o main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp

binary:
	g++ -pipe -O3 -Wall -Wextra -Werror -c $(SRC_DIR)/potential.cxx -o $(BUILD_DIR)/potential.o -std=c++11
	g++ -pipe -O3 -Wall -Wextra -Werror -c $(SRC_DIR)/main.cxx -o $(BUILD_DIR)/main.o -std=c++11
	g++ $(BUILD_DIR)/main.o $(BUILD_DIR)/potential.o -o $(BUILD_DIR)/main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp

pydebug:
	g++ -g -Wall -Wextra -Werror -c $(SRC_DIR)/potential.cxx -o $(BUILD_DIR)/potential.o -std=c++11
	g++ -Wall -shared -fPIC -std=c++11 $(includes) -undefined dynamic_lookup \
        $(SRC_DIR)/binding.cxx $(BUILD_DIR)/potential.o -o $(BUILD_DIR)/potential.so

py:
	g++ -pipe -O3 -Wall -Wextra -Werror -c $(SRC_DIR)/potential.cxx -o $(BUILD_DIR)/potential.o -std=c++11
	g++ -pipe -Wall -O3 -shared -fPIC -std=c++11 $(includes) -undefined dynamic_lookup \
        $(SRC_DIR)/binding.cxx $(BUILD_DIR)/potential.o -o $(BUILD_DIR)/potential.so

all: py binary

clean:
	rm -f main.o potential.o main potential.so
