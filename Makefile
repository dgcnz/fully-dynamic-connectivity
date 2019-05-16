INCLUDES=./include
CC = g++
CFLAGS = -Wall
TARGET = euler
SRC = src
OBJ = build
CSOURCES = $(wildcard $(SRC)/*.cpp)
COBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.out, $(CSOURCES))

all: $(COBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) main.c $(COBJECTS) -I$(INCLUDES)

$(OBJ)/%.out: $(SRC)/%.cpp
	gcc  -c $< -o $@

clean:
	rm -f $(COBJECTS) $(TARGET) *~

fclean: clean
	rm -f $(TARGET)

re: fclean all
