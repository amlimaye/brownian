g++ -g -Wall -Wextra -Werror -c main.cpp -o main.o -std=c++11
g++ main.o -o main -L/usr/local/Cellar/jsoncpp/1.8.3/lib/ -ljsoncpp
