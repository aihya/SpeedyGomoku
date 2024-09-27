# Variables
NAME = Gomoku

CC = g++
SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./inc/
UI_PATH = ./ui/

SRC_NAME = Gomoku.cpp
DEPS = $(INC_PATH)/Gomoku.h  # Adjust this if you have headers
OBJ_NAME = $(SRC_NAME:.cpp=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

# -Wall -Wextra -Werror

FLAGS = -std=c++17  -I $(INC_PATH) -O3

# Main rule
all: $(NAME)

# Compile executable
$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $^ -o $@
	@echo "\033[32m[OK]\033[0m \033[33mGomoku compiled\033[0m"

# Compile .cpp to .o in obj folder
$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(FLAGS) -c $< -o $@

# Run visualizer
launch: $(NAME)
	@python3 --version > /dev/null 2>&1 || (echo "\033[31m[ERROR]\033[0m \033[33mPython is not installed\033[0m" && exit 1)
	@if [ ! -d ".venv" ]; then \
		echo "\033[33m[INFO]\033[0m Creating virtual environment and installing requirements..."; \
		python3 -m venv .venv; \
		. .venv/bin/activate; \
		pip install -r requirements.txt; \
	else \
		echo "\033[32m[INFO]\033[0m Virtual environment already exists."; \
		. .venv/bin/activate; \
	fi
	@echo "\033[32m[INFO]\033[0m Running visualizer..."
	@. .venv/bin/activate && python3 $(UI_PATH)/visualizer.py

# Clean object files
clean:
	@rm -rf $(OBJ_PATH)
	@echo "\033[32m[OK]\033[0m \033[33mGomoku object files cleaned\033[0m"

# Clean everything
fclean: clean
	@rm -f $(NAME)
	@deactivate > /dev/null 2>&1 || true
	@rm -rf .venv
	@echo "\033[32m[OK]\033[0m \033[33mGomoku fully cleaned\033[0m"

# Rebuild everything
re: fclean all
