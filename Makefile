SRC = src
INC = include
OBJ = build
LIB = lib
BIN = bin

CXX = g++
CXXFLAGS = -std=c++17 -o $@ -I $(INC)

.PRECIOUS: $(OBJ)/%.o

BINFILES = $(addprefix $(BIN)/, $(basename $(notdir $(wildcard $(SRC)/*.cpp))))
OBJFILES = $(patsubst $(LIB)/%.cpp, $(OBJ)/%.o, $(wildcard $(LIB)/*))

all: $(BINFILES)

$(BIN)/%: $(SRC)/%.cpp $(OBJFILES)
	$(CXX) $(CXXFLAGS) $^

$(OBJ)/%.o: $(LIB)/%.cpp $(INC)/%.h
	$(CXX) $(CXXFLAGS) $< -c

clean:
	rm $(BIN)/*
	rm $(OBJ)/*
