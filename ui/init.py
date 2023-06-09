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

# Constants
HEIGHT      = 800
WIDTH       = 1400
WHITE       = pygame.Color("#ffffff")
BLACK       = pygame.Color("#000000")
BOARD_COLOR = pygame.Color("#F2A71B")
DEFAULT_BG  = pygame.Color("#EAE6E3")
WHITE_COLOR = pygame.Color("#ffffff")
BLACK_COLOR = pygame.Color("#000000")

# Player type
HUMAN       = 1
COMPUTER    = 2
TYPES       = ['human', 'ai']

# Computer difficulty
EASY        = 1
MEDIUM      = 2
HARD        = 3
MODES       = ['easy', 'medium', 'hard']

# Path to the executable
EXE_PATH = '../src/a.out'