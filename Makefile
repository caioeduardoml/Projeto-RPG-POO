CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = 
TEST_LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
OBJ_DIR = obj
TEST_DIR = tests

# Ignorando main.cpp para não causar conflito de multiplas mains no test
SRCS = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/Herois/*.cpp) $(wildcard $(SRC_DIR)/Monstros/*.cpp))
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
MAIN_OBJ = $(OBJ_DIR)/main.o

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))

TARGET = rpg_game
TEST_TARGET = test_rpg

VPATH = $(SRC_DIR) $(SRC_DIR)/Herois $(SRC_DIR)/Monstros $(TEST_DIR)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET) savegame.txt
