CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude $(shell pkg-config --cflags Qt5Widgets)
LDFLAGS = $(shell pkg-config --libs Qt5Widgets)
TEST_LDFLAGS = -lgtest -lgtest_main -pthread

SRC_DIR = src
CORE_DIR = core
OBJ_DIR = obj
TEST_DIR = tests

# Todos os fontes do jogo (exceto os arquivos da GUI em src/)
SRCS = $(wildcard $(CORE_DIR)/*.cpp) $(wildcard $(CORE_DIR)/Herois/*.cpp) $(wildcard $(CORE_DIR)/Monstros/*.cpp)
OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.cpp=.o)))

# MOC de cabeçalhos Qt
MOC = moc
MOC_SRC = $(SRC_DIR)/moc_MainWindow.cpp

GUI_SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/MainWindow.cpp $(MOC_SRC)
GUI_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(GUI_SRCS:.cpp=.o)))

TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(addprefix $(OBJ_DIR)/, $(notdir $(TEST_SRCS:.cpp=.o)))

TARGET = rpg_game
TEST_TARGET = test_rpg

VPATH = $(SRC_DIR) $(CORE_DIR) $(CORE_DIR)/Herois $(CORE_DIR)/Monstros $(TEST_DIR)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS) $(GUI_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(MOC_SRC): include/MainWindow.hpp
	$(MOC) $< -o $@

$(TEST_TARGET): $(OBJS) $(TEST_OBJS)
	$(CXX) $(filter-out $(shell pkg-config --cflags Qt5Widgets), $(CXXFLAGS)) -o $@ $^ $(TEST_LDFLAGS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TEST_TARGET) savegame.txt $(MOC_SRC)

