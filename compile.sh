g++ -g -Wall -Wextra -Werror -c potential.cpp -o potential.o -std=c++11
g++ -g -Wall -Wextra -Werror -c main.cpp -o main.o -std=c++11
g++ main.o potential.o -o main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp
