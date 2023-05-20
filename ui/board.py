import math
from pygame import gfxdraw
from surface import Surface
from init import *
from computer import Computer, Human
from components import Button, CheckBoxs
from state      import State
import fonts
import fonts

class Setup(Surface):
    """ 
    This class represents the setup surface
    """

    __slots__ = ('_window', '_repeat', '_start', '_p1', '_p1_surf', '_p1_type', '_p1_mode', '_p2', '_p2_surf', '_p2_type', '_p2_mode')

    def __init__(self, window, *args, **kwargs):
        super().__init__(WIDTH-HEIGHT, HEIGHT, *args, **kwargs)
        self._window = window
        self._repeat = True

        self._start = Button("#000000", "#66F587", "START", fonts.h3_t, relative_to=self)
        self._start.position = (self.width / 2 - self._start.width / 2, self.height * 0.7)
        # Player 1 setup surface
        self._p1_surf = Surface(300, 400, (20, 120), self)
        self._p1_type = CheckBoxs(
            {HUMAN: 'Human', COMPUTER: 'Computer'},
            position=(0, 50),
            relative_to=self._p1_surf
        )
        self._p1_mode = CheckBoxs( 
            {EASY: 'Easy', MEDIUM: 'Medium', HARD: 'Hard'},
            position=(0, self._p1_type.height + 70),
            relative_to=self._p1_surf
        )

        # Player 2 setup surface
        self._p2_surf = Surface(300, 400, (320, 120), self)
        self._p2_type = CheckBoxs(
            {HUMAN: 'Human', COMPUTER: 'Computer'},
            position=(0, 50),
            relative_to=self._p2_surf
        )
        self._p2_mode = CheckBoxs(
            {EASY: 'Easy', MEDIUM: 'Medium', HARD: 'Hard'},
            position=(0, self._p2_type.height + 70),
            relative_to=self._p2_surf
        )

        # self._p1 = None
        # self._p2 = None
        
    @property
    def window(self):
        return self._window

    @property
    def start(self):
        return self._start

    @property
    def p1_surf(self):
        return self._p1_surf

    @property
    def p1_type(self):
        return self._p1_type

    @property
    def p1_mode(self):
        return self._p1_mode

    @property
    def p2_surf(self):
        return self._p2_surf

    @property
    def p2_type(self):
        return self._p2_type

    @property
    def p2_mode(self):
        return self._p2_mode

    # @property
    # def p1(self):
    #     return self._p1

    # @property
    # def p2(self):
    #     return self._p2

    # @p1.setter
    # def p1(self, value):
    #     self._p1 = value

    # @p2.setter
    # def p2(self, value):
    # #     self._p2 = value

    @property
    def repeat(self):
        return self._repeat

    @repeat.setter
    def repeat(self, value):
        self._repeat = value

    def draw_box_1(self):
        header = fonts.h3_t.render('Player 1', True, BLACK_COLOR, DEFAULT_BG)
        header_rect = header.get_rect()
        header_rect.topleft = (0, 0)

        self.p1_surf.surface.fill(DEFAULT_BG)
        self.p1_surf.surface.blit(header, header_rect)

        # Update type checkboxs
        self.p1_type.update()
        self.p1_surf.surface.blit(self.p1_type.surface, self.p1_type.rect)

        # Blit mode surface
        if self.p1_type.anchor.value == 2:
            self.p1_mode.update()
            self.p1_surf.surface.blit(self.p1_mode.surface, self.p1_mode.rect)

        # Blit first player surface on the window
        self.surface.blit(self.p1_surf.surface, self.p1_surf.rect)

    def draw_box_2(self):
        header = fonts.h3_t.render('Player 2', True, BLACK_COLOR, DEFAULT_BG)
        header_rect = header.get_rect()
        header_rect.topleft = (0, 0)

        self.p2_surf.surface.fill(DEFAULT_BG)
        self.p2_surf.surface.blit(header, header_rect)

        # Update type checkboxs
        self.p2_type.update()
        self.p2_surf.surface.blit(self.p2_type.surface, self.p2_type.rect)

        # Blit mode surface
        if self.p2_type.anchor.value == 2:
            self.p2_mode.update()
            self.p2_surf.surface.blit(self.p2_mode.surface, self.p2_mode.rect)

        # Blit first player surface on the window
        self.surface.blit(self.p2_surf.surface, self.p2_surf.rect)

    # def setup_players(self):
    #     if self.p1_type.anchor.value == COMPUTER:
    #         # restart the bot process
    #         if isinstance(self.p1, Computer):
    #             self.p1.stop()
    #         self.p1 = Computer('--black')
    #         self.p1.start()

    #         # if restarting failed, kill everything
    #         if self.p1 == None:
    #             self.p2.stop()
    #             self.window.quit = True
    #             return
    #     else:
    #         self.p1 = Human()

    #     if self.p2_type.anchor.value == COMPUTER:
    #         # restart the bot process
    #         if isinstance(self.p2, Computer):
    #             self.p2.stop()
    #         self.p2 = Computer('--white')
    #         self.p2.start()

    #         # if restarting failed, kill everything
    #         if self.p2 == None:
    #             self.window.quit = True
    #             return
    #     else:
    #         self.p2 = Human()

    def update(self, events):
        self.surface.fill(DEFAULT_BG)

        # subtitle
        middle = fonts.h3_t.render('Game Setup', True, BLACK_COLOR, DEFAULT_BG)
        middle_rect = middle.get_rect()
        middle_rect.topleft = (270, 35)

        self.surface.blit(middle, middle_rect)

        type_checkboxs = [*self.p1_type.container, *self.p2_type.container]
        mode_checkboxs = [*self.p1_mode.container, *self.p2_mode.container]

        # while self.repeat:
        for event in events:
            if event.type == pygame.QUIT:
                exit(0)

            if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                if self.start.clicked():
                    return BOARD_SURFACE
                for box in type_checkboxs:
                    box.check_clicked()
                for box in mode_checkboxs:
                    box.check_clicked()

        self.p2_type.anchor.checked = False
        if self.p1_type.anchor.value == HUMAN:
            self.p2_type.anchor = self.p2_type.container[1]
        else:
            self.p2_type.anchor = self.p2_type.container[0]
        self.p2_type.anchor.checked = True
        self.p2_type.update()

        self.p1_type.anchor.checked = False
        if self.p2_type.anchor.value == HUMAN:
            self.p1_type.anchor = self.p1_type.container[1]
        else:
            self.p1_type.anchor = self.p1_type.container[0]
        self.p1_type.anchor.checked = True
        self.p1_type.update()

        self.start.update()
        self.draw_box_1()
        self.draw_box_2()
        self.surface.blit(self.start.surface, self.start.rect)

        return SETUP_SURFACE

class Controller:

    __slots__ = ('_window', '_phase', '_state', '_board', '_setup', '_events', '_sidebar', '_repeat', '_p1', '_p2')

    def __init__(self, window):
        self._window = window
        self._events = None
        self._repeat = True
        self._p1     = None
        self._p2     = None
        self._state  = State()
        self._setup  = Setup(window, relative_to=window, position=(HEIGHT, 0))
        self._board  = Board(window, self._state, self._setup, self._p1, self._p2)
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
        while self.repeat:
            # Register events
            self.events = pygame.event.get()

            # Exit in pygame.QUIT event
            for event in self.events:
                if event.type == pygame.QUIT:
                    exit(0)

            if self.phase == SETUP_SURFACE:
                self.board.draw_board()
                self.setup.update(self.events)
            else:
                self.board.update(self.events)

            self.window.blit(self.setup)
            self.window.blit(self.board)
            self.window.update()

            # CLOCK.tick(60)

class Board(Surface):
    """ 
    This class represents the board surface.
    """

    __slots__ = ('_turn', '_setup', '_state', '_window', '_repeat', '_offset', '_limit', '_step', '_linspace', '_p1', '_p2')

    def __init__(self, window, initial_state, setup, p1, p2):
        super().__init__(HEIGHT, HEIGHT, relative_to=window)
        self._setup    = setup
        self._state    = initial_state
        self._window   = window
        self._offset   = 40
        self._limit    = self.height - (self.offset * 2) - 18
        self._step     = int(self.limit / 18)
        self._linspace = [i + self.step for i in range(0, self.width - self.offset, self.step)]
        self._p1       = p1
        self._p2       = p2
        self._turn     = self._p1

    @property
    def p1(self):
        return self._p1

    @property
    def p2(self):
        return self._p2

    @property
    def turn(self):
        return self._turn

    @turn.setter
    def turn(self, value):
        self._turn = value

    @property
    def setup(self):
        return self._setup

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
        self.surface.fill(BOARD_COLOR)
        pygame.draw.line(self.surface, pygame.Color('#8f8f8f'), (self.width-1, 0), (self.width-1, HEIGHT), 1)
        
        for i in range(0, 19):
            # Draw horizontal lines
            ys, xs = self.offset + (i * self.step), self.offset + 0
            ye, xe = self.offset + (i * self.step), self.offset + self.limit
            pygame.draw.line(self.surface, pygame.Color('#000000'), (xs, ys), (xe, ye), 2 if i in (0, 3, 9, 15, 18) else 1)

            # Draw vertical lines
            xs, ys = self.offset + (i * self.step), self.offset + 0
            xe, ye = self.offset + (i * self.step), self.offset + self.limit
            pygame.draw.line(self.surface, pygame.Color('#000000'), (xs, ys), (xe, ye), 2 if i in (0, 3, 9, 15, 18) else 1)

            x, y = -1, -1
            if self.check_hover():
                x, y = pygame.mouse.get_pos()
                y = math.floor((y-16) / self.step)
                x = math.floor((x-16) / self.step)

            # Draw y-coords
            font = fonts.h4_b if y == i else fonts.h4_t
            text = font.render(f'{i}', True, BLACK)
            text_rect = text.get_rect()
            text_rect.center = (self.width - 30, self.linspace[i])
            self.surface.blit(text, text_rect)

            # Draw x-coords
            font = fonts.h4_b if x == i else fonts.h4_t
            text = font.render(f'{"ABCDEFGHIJKLMNOPQRS"[i]}', True, BLACK)
            text_rect = text.get_rect()
            text_rect.center = (self.linspace[i], self.width - 30)
            self.surface.blit(text, text_rect)
        

    def draw_state(self):
        for r, row in enumerate(self.state.state):
            for c, col in enumerate(row):
                if col in ['1', '2']:
                    color = "#ffffff" if col == '1' else "#000000"
                    x = self.linspace[c] + 1
                    y = self.linspace[r] + 1
                    Board.draw_circle(self.surface, x, y, 16, pygame.Color(color))

                    counter = self.state.counts.get((c, r))
                    if counter == None:
                        continue
                    if counter == self.state.counter:
                        count_text = fonts.h5_b.render(f'{counter}', True, (255, 0, 0))

                    if counter == self.state.counter:
                        x = self.linspace[c] + 1
                        y = self.linspace[r] + 1
                        Board.draw_circle(self.surface, x+12, y-12, 5, (255, 255, 0))

                    count_text = fonts.h5_b.render(f'{counter}', True, (0, 0, 0) if col == '1' else (255, 255, 255))
                    count_rect = count_text.get_rect()
                    count_rect.center = (x, y)
                    self.surface.blit(count_text, count_rect)

    def check_hover(self):
        x, y = pygame.mouse.get_pos()
        if x >= self.offset and x <= self.limit + self.offset:
            if y >= self.offset and y <= self.limit + self.offset:
                return True
        return False

    def show_hover(self):
        radius = 16
        color = "#ffffff" if self.turn == self.p1 else "#000000"
        x, y = pygame.mouse.get_pos()
        x = self.linspace[math.floor((x-radius) / self.step)]+1
        y = self.linspace[math.floor((y-radius) / self.step)]+1
        # if math.sqrt((x-nx)**2 + (y-ny)**2) <= 10:
            # x, y = nx + 1, ny + 1
        Board.draw_circle(self.surface, x, y, radius, pygame.Color(color))

        # Show the current count value on the hover piece.
        if isinstance(self.turn, Human):
            color = "#000000" if self.turn == self.p1 else "#ffffff"
            count_text = fonts.h5_b.render(f'{self.state.counter + 1}', True, color)
            count_rect = count_text.get_rect()
            count_rect.center = (x, y)
            self.surface.blit(count_text, count_rect)

        # Return coordinates of the mouse
        return x, y

    def update_board(self, event):
        self.draw_board()
        self.draw_state()
        for event in pygame.event.get():

            if event.type == pygame.QUIT:
                exit(0)

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

                    print(f'({y}, {"ABCDEFGHIJKLMNOPQRS"[x]})')

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
                print(f"({move['coords'][1]}, {'ABCDEFGHIJKLMNOPQRS'[move['coords'][0]]})")

        if isinstance(self.turn, Human) and self.check_hover():
            self.show_hover()
        self.surface.blit(self.surface, (0, 0))

    # def update_sidebar(self):
    #     self.sidebar.update()
    #     self.surface.blit(self.sidebar.surface, (self.board.width, 0))

    def update(self, event):
        self.update_board(event)
        # self.update_sidebar()
        # self.window.blit(self)
        # self.window.update()

    def player_symbol(self):
        if self.turn == self.p1:
            return '1'
        return '2'

    def reset(self):
        self.state.reset()
        self.setup_players()
        self.turn = self.p1
