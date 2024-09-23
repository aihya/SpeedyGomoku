import pygame
from surface import Surface

# Clock tick: 30 ticks
CLOCK = pygame.time.Clock()


# Quit
def quit():
    return Surface.QUIT


# Current surface
SETUP_SURFACE = 1
BOARD_SURFACE = 2
FINAL_SURFACE = 3
STATS_SURFACE = 4

# Dimentions
HEIGHT = 800
WIDTH = 1400

# Colors
GRAY_1 = pygame.Color("#252525")
GRAY_2 = pygame.Color("#323232")
GRAY_3 = pygame.Color("#4B4B4B")
LIGHT = pygame.Color("#E0E0E0")
ACCENT = pygame.Color("#E43F5A")
WHITE = pygame.Color("#ffffff")
BLACK = pygame.Color("#000000")
BOARD_COLOR = pygame.Color("#F2A71B")
DEFAULT_BG = pygame.Color("#EAE6E3")

# Checkbox alignment
VERTICAL = 1
HORIZONTAL = 2

# Player type
HUMAN = 1
COMPUTER = 2
TYPES = ["human", "ai"]

# Rules
STANDARD = 1
PRO = 2
LONG_PRO = 3

# Sizes
SIZE_19 = 1
SIZE_15 = 2
SIZE_13 = 3
SIZE_10 = 4
SIZES = ["19", "15", "13", "10"]


# Computer difficulty
EASY = 1
MEDIUM = 2
HARD = 3
MODES = ["easy", "medium", "hard"]

# Path to the executable
EXE_PATH = "../src/a.out"
