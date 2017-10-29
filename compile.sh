BUILD_DIR='.'
SRC_DIR='src'

#regular binary target
if [[ $1 -eq 'binary-debug' ]]
then
    g++ -g -Wall -Wextra -Werror -c ${SRC_DIR}/potential.cpp -o ${BUILD_DIR}/potential.o -std=c++11
    g++ -g -Wall -Wextra -Werror -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o -std=c++11
    g++ ${BUILD_DIR}/main.o ${BUILD_DIR}/potential.o -o main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp
fi

if [[ $1 -eq 'binary' ]]
then
    g++ -pipe -O3 -Wall -Wextra -Werror -c ${SRC_DIR}/potential.cpp -o ${BUILD_DIR}/potential.o -std=c++11
    g++ -pipe -O3 -Wall -Wextra -Werror -c ${SRC_DIR}/main.cpp -o ${BUILD_DIR}/main.o -std=c++11
    g++ ${BUILD_DIR}/main.o ${BUILD_DIR}/potential.o -o ${BUILD_DIR}/main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp
fi

#pybind target
if [[ $1 == 'python-debug' ]]
then
    #compile potential.o
    g++ -g -Wall -Wextra -Werror -c ${SRC_DIR}/potential.cpp -o ${BUILD_DIR}/potential.o -std=c++11

    #whole lot of flag magic to get pybind11 to compile a .so for python
    includes=`python -m pybind11 --includes`
    g++ -Wall -shared -fPIC -std=c++11 $includes -undefined dynamic_lookup \
        ${SRC_DIR}/binding.cpp ${BUILD_DIR}/potential.o -o ${BUILD_DIR}/potential.so
fi

if [[ $1 == 'python' ]]
then
    #compile potential.o
    g++ -pipe -O3 -Wall -Wextra -Werror -c ${SRC_DIR}/potential.cpp -o ${BUILD_DIR}/potential.o -std=c++11

    #whole lot of flag magic to get pybind11 to compile a .so for python
    includes=`python -m pybind11 --includes`
    g++ -pipe -Wall -O3 -shared -fPIC -std=c++11 $includes -undefined dynamic_lookup \
        ${SRC_DIR}/binding.cpp ${BUILD_DIR}/potential.o -o ${BUILD_DIR}/potential.so
fi
