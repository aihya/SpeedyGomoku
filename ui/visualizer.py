import asyncio
import pygame
from surface    import Surface
from fonts      import *
from init       import *
# from setup      import Setup
from board      import Controller
from final      import Final
from state      import State

# Initialize pygame
pygame.init()


class Window(Surface):
    """
    This class represents the display surface.
    """

    __slots__ = ('_quit',)

    def __init__(self):
        super().__init__(WIDTH, HEIGHT, is_window=True)
        self._quit = False

    @property
    def quit(self):
        return self._quit
    
    @quit.setter
    def quit(self, value):
        self._quit = value

    def blit(self, surface):
        self.surface.blit(surface.surface, surface.abs_rect)

    def update(self):
        pygame.display.flip()


class Game:
    """
    This class represents the game logic.
    """

    __slots__ = ('_state', '_window', '_controller', '_winner')

    def __init__(self):
        self._state           = State()
        self._window          = Window()
        self._controller      = Controller(self.window)
        self._winner          = 0

    @property
    def window(self):
        return self._window
    
    @property
    def controller(self):
        return self._controller

    # @property
    # def setup_surface(self):
    #     return self._setup_surface

    # @property
    # def board_surface(self):
    #     return self._board_surface

    # @property
    # def final_surface(self):
    #     return self._final_surface

    # @property
    # def current_surface(self):
    #     return self._current_surface

    # @current_surface.setter
    # def current_surface(self, value):
    #     self._current_surface = value

    @property
    def state(self):
        return self._state
    
    @property
    def winner(self):
        return self._winner
    
    @winner.setter
    def winner(self, value):
        self._winner = value

    def run(self):
        # while self.window.quit == False:
            # if self.current_surface == SETUP_SURFACE:
            #     self.current_surface = self.setup_surface.loop()
            # elif self.current_surface == BOARD_SURFACE:
            #     self.current_surface, self.winner = self.board_surface.loop()
            # elif self.current_surface == FINAL_SURFACE:
            #     self.final_surface.winner = self.winner
            #     self.current_surface = self.final_surface.loop()
        self.controller.loop()
        # return None


if __name__ == "__main__":
    game = Game()
    game.run()

# [ ] Link the setup with the board
# [ ] Kill the bot(computer) process at the end
