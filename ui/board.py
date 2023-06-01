import math
from pygame import gfxdraw
from surface import Surface
from init import *
from computer import Computer, Human
import asyncio

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
    def repeat(self):
        return self._repeat

    @repeat.setter
    def repeat(self, value):
        self._repeat = value

    def draw_box_1(self):
        header = fonts.h3_r.render('Black', True, BLACK_COLOR)
        header_rect = header.get_rect()
        header_rect.topleft = (70, 0)

        self.p1_surf.surface.blit(header, header_rect, special_flags=pygame.BLEND_RGBA_MAX)

        # Update type checkboxs
        self.p1_type.update()
        self.p1_surf.surface.blit(self.p1_type.surface, self.p1_type.rect)

        # Blit mode surface
        mode = fonts.h3_r.render('Level', True, BLACK_COLOR)
        mode_rect = header.get_rect()
        mode_rect.topleft = (70, 170)

        self.p1_mode.update()
        self.p1_surf.surface.blit(mode, mode_rect, special_flags=pygame.BLEND_RGBA_MAX)
        self.p1_surf.surface.blit(self.p1_mode.surface, self.p1_mode.rect)

        # Blit first player surface on the window
        self.surface.blit(self.p1_surf.surface, self.p1_surf.rect)

    def draw_box_2(self):
        header = fonts.h3_r.render('White', True, BLACK_COLOR)
        header_rect = header.get_rect()
        header_rect.topleft = (70, 0)

        self.p2_surf.surface.blit(header, header_rect, special_flags=pygame.BLEND_RGBA_MAX)

        # Update type checkboxs
        self.p2_type.update()
        self.p2_surf.surface.blit(self.p2_type.surface, self.p2_type.rect)

        # Blit mode surface
        mode = fonts.h3_r.render('Level', True, BLACK_COLOR)
        mode_rect = header.get_rect()
        mode_rect.topleft = (70, 170)

        self.p2_mode.update()
        self.p2_surf.surface.blit(mode, mode_rect, special_flags=pygame.BLEND_RGBA_MAX)
        self.p2_surf.surface.blit(self.p2_mode.surface, self.p2_mode.rect)

        # Blit first player surface on the window
        self.surface.blit(self.p2_surf.surface, self.p2_surf.rect)

    def update(self, events):
        self.surface.fill(WHITE)

        # Title
        middle = fonts.h3_b.render('Game Setup', True, BLACK_COLOR)
        middle_rect = middle.get_rect()
        middle_rect.center = (int(self.width / 2), 60)

        type_checkboxs = [*self.p1_type.container, *self.p2_type.container]
        mode_checkboxs = [*self.p1_mode.container, *self.p2_mode.container]

        for event in events:
            if event.type == pygame.QUIT:
                exit(0)

            if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                if self.start.clicked():
                    self.start.pressed = False
                    return BOARD_SURFACE

                for box in type_checkboxs:
                    box.check_clicked()
                    box.update()
                for box in mode_checkboxs:
                    box.check_clicked()
                    box.update()
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_RETURN:
                self.start.pressed = False # Just in case it's not reseted
                return BOARD_SURFACE
                

        if self.p1_type.anchor.value == 2:
            self.p1_mode.active = True
        else:
            self.p1_mode.active = False
        
        if self.p2_type.anchor.value == 2:
            self.p2_mode.active = True
        else:
            self.p2_mode.active = False

        self.draw_box_1()
        self.draw_box_2()
        self.start.update()
        self.surface.blit(self.start.surface, self.start.rect)
        self.surface.blit(middle, middle_rect)

        if self.start.pressed:
            self.start.pressed = False
            return BOARD_SURFACE
        return SETUP_SURFACE

class Stats(Surface):

    __slots__ = ('_left', '_right', '_rff', '_lff', '_states')

    def __init__(self, states, *args, **kwargs):
        super().__init__(WIDTH-HEIGHT, HEIGHT, *args, **kwargs)
        
        # Load images for left and right buttons
        r_img = pygame.transform.smoothscale(pygame.image.load('./ressources/images/right.png'), (50, 50))
        l_img = pygame.transform.smoothscale(pygame.image.load('./ressources/images/right.png'), (50, 50))
        l_img = pygame.transform.rotate(l_img, 180)
        rff_img = pygame.transform.smoothscale(pygame.image.load('./ressources/images/rff.png'), (50, 50))
        lff_img = pygame.transform.smoothscale(pygame.image.load('./ressources/images/rff.png'), (50, 50))
        lff_img = pygame.transform.rotate(lff_img, 180)

        self._left  = Button('#ffffff', '#ffffff', l_img, None, relative_to=self)
        self._right = Button('#ffffff', '#ffffff', r_img, None, relative_to=self)
        self._lff   = Button('#ffffff', '#ffffff', lff_img, None, relative_to=self)
        self._rff   = Button('#ffffff', '#ffffff', rff_img, None, relative_to=self)
        self._left.position  = (self.width / 2 - self.left.width, self.height - 100)
        self._right.position = (self.width / 2, self.height - 100)
        self._lff.position   = (self.width / 2 - self.left.width * 2, self.height - 100)
        self._rff.position   = (self.width / 2 + self.right.width, self.height - 100)

        self._states = states

    @property
    def states(self):
        return self._states

    def check_hover(self):
        if self.abs_rect.collidepoint(pygame.mouse.get_pos()):
            return True
        return False

    @property
    def left(self):
        return self._left
    
    @property
    def right(self):
        return self._right

    @property
    def lff(self):
        return self._lff
    
    @property
    def rff(self):
        return self._rff

    def update(self, events):
        self.surface.fill(WHITE)
        self.left.update()
        self.right.update()
        self.lff.update()
        self.rff.update()

        for event in events:
            if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                if self.left.clicked():
                    if self.states.index > 0:
                        self.states.index -= 1
                    elif self.states.index == -1:
                        self.states.index = self.states.counter - 1
                    self.left.pressed = False
                elif self.right.clicked():
                    if self.states.index < self.states.counter and self.states.index != -1:
                        self.states.index += 1
                        if self.states.index == self.states.counter:
                            self.states.index = -1
                    self.right.pressed = False
                elif self.rff.clicked():
                    self.states.index = -1
                    self.rff.pressed = False
                elif self.lff.clicked():
                    self.states.index = 0
                    self.lff.pressed = False


        self.surface.blit(self.left.surface, self.left.rect)
        self.surface.blit(self.right.surface, self.right.rect)
        self.surface.blit(self.lff.surface, self.lff.rect)
        self.surface.blit(self.rff.surface, self.rff.rect)

class Board(Surface):
    """ 
    This class represents the board surface.
    """

    __slots__ = ('_turn', '_setup', '_states', '_computer', '_repeat', '_offset', '_limit', '_step', '_linspace', '_p1', '_p2', '_finished')

    def __init__(self, states, setup, p1, p2, computer, *args, **kwargs):
        super().__init__(HEIGHT, HEIGHT, *args, **kwargs)
        self._setup    = setup
        self._states   = states
        self._offset   = 40
        self._limit    = self.height - (self.offset * 2) - 18
        self._step     = int(self.limit / 18)
        self._linspace = [i + self.step for i in range(0, self.width - self.offset, self.step)]
        self._p1       = p1
        self._p2       = p2
        self._turn     = self._p1
        self._computer = computer
        self._finished = False

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

    def check_hover(self):
        x, y = pygame.mouse.get_pos()
        if x >= self.offset and x <= self.limit + self.offset:
            if y >= self.offset and y <= self.limit + self.offset:
                return True
        return False

    def show_hover(self):
        radius = 13
        x, y = pygame.mouse.get_pos()
        # color = "#ffffff" if self.turn == self.p1 else "#000000"
        color = "#FFFF00"
        nx = self.linspace[math.floor((x-radius) / self.step)]
        ny = self.linspace[math.floor((y-radius) / self.step)]
        if math.sqrt((x-nx)**2 + (y-ny)**2) <= radius:
            x, y = nx + 1, ny + 1
        Board.draw_circle(self.board.surface, x, y, radius, pygame.Color(color))
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
            if self.p1:
                self.p1.stop()

            # Need to run in parallel
            self.p1 = Computer('--black')
            self.p1.start()

            # if restarting failed, kill everything
            if self.p1 == None:
                self.window.quit = True
                return
        else:
            self.p1 = Human()

        if self.setup.p2_type.anchor.value == COMPUTER:
            # restart the bot process
            if self.p2:
                self.p2.stop()

            # Need to run in parallel
            self.p2 = Computer('--white')
            self.p2.start()

            # if restarting failed, kill everything
            if self.p2 == None:
                self.p2.stop()
                self.window.quit = True
                return
        else:
            self.p2 = Human()

    def loop(self):
        self.setup_players()
        self.turn = self.p1

        print('p1', self.setup.p1_type.anchor.value)
        print('p2', self.setup.p2_type.anchor.value)
        
        self.update()
        while self.repeat:
            for event in pygame.event.get():

                if event.type == pygame.QUIT:
                    self.window.quit = True
                    self.repeat = False
                    break

                if isinstance(self.turn, Human):
                    if event.type == pygame.MOUSEBUTTONUP and event.button == 1 and self.check_hover():
                        x, y = pygame.mouse.get_pos()
                        x = math.floor((x-16) / self.step)
                        y = math.floor((y-16) / self.step)

                        # Update the value of the board position to 1 or 2 according to the current turn
                        if self.state.state[y][x] == '0':
                            self.state.update(x, y, self.player_symbol())
                            self.turn = self.p1 if self.turn == self.p2 else self.p2
                            if isinstance(self.turn, Computer):
                                self.turn.process.send(f'{y} {"ABCDEFGHIJKLMNOPQRS"[x]}\n')
                else:
                    exp = self.turn.expect(['Enter move: \n'])
                    if exp == 0:
                        move = self.turn.next_move()
                        self.state.update(move['coords'][0], move['coords'][1], self.player_symbol())
                        self.turn = self.p1 if self.turn == self.p2 else self.p2

            if self.window.quit == False:
                self.update()

            CLOCK.tick(60)

        # # Reset the turns: Need to check if the turn is computer to close it's process
        # self.p1 = None
        # self.p2 = None