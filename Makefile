INCLUDES=./lib
CC = g++
CFLAGS = -Wall -std=c++17 -g
TARGET = dynamic
SRC = src
OBJ = build
CSOURCES = $(wildcard $(SRC)/*.cpp)
COBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.out, $(CSOURCES))

all: $(COBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) main.cpp $(COBJECTS) -I$(INCLUDES)

$(OBJ)/%.out: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(COBJECTS) $(TARGET) *~

fclean: clean
	rm -f $(TARGET)
	rm -rf $(TARGET).dSYM/

re: fclean all
