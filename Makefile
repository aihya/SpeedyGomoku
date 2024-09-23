# Variables
SRC_DIR = src
INC_DIR = inc
UI_DIR = ui
EXECUTABLE = .gomoku
O_FLAGS = Wall -Wextra -Werror
FLAGS = -std=c++17 -I$(INC_DIR) -O3


# Compile rule
$(EXECUTABLE): $(SRC_DIR)/Gomoku.cpp
	g++ -o $(EXECUTABLE) $(SRC_DIR)/Gomoku.cpp  $(FLAGS)

# Run visualizer
.PHONY: launch
launch: $(EXECUTABLE)
	python3 $(UI_DIR)/visualizer.py   # <--- Make sure this line is indented with a tab

# Clean rule
.PHONY: clean
clean:
	rm -f $(EXECUTABLE)
