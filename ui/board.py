import math
from pygame import gfxdraw
from surface import Surface
from init import *
from computer import Computer, Human
import fonts

class Board(Surface):
    """ 
    This class represents the board surface (game board + sidebar).
    """

    __slots__ = ('_turn', '_board', '_sidebar', '_state', '_window', '_repeat', '_offset', '_limit', '_step', '_linspace', '_setup', '_p1', '_p2')

    def __init__(self, window, initial_state, setup):
        super().__init__(WIDTH, HEIGHT, (0, 0))
        self._board    = Surface(HEIGHT, HEIGHT, None)
        self._sidebar  = Surface(WIDTH-HEIGHT, HEIGHT, None)
        self._state    = initial_state
        self._window   = window
        self._repeat   = True
        self._offset   = 40
        self._limit    = self.board.height - self.offset * 2 - 18
        self._step     = int(self.limit / 18)
        self._linspace = [i+self.step for i in range(0, self.board.width - self.offset, self.step)]
        self._setup    = setup
        self._p1       = None
        self._p2       = None
        self._turn     = self._p1

    @property
    def p1(self):
        return self._p1

    @property
    def p2(self):
        return self._p2

    @p1.setter
    def p1(self, value):
        self._p1 = value

    @p2.setter
    def p2(self, value):
        self._p2 = value

    @property
    def setup(self):
        return self._setup

    @property
    def turn(self):
        return self._turn

    @turn.setter
    def turn(self, value):
        self._turn = value

    @property
    def board(self):
        return self._board

    @property
    def sidebar(self):
        return self._sidebar

    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, value):
        self._state = value

    @property
    def repeat(self):
        return self._repeat

    @repeat.setter
    def repeat(self, value):
        self._repeat = value

    @property
    def offset(self):
        return self._offset

    @property
    def limit(self):
        return self._limit

    @property
    def step(self):
        return self._step

    @property
    def linspace(self):
        return self._linspace

    @property
    def window(self):
        return self._window

    @staticmethod
    def draw_circle(surface, x, y, radius, color):
        gfxdraw.aacircle(surface, x, y, radius+1, BLACK_COLOR)
        gfxdraw.aacircle(surface, x, y, radius, color)
        gfxdraw.filled_circle(surface, x, y, radius, color)

    def draw_board(self):
        self.board.surface.fill(BOARD_COLOR)

        for i in range(0, 19):
            # Draw horizontal lines
            xs = self.offset + 0
            ys = self.offset + i * self.step
            xe = self.offset + self.limit
            ye = self.offset + i * self.step
            pygame.draw.line(self.board.surface, pygame.Color('#000000'), (xs, ys), (xe, ye), 1)

            # Draw vertical lines
            xs = self.offset + i * self.step
            ys = self.offset + 0
            xe = self.offset + i * self.step
            ye = self.offset + self.limit
            pygame.draw.line(self.board.surface, pygame.Color('#000000'), (xs, ys), (xe, ye), 1)

    def draw_state(self):
        for r, row in enumerate(self.state.state):
            for c, col in enumerate(row):
                if col in ['1', '2']:
                    color = "#ffffff" if col == '1' else "#000000"
                    x = self.linspace[c] + 1
                    y = self.linspace[r] + 1
                    Board.draw_circle(self.board.surface, x, y, 16, pygame.Color(color))

                    counter = self.state.counts.get((c, r))
                    if counter == None:
                        continue
                    if counter == self.state.counter:
                        count_text = fonts.h4_b.render(f'{counter}', True, (255, 0, 0))
                    else:
                        count_text = fonts.h4_b.render(f'{counter}', True, (0, 0, 0) if col == '1' else (255, 255, 255))
                    count_rect = count_text.get_rect()
                    count_rect.center = (x, y)
                    self.board.surface.blit(count_text, count_rect)
                    

    def check_hover(self):
        x, y = pygame.mouse.get_pos()
        if x >= self.offset and x <= self.limit + self.offset:
            if y >= self.offset and y <= self.limit + self.offset:
                return True
        return False

    def show_hover(self):
        radius = 16
        x, y = pygame.mouse.get_pos()
        # color = "#ffffff" if self.turn == self.p1 else "#000000"
        color = "#FFFF00"
        nx = self.linspace[math.floor((x-radius) / self.step)]
        ny = self.linspace[math.floor((y-radius) / self.step)]
        if math.sqrt((x-nx)**2 + (y-ny)**2) <= radius:
            x, y = nx + 1, ny + 1
        Board.draw_circle(self.board.surface, x, y, radius, pygame.Color(color))

        # Show the current count value on the hover piece.
        if isinstance(self.turn, Human):
            count_text = fonts.h4_b.render(f'{self.state.counter + 1}', True, (0, 0, 0))
            count_rect = count_text.get_rect()
            count_rect.center = (x, y)
            self.board.surface.blit(count_text, count_rect)

        # Return coordinates of the mouse
        return x, y

    def update_board(self):
        self.draw_board()
        self.draw_state()
        if self.check_hover():
            self.show_hover()
        self.surface.blit(self.board.surface, (0, 0))

    def update_sidebar(self):
        self.sidebar.surface.fill(pygame.Color("#EAE6E3"))
        self.surface.blit(self.sidebar.surface, (self.board.width, 0))

    def update(self):
        self.update_board()
        self.update_sidebar()
        self.window.blit(self)
        self.window.update()

    def player_symbol(self):
        if self.turn == self.p1:
            return '1'
        return '2'

    def setup_players(self):
        if self.setup.p1_type.anchor.value == COMPUTER:
            # restart the bot process
            if isinstance(self.p1, Computer):
                self.p1.stop()
            self.p1 = Computer('--black')
            self.p1.start()

            # if restarting failed, kill everything
            if self.p1 == None:
                self.p2.stop()
                self.window.quit = True
                return
        else:
            self.p1 = Human()

        if self.setup.p2_type.anchor.value == COMPUTER:
            # restart the bot process
            if isinstance(self.p2, Computer):
                self.p2.stop()
            self.p2 = Computer('--white')
            self.p2.start()

            # if restarting failed, kill everything
            if self.p2 == None:
                self.window.quit = True
                return
        else:
            self.p2 = Human()

    def reset(self):
        self.state.reset()
        self.setup_players()
        self.turn = self.p1

    def loop(self):
        self.reset()
        self.update()
        while self.repeat:
            for event in pygame.event.get():

                if event.type == pygame.QUIT:
                    self.window.quit = True
                    self.repeat = False
                    break

                if isinstance(self.turn, Human):
                    if event.type == pygame.MOUSEBUTTONUP and event.button == 1 and self.check_hover():

                        # Get the current position of the mouse and map the coordinantes to index the board
                        x, y = pygame.mouse.get_pos()
                        x = math.floor((x-16) / self.step)
                        y = math.floor((y-16) / self.step)

                        # Update the value of the board position to 1 or 2 according to the current turn
                        if self.state.state[y][x] == '0':
                            self.state.update(x, y, self.player_symbol())
                            self.turn = self.p1 if self.turn == self.p2 else self.p2
                            if isinstance(self.turn, Computer):
                                self.turn.process.send(f'{y} {"ABCDEFGHIJKLMNOPQRS"[x]}\n')

            # The previous for-loop will prevent the computer to make a move unless there was a registered event.
            if isinstance(self.turn, Computer):
                # Attempt to get the next move.
                # The function might return `None` in case PopenSpawn.expect did not match the target string.
                move = self.turn.next_move()

                if isinstance(move, int):
                    return FINAL_SURFACE, move

                if move:
                    self.state.update(move['coords'][0], move['coords'][1], self.player_symbol())
                    self.turn = self.p1 if self.turn == self.p2 else self.p2

            if self.window.quit == False:
                self.update()

            CLOCK.tick(60)
