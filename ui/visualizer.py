import pygame
from surface    import Surface
from fonts      import *
from init       import *
# from setup      import Setup
from board      import Setup, Board, Game
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


class Controller:

    __slots__ = ('_window', '_phase', '_state', '_board', '_setup', '_stats', '_events', '_sidebar', '_repeat', '_p1', '_p2')

    def __init__(self):
        self._window = Window()
        self._events = None
        self._repeat = True
        self._p1     = None
        self._p2     = None
        # self._state  = State()
        # self._stats  = Stats(relative_to=self.window, position=(HEIGHT, 0))
        self._setup  = Setup(relative_to=self.window, position=(HEIGHT, 0))
        self._board  = Board(None, self._setup, self._p1, self._p2, None)
        self._phase  = SETUP_SURFACE

    @property
    def phase(self):
        return self._phase
    
    @phase.setter
    def phase(self, value):
        self._phase = value

    @property
    def state(self):
        return self._state

    @property
    def board(self):
        return self._board

    @property
    def events(self):
        return self._events

    @events.setter
    def events(self, value):
        self._events = value

    @property
    def repeat(self):
        return self._repeat

    @repeat.setter
    def repeat(self, value):
        self._repeat = value

    @property
    def setup(self):
        return self._setup

    @property
    def p1(self):
        return self._p1
    
    @p1.setter
    def p1(self, value):
        self._p1 = value

    @property
    def p2(self):
        return self._p2
    
    @p2.setter
    def p2(self, value):
        self._p2 = value

    @property
    def window(self):
        return self._window

    def loop(self):
        while not quit():

            self.events = pygame.event.get()

            # Exit in pygame.QUIT event
            for event in self.events:
                if event.type == pygame.QUIT:
                    exit(0)

            # TODO: To reconsider
            if self.phase == SETUP_SURFACE:
                self.board.draw_board()
                self.phase = self.setup.update(self.events)
            else:
                game = Game(self.window, self.setup)
                game.loop()

            self.window.blit(self.setup)
            self.window.blit(self.board)
            self.window.update()

            CLOCK.tick(60)


if __name__ == "__main__":
    game = Controller()
    game.loop()

# [ ] Link the setup with the board
# [ ] Kill the bot(computer) process at the end
