TARGET = geometry
SUBTARGET = test

CC = clang++
CFLAGS = -Wall -Werror
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
GTEST_FLAGS = -lgtest -pthread

SRC_DIR = src
TEST_DIR = test
OBJ_DIR_SRC = obj/src
OBJ_DIR_TEST = obj/test
BIN_DIR = bin

SRC = $(wildcard $(SRC_DIR)/main/*.cpp) $(wildcard $(SRC_DIR)/lib/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR_SRC)/%.o, $(SRC))

all: $(BIN_DIR)/$(TARGET) $(BIN_DIR)/test

$(BIN_DIR)/$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $(SFML_FLAGS) $^ -o $@

$(BIN_DIR)/$(SUBTARGET): $(OBJ_DIR_TEST)/MyParser.o $(OBJ_DIR_TEST)/ParserTest.o
	$(CC) $(CFLAGS) $^ -o $@ $(GTEST_FLAGS)

$(OBJ_DIR_SRC)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_TEST)/%.o: $(SRC_DIR)/lib/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR_TEST)/%.o: $(TEST_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR_SRC)/*.o $(OBJ_DIR_TEST)/*.o $(BIN_DIR)/$(TARGET) $(BIN_DIR)/$(SUBTARGET)

.PHONY: all clean