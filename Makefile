CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = 
TEST_LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
CORE_DIR = core
OBJ_DIR = obj
TEST_DIR = tests

# Todos os fontes do jogo (exceto main.cpp que está na pasta src)
SRCS = $(wildcard $(CORE_DIR)/*.cpp) $(wildcard $(CORE_DIR)/Herois/*.cpp) $(wildcard $(CORE_DIR)/Monstros/*.cpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))
MAIN_OBJ = $(OBJ_DIR)/main.o

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))

TARGET = rpg_game
TEST_TARGET = test_rpg

VPATH = $(SRC_DIR) $(CORE_DIR) $(CORE_DIR)/Herois $(CORE_DIR)/Monstros $(TEST_DIR)

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
