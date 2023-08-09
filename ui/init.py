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
WHITE       = pygame.Color("#ffffffff")
BLACK       = pygame.Color("#000000ff")
BOARD_COLOR = pygame.Color("#F2A71Bff")
DEFAULT_BG  = pygame.Color("#EAE6E3ff")

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
EXE_PATH = '../a.out'