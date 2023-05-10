import asyncio
import pygame
from surface    import Surface
from fonts      import *
from init       import *
from setup      import Setup
from board      import Board
from final      import Final
from state      import State

# Initialize pygame
pygame.init()


class Window:
    """
    This class represents the display surface.
    """

    __slots__ = ('_width', '_height', '_surface', '_quit')

    def __init__(self):
        self._width   = WIDTH
        self._height  = HEIGHT
        self._surface = pygame.display.set_mode((self._width, self._height))
        self._quit    = False

    @property
    def width(self):
        return self._width

    @property
    def height(self):
        return self._height

    @property
    def quit(self):
        return self._quit
    
    @quit.setter
    def quit(self, value):
        self._quit = value

    @property
    def surface(self):
        return self._surface

    def blit(self, surface: Surface):
        self._surface.blit(surface.surface, (0, 0))

    def update(self):
        pygame.display.flip()


class Game:
    """
    This class represents the game logic.
    """

    __slots__ = ('_state', '_window', '_setup_surface', '_board_surface', '_final_surface', '_current_surface', '_computer')

    def __init__(self):
        self._state           = State()
        self._window          = Window()
        self._setup_surface   = Setup(self._window)
        self._board_surface   = Board(self._window, 1, self._state, self._setup_surface)
        self._final_surface   = Final(self._window)
        self._current_surface = FINAL_SURFACE

    @property
    def window(self):
        return self._window

    @property
    def setup_surface(self):
        return self._setup_surface

    @property
    def board_surface(self):
        return self._board_surface

    @property
    def final_surface(self):
        return self._final_surface

    @property
    def current_surface(self):
        return self._current_surface

    @current_surface.setter
    def current_surface(self, value):
        self._current_surface = value

    @property
    def state(self):
        return self._state

    def run(self):
        while self.window.quit == False:
            if self.current_surface == SETUP_SURFACE:
                self.current_surface = self.setup_surface.loop()
            elif self.current_surface == BOARD_SURFACE:
                self.current_surface = self.board_surface.loop()
            elif self.current_surface == FINAL_SURFACE:
                self.current_surface = self.final_surface.loop()
        return None


if __name__ == "__main__":
    game = Game()
    game.run()

# [ ] Link the setup with the board
# [ ] Kill the bot(computer) process at the end
