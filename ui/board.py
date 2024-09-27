import math
import os
from surface import Surface
from init import *
from computer import Computer, Player
from components import Button, CheckBoxs, ColorPallet, draw_circle
from state import States, State, HistoryTable
import fonts


class Setup(Surface):
    """
    This class represents the setup surface
    """

    __slots__ = (
        "_repeat",
        "_start",
        "_p1",
        "_p1_surf",
        "_p1_type",
        "_p1_mode",
        "_p2",
        "_p2_surf",
        "_p2_type",
        "_p2_mode",
        "_p1",
        "_p2",
        "_rules",
        "_rules_surf",
        "_sizes",
        "_sizes_surf",
        "_sizes_dropdown",
        "_pallet",
        "_themes",
    )

    def __init__(self, pallet, *args, **kwargs):
        super().__init__(WIDTH - HEIGHT, HEIGHT, alpha=True, *args, **kwargs)
        self._repeat = True
        self._pallet = pallet
        self._start = Button(
            self.pallet.foreground,
            self.pallet.secondary,
            "START",
            fonts.h4_b,
            height=50,
            expand=True,
            relative_to=self,
        )
        self._start.position = (0, self.height - self._start.height)

        # Player 1 setup surface
        self._p1_surf = Surface(300, 400, (50, 70), self, True)
        self._p1_type = CheckBoxs(
            self.pallet,
            {HUMAN: "Human", COMPUTER: "CPU"},
            position=(0, 40),
            relative_to=self._p1_surf,
            alpha=True,
        )
        self._p1_mode = CheckBoxs(
            self.pallet,
            {EASY: "Easy", MEDIUM: "Medium", HARD: "Hard"},
            position=(0, self._p1_type.height + 110),
            relative_to=self._p1_surf,
            alpha=True,
        )

        # Player 2 setup surface
        self._p2_surf = Surface(300, 400, (320, 70), self, True)
        self._p2_type = CheckBoxs(
            self.pallet,
            {HUMAN: "Human", COMPUTER: "CPU"},
            position=(0, 40),
            relative_to=self._p2_surf,
            alpha=True,
        )
        self._p2_mode = CheckBoxs(
            self.pallet,
            {EASY: "Easy", MEDIUM: "Medium", HARD: "Hard"},
            position=(0, self._p2_type.height + 110),
            relative_to=self._p2_surf,
            alpha=True,
        )

        self._rules_surf = Surface(self.width - 50, 190, (50, 480), self, True)
        self._rules = CheckBoxs(
            self.pallet,
            {STANDARD: "Standard", LONG_PRO: "Long Pro", PRO: "Pro"},
            position=(0, 0),
            relative_to=self.rules_surf,
            alpha=True,
        )

        self._sizes_surf = Surface(self.width - 50, 190, (320, 480), self, True)
        self._sizes = CheckBoxs(
            self.pallet,
            {SIZE_19: "19x19", SIZE_15: "15x15", SIZE_13: "13x13"},
            position=(0, 0),
            relative_to=self._sizes_surf,
            alpha=True,
        )

        coords = [(100, 690), (self.width // 2 - 45, 690), (self.width - 200, 690)]
        self._themes = []
        for i in range(3):
            self._themes.append(Surface(90, 30, position=coords[i], relative_to=self))

        self._p1 = None
        self._p2 = None

    @property
    def themes(self):
        return self._themes

    @property
    def pallet(self):
        return self._pallet

    @property
    def rules(self):
        return self._rules

    @property
    def rules_surf(self):
        return self._rules_surf

    @property
    def sizes(self):
        return self._sizes

    @property
    def sizes_surf(self):
        return self._sizes_surf

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
        header = fonts.h4_b.render("Black", True, self.pallet.foreground)
        header_rect = header.get_rect()
        header_rect.topleft = (0, 0)

        self.p1_surf.surface.blit(
            header, header_rect, special_flags=pygame.BLEND_RGBA_MAX
        )

        # Update type checkboxs
        self.p1_type.update()
        self.p1_surf.surface.blit(self.p1_type.surface, self.p1_type.rect)

        self.p1_mode.update()
        self.p1_surf.surface.blit(self.p1_mode.surface, self.p1_mode.rect)

        # Blit first player surface on the window
        self.surface.blit(self.p1_surf.surface, self.p1_surf.rect)

    def draw_box_2(self):
        header = fonts.h4_b.render("White", True, self.pallet.foreground)
        header_rect = header.get_rect()
        header_rect.topleft = (0, 0)

        self.p2_surf.surface.blit(
            header, header_rect, special_flags=pygame.BLEND_RGBA_MAX
        )

        # Update type checkboxs
        self.p2_type.update()
        self.p2_surf.surface.blit(self.p2_type.surface, self.p2_type.rect)

        self.p2_mode.update()
        self.p2_surf.surface.blit(self.p2_mode.surface, self.p2_mode.rect)

        # Blit first player surface on the window
        self.surface.blit(self.p2_surf.surface, self.p2_surf.rect)

    def draw_rules(self):
        self.rules.update()
        self.rules_surf.surface.blit(self.rules.surface, self.rules.rect)
        self.surface.blit(self.rules_surf.surface, self.rules_surf.rect)

    def draw_sizes(self):
        self.sizes.update()
        self.sizes_surf.surface.blit(self.sizes.surface, self.sizes.rect)
        self.surface.blit(self.sizes_surf.surface, self.sizes_surf.rect)

    def draw_titles(self):
        black_level = fonts.h4_b.render("Black Level", True, self.pallet.foreground)
        white_level = fonts.h4_b.render("White Level", True, self.pallet.foreground)

        black_level_rect = black_level.get_rect()
        white_level_rect = white_level.get_rect()
        black_level_rect.topleft = (50, 220)
        white_level_rect.topleft = (320, 220)

        rules = fonts.h4_b.render("Game Rules", True, self.pallet.foreground)
        rules_rect = rules.get_rect()
        rules_rect.topleft = (50, 430)

        sizes = fonts.h4_b.render("Board Size", True, self.pallet.foreground)
        sizes_rect = rules.get_rect()
        sizes_rect.topleft = (320, 430)

        self.surface.blit(black_level, black_level_rect)
        self.surface.blit(white_level, white_level_rect)
        self.surface.blit(rules, rules_rect)
        self.surface.blit(sizes, sizes_rect)

    def draw_themes(self):
        themes_title = fonts.h3_b.render("Themes", True, self.pallet.foreground)
        themes_title_rect = themes_title.get_rect()
        themes_title_rect.center = (self.width // 2, 650)
        self.surface.blit(themes_title, themes_title_rect)
        coords = [(100, 730), (self.width // 2 - 45, 730), (self.width - 200, 730)]
        for i, theme_surf in enumerate(self.themes):
            theme_surf.surface.fill(self.pallet.background)
            draw_circle(theme_surf.surface, 15, 15, 10, self.pallet.pallets[i][0])
            draw_circle(theme_surf.surface, 45, 15, 10, self.pallet.pallets[i][1])
            draw_circle(theme_surf.surface, 75, 15, 10, self.pallet.pallets[i][3])
            if self.pallet.pallet == self.pallet.pallets[i]:
                surf = Surface(90, 2, position=coords[i], relative_to=self)
                surf.surface.fill(self.pallet.accent_dimmed)
                self.surface.blit(surf.surface, surf.rect)
            if theme_surf.check_hover():
                surf = Surface(90, 2, position=coords[i], relative_to=self)
                surf.surface.fill(self.pallet.accent)
                self.surface.blit(surf.surface, surf.rect)
            self.surface.blit(theme_surf.surface, theme_surf.rect)

    def update(self, events):
        self.surface.fill(self.pallet.background)

        # Title
        middle = fonts.h3_b.render("Game Setup", True, self.pallet.foreground)
        middle_rect = middle.get_rect()
        middle_rect.center = (int(self.width / 2), 30)

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
                for box in self.rules.container:
                    box.check_clicked()
                    box.update()
                for box in self.sizes.container:
                    box.check_clicked()
                    box.update()
                for i, theme in enumerate(self.themes):
                    if theme.check_hover():
                        self.pallet.pallet = i
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_RETURN:
                self.start.pressed = False  # Just in case it's not reseted
                return BOARD_SURFACE

        if self.p1_type.anchor.value == 2:
            # self.p2_type.anchor = self.p2_type.container[0]
            self.p1_mode.active = True
        else:
            # self.p2_type.anchor = self.p2_type.container[1]
            self.p1_mode.active = False

        if self.p2_type.anchor.value == 2:
            # self.p1_type.anchor = self.p1_type.container[0]
            self.p2_mode.active = True
        else:
            self.p2_mode.active = False

        self.draw_titles()
        self.draw_box_1()
        self.draw_box_2()
        self.draw_rules()
        self.draw_sizes()
        self.draw_themes()
        self.start.update()
        self.surface.blit(self.start.surface, self.start.rect)
        self.surface.blit(middle, middle_rect)
        if self.start.pressed:
            self.start.pressed = False
            return BOARD_SURFACE
        return SETUP_SURFACE


class Stats(Surface):

    __slots__ = (
        "_left",
        "_right",
        "_rff",
        "_lff",
        "_states",
        "_board",
        "_text",
        "_restart",
        "_suggest",
        "_player_header",
        "_versus_message",
        "_winner",
        "_history",
        "_history_title",
        "_pallet",
        "_winner",
    )

    script_dir = os.path.dirname(os.path.abspath(__file__))

    def __init__(self, pallet, states, board, winner=None, *args, **kwargs):
        super().__init__(WIDTH - HEIGHT, HEIGHT, *args, **kwargs)

        self._pallet = pallet
        suggest_text = fonts.h5_b.render("Suggestion", True, self.pallet.black)
        self._suggest = Button(
            self.pallet.black,
            "#FFBC24",
            suggest_text,
            None,
            height=50,
            relative_to=self,
        )
        self._suggest.position = (0, self.height - self.suggest.height)

        restart_text = fonts.h5_b.render("Restart", True, self.pallet.black)
        self._restart = Button(
            self.pallet.black,
            "#008CDB",
            restart_text,
            None,
            width=self.suggest.width,
            height=50,
            relative_to=self,
        )
        self._restart.position = (
            self.width - self.restart.width,
            self.height - self.restart.height,
        )

        # Load images for left and right buttons
        # r_img = pygame.transform.smoothscale(
        #     pygame.image.load("./ressources/images/right.png"), (30, 30)
        # )
        r_img = self.load_images("ressources/images/right.png", (30, 30))
        l_img = self.load_images("ressources/images/right.png", (30, 30))
        l_img = pygame.transform.rotate(l_img, 180)
        # rff_img = pygame.transform.smoothscale(
        #     pygame.image.load("./ressources/images/rff.png").convert_alpha(), (30, 30)
        # )
        rff_img = self.load_images("ressources/images/rff.png", (30, 30))
        lff_img = self.load_images("ressources/images/rff.png", (30, 30))
        lff_img = pygame.transform.rotate(lff_img, 180)

        self._left = Button(
            self.pallet.white,
            self.pallet.primary,
            l_img,
            None,
            width=65,
            height=50,
            hover_color=GRAY_3,
            relative_to=self,
        )
        self._right = Button(
            self.pallet.white,
            self.pallet.primary,
            r_img,
            None,
            width=65,
            height=50,
            hover_color=GRAY_3,
            relative_to=self,
        )
        self._lff = Button(
            self.pallet.white,
            self.pallet.primary,
            lff_img,
            None,
            width=65,
            height=50,
            hover_color=GRAY_3,
            relative_to=self,
        )
        self._rff = Button(
            self.pallet.white,
            self.pallet.primary,
            rff_img,
            None,
            width=65,
            height=50,
            hover_color=GRAY_3,
            relative_to=self,
        )
        self._left.position = (
            self.width / 2 - self.left.width,
            self.height - self.left.height,
        )
        self._right.position = (self.width / 2, self.height - self.left.height)
        self._lff.position = (self.suggest.width, self.height - self.left.height)
        self._rff.position = (
            self.restart.position[0] - self.rff.width,
            self.height - self.left.height,
        )

        self._states = states
        self._board = board

        self._versus_message = fonts.h3_b.render("VS", True, self.pallet.foreground)
        self._history_title = fonts.h4_b.render("History", True, self.pallet.foreground)

        self._history = HistoryTable(
            self.pallet, self.states, self.width, 560, relative_to=self
        )
        self._history.position = (0, 190)

    def load_images(self, path, size: tuple):
        path = os.path.join(self.script_dir, path)
        return pygame.transform.smoothscale(
            pygame.image.load(path).convert_alpha(), size
        )

    @property
    def pallet(self):
        return self._pallet

    @property
    def history(self):
        return self._history

    @property
    def states(self):
        return self._states

    @property
    def board(self):
        return self._board

    @property
    def versus_message(self):
        return self._versus_message

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
    def restart(self):
        return self._restart

    @property
    def suggest(self):
        return self._suggest

    @property
    def history_title(self):
        return self._history_title

    def update_current_state(self, events):
        if self.history.selected_slot:
            self.states.index = self.history.selected_slot + 1
        for event in events:
            if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                if self.left.clicked():
                    self.history.selected_slot = None
                    if self.states.index > 0:
                        self.states.index -= 1
                    elif self.states.index == -1:
                        self.states.index = self.states.counter - 1
                    self.left.pressed = False
                elif self.right.clicked():
                    self.history.selected_slot = None
                    if (
                        self.states.index < self.states.counter
                        and self.states.index != -1
                    ):
                        self.states.index += 1
                        if self.states.index == self.states.counter:
                            self.states.index = -1
                    self.right.pressed = False
                elif self.rff.clicked():
                    self.history.selected_slot = None
                    self.states.index = -1
                    self.rff.pressed = False
                elif self.lff.clicked():
                    self.history.selected_slot = None
                    self.states.index = 0
                    self.lff.pressed = False

    def update(self, events):
        self.surface.fill(self.pallet.background)

        history_rect = self.history_title.get_rect()
        history_rect.center = (self.width // 2, 160)
        self.surface.blit(self.history_title, history_rect)

        if self.board.turn.turn == 1:
            ind_x, ind_y = self.width // 4, 80
        else:
            ind_x, ind_y = 3 * self.width // 4, 80

        draw_circle(self.surface, ind_x, ind_y, 60, self.pallet.accent)
        draw_circle(self.surface, self.width // 4, 80, 50, self.pallet.black)
        draw_circle(self.surface, 3 * self.width // 4, 80, 50, self.pallet.white)

        self.surface.blit(
            self.versus_message,
            (self.width / 2 - self.versus_message.get_rect()[2] / 2, 65),
        )

        if self.states.states[-1].captures == None:
            white_score, black_score = 0, 0
        else:
            black_score = self.states.states[-1].captures[0]
            white_score = self.states.states[-1].captures[1]
        black_score_text = fonts.h2_b.render(f"{black_score}", True, self.pallet.white)
        white_score_text = fonts.h2_b.render(f"{white_score}", True, self.pallet.black)

        black_score_text_rect = black_score_text.get_rect()
        black_score_text_rect.center = (self.width // 4, 80)

        white_score_text_rect = white_score_text.get_rect()
        white_score_text_rect.center = (3 * self.width // 4, 80)
        self.surface.blit(black_score_text, black_score_text_rect)
        self.surface.blit(white_score_text, white_score_text_rect)

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

        self.history.update(events)
        self.surface.blit(self.history.surface, self.history.rect)

        self.update_current_state(events)


class Board(Surface):
    """
    This class represents the board surface.
    """

    __slots__ = (
        "_turn",
        "_setup",
        "_states",
        "_computer",
        "_size",
        "_repeat",
        "_offset",
        "_limit",
        "_step",
        "_linspace",
        "_p1",
        "_p2",
        "_finished",
        "_pallet",
        "_winner",
    )

    def __init__(
        self, pallet, states, setup, p1, p2, computer, size=15, *args, **kwargs
    ):
        super().__init__(HEIGHT, HEIGHT, *args, **kwargs)
        self._pallet = pallet
        self._setup = setup
        self._states = states
        self._offset = 50
        self._size = size
        self._step = int((self.height - self.offset) / self.size)
        self._limit = self.offset + self.step * (self.size - 1)
        self._linspace = [i for i in range(self.offset, self.limit + 1, self.step)]
        self._p1 = p1
        self._p2 = p2
        self._turn = self._p1
        self._computer = computer
        self._finished = False

    @property
    def pallet(self):
        return self._pallet

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

    @limit.setter
    def limit(self, value):
        self._limit = value

    @property
    def linspace(self):
        return self._linspace

    @property
    def finished(self):
        return self._finished

    @property
    def size(self):
        return self._size

    @finished.setter
    def finished(self, value):
        self._finished = value

    @property
    def winner(self):
        return self._winner

    @winner.setter
    def winner(self, value):
        self._winner = value

    def draw_board(self):
        self.surface.fill(BOARD_COLOR)
        pygame.draw.line(
            self.surface, GRAY_1, (self.width - 1, 0), (self.width - 1, HEIGHT), 1
        )

        for i in range(0, self.size):
            # Draw vertical lines
            ys, xs = self.offset + (i * self.step), self.offset
            ye, xe = self.offset + (i * self.step), self.limit
            pygame.draw.line(
                self.surface,
                self.pallet.black,
                (xs, ys),
                (xe, ye),
                2 if i in (0, self.size - 1) else 1,
            )

            # Draw horizontal lines
            xs, ys = self.offset + (i * self.step), self.offset
            xe, ye = self.offset + (i * self.step), self.limit
            pygame.draw.line(
                self.surface,
                self.pallet.black,
                (xs, ys),
                (xe, ye),
                2 if i in (0, self.size - 1) else 1,
            )

            x, y = -1, -1
            if self.check_hover():
                x, y = pygame.mouse.get_pos()
                x = self.linspace[
                    math.floor((x - self.offset + self.step / 2) / self.step)
                ]
                y = self.linspace[
                    math.floor((y - self.offset + self.step / 2) / self.step)
                ]

            # Draw y-coords
            font = fonts.h5_b if y == (i * self.step) + self.offset else fonts.h5_t
            text = font.render(f"{i+1}", True, self.pallet.black)
            text_rect = text.get_rect()
            text_rect.center = (25, self.offset + (i * self.step))
            self.surface.blit(text, text_rect)

            # Draw x-coords
            font = fonts.h5_b if x == (i * self.step) + self.offset else fonts.h5_t
            text = font.render(f'{"ABCDEFGHIJKLMNOPQRS"[i]}', True, self.pallet.black)
            text_rect = text.get_rect()
            text_rect.center = (self.offset + (i * self.step), 25)
            self.surface.blit(text, text_rect)

    def draw_state(self):
        radius = self.step // 2 - 5
        for r, row in enumerate(self.states.current.state):
            for c, col in enumerate(row):
                if col in (1, 2):
                    color = self.pallet.white if col == 2 else self.pallet.black
                    x = self.offset + c * self.step
                    y = self.offset + r * self.step
                    draw_circle(self.surface, x, y, radius, color)

                    counter = self.states.current.count.get((c, r))
                    if counter == None:
                        continue
                    if counter == self.states.counter:
                        x = self.offset + c * self.step
                        y = self.offset + r * self.step
                        draw_circle(
                            self.surface,
                            x + self.step // 2 - 10,
                            y - self.step // 2 + 10,
                            5,
                            (255, 255, 0),
                        )

                    font = fonts.h6_b if self.size > 15 else fonts.h5_b
                    count_text = font.render(
                        f"{counter}",
                        True,
                        self.pallet.black if col == 2 else self.pallet.white,
                    )
                    count_rect = count_text.get_rect()
                    count_rect.center = (x, y)
                    self.surface.blit(count_text, count_rect)

                elif col == 3:
                    x = self.offset + c * self.step
                    y = self.offset + r * self.step
                    draw_circle(self.surface, x, y, 3, pygame.Color("#E83907"))

                elif col == 4:
                    x = self.offset + c * self.step
                    y = self.offset + r * self.step
                    draw_circle(self.surface, x, y, 3, pygame.Color("#00ff00"))

        if self.states.last == self.states.current and self.states.last.suggestion:
            # Show suggestion only if we are at the last state
            color = "#ffffff88" if self.turn.turn == 2 else "#00000088"
            x = self.linspace[self.states.last.suggestion["move"][0]] + 1
            y = self.linspace[self.states.last.suggestion["move"][1]] + 1
            draw_circle(self.surface, x, y, radius, pygame.Color(color))

        score = fonts.h4_t.render(f"Score: {self.states.current.score}", True, BLACK)
        score_rect = score.get_rect()
        score_rect.topleft = (self.offset + 10, self.height - 40)
        self.surface.blit(score, score_rect)

    def check_hover(self):
        x, y = pygame.mouse.get_pos()
        if x >= self.offset and x <= self.limit:
            if y >= self.offset and y <= self.limit:
                return True
        return False

    def show_hover(self):
        radius = math.floor(self.step / 2)
        color = "#ffffff" if self.turn == self.p2 else "#000000"
        x, y = pygame.mouse.get_pos()
        x = self.linspace[math.floor((x - self.offset + self.step / 2) / self.step)]
        y = self.linspace[math.floor((y - self.offset + self.step / 2) / self.step)]
        draw_circle(self.surface, x, y, radius, pygame.Color(color))

        # Show the current count value on the hover piece.
        if self.turn.player == HUMAN:
            color = "#000000" if self.turn == self.p2 else "#ffffff"
            count_text = fonts.h5_b.render(f"{self.states.counter + 1}", True, color)
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
                    x = math.floor((pos[0] - self.offset + self.step / 2) / self.step)
                    y = math.floor((pos[1] - self.offset + self.step / 2) / self.step)

                    # Send coords to the process and wait for responce
                    # only if the position does not corresponde to an
                    # illegal move or is not already occupied.
                    self.computer.send(f"M\n{x} {y}\n")
            else:
                # Process the received output
                # self.computer.expecting = True
                resp = self.computer.next_move()
                if resp:
                    if isinstance(resp, tuple) and resp[0] == 0:  # No winner yet
                        # print(
                        #     f"Human[{self.turn.turn}]", resp[1]["time"], resp[1]["move"]
                        # )
                        self.states.add(State(**resp[1]))
                        self.turn = self.p1 if self.turn == self.p2 else self.p2
                        self.computer.expecting = False

                    elif isinstance(resp, tuple) and resp[0] in (1, 2):
                        self.states.add(State(**resp[1]))
                        self.finished = True
                        self.winner = resp[0]

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
                if isinstance(resp, tuple) and resp[0] == 0:  # No winner yet
                    print(
                        f"Computer[{self.turn.turn}]", resp[1]["time"], resp[1]["move"]
                    )
                    self.states.add(State(**resp[1]))
                    self.turn = self.p1 if self.turn == self.p2 else self.p2
                    self.computer.expecting = False
                elif isinstance(resp, tuple) and resp[0] in (1, 2):  # Winner found
                    self.states.add(State(**resp[1]))
                    print(f"Player {resp[0]} wins!")
                    self.finished = True
                elif resp == 4:
                    self.finished = True

    def reset(self):
        self.state.reset()
        self.setup_players()
        self.turn = self.p1


class Game:

    __slots__ = (
        "_pallet",
        "_window",
        "_board",
        "_stats",
        "_states",
        "_setup",
        "_computer",
        "_p1",
        "_p2",
    )

    def __init__(self, pallet, window, setup, *args, **kwargs):
        self._pallet = pallet
        self._window = window
        self._states = States()
        self._setup = setup
        self._stats = None
        self._board = None
        self._computer = None
        self._p1 = None
        self._p2 = None

    @property
    def pallet(self):
        return self._pallet

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
        rule = RULES[self.setup.rules.anchor.value - 1]
        size = SIZES[self.setup.sizes.anchor.value - 1]

        args = [
            f"{SIZES[self.setup.sizes.anchor.value - 1]}",
            f"--p1_type={p1_type}",
            f"--p1_diff={p1_diff}",
            f"--p2_type={p2_type}",
            f"--p2_diff={p2_diff}",
            f"--rule={rule}",
        ]

        self.p1 = Player(self.setup.p1_type.anchor.value, 1)
        self.p2 = Player(self.setup.p2_type.anchor.value, 2)

        self.computer = Computer(*args)
        self.board = Board(
            self.pallet,
            self.states,
            self.setup,
            self.p1,
            self.p2,
            self.computer,
            size=int(size),
        )
        self.stats = Stats(
            self.pallet,
            self.states,
            self.board,
            relative_to=self.window,
            position=(HEIGHT, 0),
        )

    def loop(self):
        self.setup_game()
        self.computer.start()

        is_first_move = True
        rule = self.setup.rules.anchor.value - 1
        while True:
            events = pygame.event.get()
            if is_first_move and self.p1.player == HUMAN and rule in (1, 2):
                self.computer.expecting = True
                resp = self.computer.next_move()
                if resp == None:
                    continue
                self.states.add(State(**resp[1]))
                self.board.turn = self.p1 if self.board.turn == self.p2 else self.p2
                self.computer.expecting = False
                is_first_move = False

            for event in events:
                if event.type == pygame.QUIT:
                    self.computer.stop()
                    exit(0)
                if event.type == pygame.MOUSEBUTTONUP and event.button == 1:
                    if self.stats.restart.clicked():
                        self.computer.stop()
                        return
                    if self.board.turn.player == HUMAN:
                        if (
                            self.stats.suggest.clicked()
                            and self.board.states.last.suggestion == None
                        ):
                            self.stats.suggest.pressed = False
                            self.computer.send("S")
                    else:
                        self.stats.suggest.disable()

            self.stats.update(events)
            self.board.update(events)
            self.window.blit(self.board)
            self.window.blit(self.stats)
            self.window.update()
            CLOCK.tick(60)
