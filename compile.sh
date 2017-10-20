#regular binary target
if [[ $1 -eq 'binary' ]]
then
    g++ -g -Wall -Wextra -Werror -c potential.cpp -o potential.o -std=c++11
    g++ -g -Wall -Wextra -Werror -c main.cpp -o main.o -std=c++11
    g++ main.o potential.o -o main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp
fi

#pybind target
if [[ $1 == 'python' ]]
then
    g++ -g -Wall -Wextra -Werror -c potential.cpp -o potential.o -std=c++11

    g++ -Wall -shared -fPIC -std=c++11 $(python -m pybind11 --includes) -undefined dynamic_lookup binding.cpp potential.o -o potential.so
fi
