import math
from pygame import gfxdraw
from surface import Surface
from init import *
from computer import Computer, Player
from components import Button, CheckBoxs
from state      import States, State
import fonts
import fonts

class Setup(Surface):
    """ 
    This class represents the setup surface
    """

    __slots__ = ('_repeat', '_start', '_p1', '_p1_surf', '_p1_type', '_p1_mode', '_p2', '_p2_surf', '_p2_type', '_p2_mode', '_p1', '_p2')

    def __init__(self, *args, **kwargs):
        super().__init__(WIDTH-HEIGHT, HEIGHT, alpha=True, *args, **kwargs)
        self._repeat = True

        self._start = Button("#000000", "#66F587", "START", fonts.h3_t, relative_to=self)
        self._start.position = (self.width / 2 - self._start.width / 2, self.height - 100)
        
        # Player 1 setup surface
        self._p1_surf = Surface(300, 400, (50, 120), self, True)
        self._p1_type = CheckBoxs(
            {HUMAN: 'Human', COMPUTER: 'Computer'},
            position=(0, 50),
            relative_to=self._p1_surf,
            alpha=True
        )
        self._p1_mode = CheckBoxs( 
            {EASY: 'Easy', MEDIUM: 'Medium', HARD: 'Hard'},
            position=(0, self._p1_type.height + 130),
            relative_to=self._p1_surf,
            alpha=True
        )

        # Player 2 setup surface
        self._p2_surf = Surface(300, 400, (320, 120), self, True)
        self._p2_type = CheckBoxs(
            {HUMAN: 'Human', COMPUTER: 'Computer'},
            position=(0, 50),
            relative_to=self._p2_surf,
            alpha=True
        )
        self._p2_mode = CheckBoxs(
            {EASY: 'Easy', MEDIUM: 'Medium', HARD: 'Hard'},
            position=(0, self._p2_type.height + 130),
            relative_to=self._p2_surf,
            alpha=True
        )

        self._p1 = None
        self._p2 = None

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

    __slots__ = ('_left', '_right', '_rff', '_lff', '_states', '_board', '_text', '_restart', '_suggest')

    def __init__(self, states, board, *args, **kwargs):
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

        self._text = {
            'black': fonts.h3_t.render('Black', True, BLACK),
            'white': fonts.h3_t.render('White', True, BLACK),
        }

        self._states = states
        self._board = board

        restart_img = pygame.transform.smoothscale(pygame.image.load('./ressources/images/reload.png'), (50, 50))
        self._restart = Button(
            '#000000', 
            '#31E8DF', 
            restart_img, 
            None, 
            relative_to=self)
        self._restart.position = (self.width - self._restart.width - 30, 30)

        suggest_img = pygame.transform.smoothscale(pygame.image.load('./ressources/images/suggest.png'), (50, 50))
        self._suggest = Button(
            '#000000', 
            '#FFE601', 
            suggest_img, 
            None, 
            relative_to=self)
        self._suggest.position = (self.width - self._suggest.width - 30, self._restart.width + 30)

    @property
    def states(self):
        return self._states

    @property
    def board(self):
        return self._board

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

    @property
    def text(self):
        return self._text

    @property
    def restart(self):
        return self._restart
    
    @property
    def suggest(self):
        return self._suggest

    def update_current_state(self, events):
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

    def update(self, events):
        self.surface.fill(WHITE)
        Board.draw_circle(self.surface, 50, 50, 20, BLACK)
        Board.draw_circle(self.surface, 50, 100, 20, WHITE)
        self.surface.blit(self.text['black'], (90, 32))
        self.surface.blit(self.text['white'], (90, 82))
        if self.board.turn.turn == 1:
            ind_x, ind_y = 50, 50
        else:
            ind_x, ind_y = 50, 100
        Board.draw_circle(self.surface, ind_x, ind_y, 10, pygame.Color('#FFFF00'))

        self.restart.update()
        self.surface.blit(self.restart.surface, self.restart.rect)

        self.suggest.update()
        self.surface.blit(self.suggest.surface, self.suggest.rect)

        self.left.update()
        self.right.update()
        self.lff.update()
        self.rff.update()
        self.surface.blit(self.left.surface, self.left.rect)
        self.surface.blit(self.right.surface, self.right.rect)
        self.surface.blit(self.lff.surface, self.lff.rect)
        self.surface.blit(self.rff.surface, self.rff.rect)

        self.update_current_state(events)


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
    
    @property
    def computer(self):
        return self._computer

    @turn.setter
    def turn(self, value):
        self._turn = value

    @property
    def setup(self):
        return self._setup

    @property
    def states(self):
        return self._states

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
    def finished(self):
        return self._finished
    
    @finished.setter
    def finished(self, value):
        self._finished = value

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
            text_rect.center = (self.width - 25, self.linspace[i])
            self.surface.blit(text, text_rect)

            # Draw x-coords
            font = fonts.h4_b if x == i else fonts.h4_t
            text = font.render(f'{"ABCDEFGHIJKLMNOPQRS"[i]}', True, BLACK)
            text_rect = text.get_rect()
            text_rect.center = (self.linspace[i], self.width - 25)
            self.surface.blit(text, text_rect)
        

    def draw_state(self):
        for r, row in enumerate(self.states.current.state):
            for c, col in enumerate(row):
                if col in (1, 2):
                    color = "#ffffff" if col == 2 else "#000000"
                    x = self.linspace[c] + 1
                    y = self.linspace[r] + 1
                    Board.draw_circle(self.surface, x, y, 16, pygame.Color(color))

                    counter = self.states.current.count.get((c, r))
                    if counter == None:
                        continue
                    if counter == self.states.counter:
                        x = self.linspace[c] + 1
                        y = self.linspace[r] + 1
                        Board.draw_circle(self.surface, x+12, y-12, 5, (255, 255, 0))
                        count_text = fonts.h5_b.render(f'{counter}', True, (255, 0, 0))

                    count_text = fonts.h5_b.render(f'{counter}', True, (0, 0, 0) if col == 2 else (255, 255, 255))
                    count_rect = count_text.get_rect()
                    count_rect.center = (x, y)
                    self.surface.blit(count_text, count_rect)

                elif col == 3:
                    x = self.linspace[c] + 1
                    y = self.linspace[r] + 1
                    Board.draw_circle(self.surface, x, y, 3, pygame.Color('#E83907'))

        if self.states.last == self.states.current and self.states.last.suggestion:
            # Show suggestion only if we are at the last state
            color = "#ffffff99" if self.turn.turn == 2 else "#00000099"
            x = self.linspace[self.states.last.suggestion['move'][0]] + 1
            y = self.linspace[self.states.last.suggestion['move'][1]] + 1
            Board.draw_circle(self.surface, x, y, 16, pygame.Color(color))

    def check_hover(self):
        x, y = pygame.mouse.get_pos()
        if x >= self.offset and x <= self.limit + self.offset:
            if y >= self.offset and y <= self.limit + self.offset:
                return True
        return False

    def show_hover(self):
        radius = 16
        color = "#ffffff" if self.turn == self.p2 else "#000000"
        x, y = pygame.mouse.get_pos()
        x = self.linspace[math.floor((x-radius) / self.step)]+1
        y = self.linspace[math.floor((y-radius) / self.step)]+1
        # if math.sqrt((x-nx)**2 + (y-ny)**2) <= 10:
        #     x, y = nx + 1, ny + 1
        Board.draw_circle(self.surface, x, y, radius, pygame.Color(color))

        # Show the current count value on the hover piece.
        if self.turn.player == HUMAN:
            color = "#000000" if self.turn == self.p2 else "#ffffff"
            count_text = fonts.h5_b.render(f'{self.states.counter + 1}', True, color)
            count_rect = count_text.get_rect()
            count_rect.center = (x, y)
            self.surface.blit(count_text, count_rect)

        # Return coordinates of the mouse
        return x, y

    def update(self, events):

        # Ajust the index of the current state.
        for event in events:
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    if self.states.index > 0:
                        self.states.index -= 1
                    elif self.states.index == -1:
                        self.states.index = self.states.counter - 1
                elif event.key == pygame.K_RIGHT:
                    if self.states.index == -1:
                        continue
                    elif self.states.index < self.states.counter:
                        self.states.index += 1
                        if self.states.index == self.states.counter:
                            self.states.index = -1
                elif event.key == pygame.K_UP:
                    self.states.index = -1
                elif event.key == pygame.K_DOWN:
                    self.states.index = 0

        self.draw_board()
        self.draw_state()

        # Not used yet
        if self.finished:
            return

        # Human turn
        if self.turn.player == HUMAN:
            if self.check_hover():
                self.show_hover()

            pos = None
            if not self.computer.expecting:
                for event in events:
                    if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                        # Get the current position of the mouse and map the
                        # coordinantes to index the board
                        pos = event.pos

                if pos and self.check_hover() and self.states.index == -1:
                    # 16 is the diameter of the pieces
                    x = math.floor((pos[0]-16) / self.step)
                    y = math.floor((pos[1]-16) / self.step)

                    # print()
                    # if self.states.last.state[y][x] == '0':
                        # Send coords to the process and want for responce
                        # only if the position does not corresponde to an
                        # illegal move or is not already occupied.
                    self.computer.send(f'M\n{x} {y}\n')
            else:
                # Process the received output
                self.computer.expecting = True
                resp = self.computer.next_move()
                if resp:
                    if isinstance(resp, tuple) and resp[0] == 0: # No winner yet
                        print(f'Human[{self.turn.turn}]', resp[1]['time'], resp[1]['move'])
                        print(resp)
                        self.states.add(State(**resp[1]))
                        self.turn = self.p1 if self.turn == self.p2 else self.p2
                        self.computer.expecting = False
                        print('turn:', self.turn.turn)

                    elif isinstance(resp, tuple) and resp[0] in (1, 2):
                        self.states.add(State(**resp[1]))
                        print(f'Player {resp[0]} wins!')
                        self.finished = True

                    elif isinstance(resp, tuple) and resp[0] == 3:
                        self.states.last.suggestion = resp[1]
                        self.computer.expecting = False

                    elif resp == 4:
                        self.computer.expecting = False

                    elif resp == 5:
                        self.finished = True

                    else:
                        return

        elif self.turn.player == COMPUTER:
            # Process the received output
            self.computer.expecting = True
            resp = self.computer.next_move()
            if resp:
                if isinstance(resp, tuple) and resp[0] == 0: # No winner yet
                    print(f'Computer[{self.turn.turn}]', resp[1]['time'], resp[1]['move'])
                    self.states.add(State(**resp[1]))
                    self.turn = self.p1 if self.turn == self.p2 else self.p2
                    self.computer.expecting = False
                elif isinstance(resp, tuple) and resp[0] in (1, 2): # Winner found
                    self.states.add(State(**resp[1]))
                    print(f'Player {resp[0]} wins!')
                    self.finished = True
                elif resp == 4:
                    self.finished = True

    def reset(self):
        self.state.reset()
        self.setup_players()
        self.turn = self.p1

class Game:
     
    __slots__ = ('_window', '_board', '_stats', '_states', '_setup', '_computer', '_p1', '_p2')

    def __init__(self, window, setup, *args, **kwargs):
        self._window = window
        self._states = States()
        self._setup = setup
        self._stats = None
        self._board = None
        self._computer = None
        self._p1 = None
        self._p2 = None

    @property
    def window(self):
        return self._window

    @property
    def setup(self):
        return self._setup

    @property
    def stats(self):
        return self._stats
    
    @stats.setter
    def stats(self, obj: Stats):
        self._stats = obj
    
    @property
    def states(self):
        return self._states

    @property
    def board(self):
        return self._board

    @board.setter
    def board(self, obj: Board):
        self._board = obj

    @property
    def computer(self):
        return self._computer
    
    @computer.setter
    def computer(self, obj: Computer):
        self._computer = obj

    @property
    def p1(self):
        return self._p1

    @property
    def p2(self):
        return self._p2
    
    @p1.setter
    def p1(self, obj: Player):
        self._p1 = obj

    @p2.setter
    def p2(self, obj: Player):
        self._p2 = obj

    def setup_game(self):
        """
        Players and board setup for a new game
        """
        p1_type = TYPES[self.setup.p1_type.anchor.value - 1]
        p1_diff = MODES[self.setup.p1_mode.anchor.value - 1]
        p2_type = TYPES[self.setup.p2_type.anchor.value - 1]
        p2_diff = MODES[self.setup.p2_mode.anchor.value - 1]

        args = [
            f'--p1_type={p1_type}', f'--p1_diff={p1_diff}',
            f'--p2_type={p2_type}', f'--p2_diff={p2_diff}'
        ]

        self.p1 = Player(self.setup.p1_type.anchor.value, 1)
        self.p2 = Player(self.setup.p2_type.anchor.value, 2)

        self.computer = Computer(*args)
        self.board = Board(self.states, self.setup, self.p1, self.p2, self.computer)
        self.stats = Stats(self.states, self.board, relative_to=self.window, position=(HEIGHT, 0))

    def loop(self):
        self.setup_game()
        self.computer.start()

        while True:
            events = pygame.event.get()
            for event in events:
                if event.type == pygame.QUIT:
                    self.computer.stop()
                    exit(0)
                if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                    if self.stats.restart.clicked():
                        self.computer.stop()
                        return
                    if self.board.turn.player == HUMAN:
                        if self.stats.suggest.clicked() and self.board.states.last.suggestion == None:
                            self.stats.suggest.pressed = False
                            self.computer.send('S')
                    else:
                        self.stats.suggest.disable()

            self.stats.update(events)
            self.board.update(events)
            self.window.blit(self.board)
            self.window.blit(self.stats)
            self.window.update()
            CLOCK.tick(60)
