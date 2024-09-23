from surface import Surface
from components import draw_circle
from init import *
import fonts


class State:
    """
    This class represents a board state read from the game logic.
    """

    __slots__ = (
        "_state",
        "_count",
        "_move",
        "_time",
        "_suggestion",
        "_captures",
        "_color",
        "_score",
    )

    def __init__(self, state=None, time=0, move=None, captures=None, score=0):
        self._state = state if state else [["0" for j in range(19)] for i in range(19)]
        self._count = {}
        self._time = time
        self._move = move
        self._suggestion = None
        self._captures = captures
        self._score = score

    def __getitem__(self, index):
        return self.state[index]

    @property
    def score(self):
        return self._score

    @property
    def color(self):
        if self.move:
            return int(self.state[self.move[1]][self.move[0]])

    @property
    def captures(self):
        return self._captures

    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, new_state):
        self._state = new_state

    @property
    def count(self):
        return self._count

    @count.setter
    def count(self, value):
        self._count = value

    @property
    def time(self):
        return self._time

    # Very unlikely to be used.
    @time.setter
    def time(self, new_time):
        self._time = new_time

    @property
    def move(self):
        return self._move

    # Very unlikely to be used.
    @move.setter
    def move(self, new_move: tuple):
        self._move = new_move

    @property
    def suggestion(self):
        return self._suggestion

    @suggestion.setter
    def suggestion(self, value):
        self._suggestion = value

    def update(self, x, y, player, count):
        self.count[(x, y)] = count
        self.state[y][x] = player

    def print(self):
        for row in self.state:
            print("".join(row))


class States:

    __slots__ = ("_states", "_counter", "_index")

    def __init__(self):
        self._states = [State()]
        self._counter = 0
        self._index = -1

    @property
    def states(self):
        return self._states

    @property
    def counter(self):
        return self._counter

    @counter.setter
    def counter(self, obj: int):
        self._counter = obj

    @property
    def current(self):
        if self.states:
            return self.states[self.index]
        return None

    @property
    def index(self):
        return self._index

    @index.setter
    def index(self, value):
        self._index = value

    @property
    def last(self):
        return self.states[-1]

    @property
    def first(self):
        return self.states[0]

    def add(self, state):
        self.counter = self.counter + 1
        state.count = self.last.count.copy()
        state.count[state.move] = self.counter
        self.states.append(state)


class HistoryTable(Surface):

    __slots__ = (
        "_states",
        "_slots",
        "_slot_height",
        "_num_slots",
        "_current",
        "_start",
        "_stop",
        "_selected_slot",
    )

    def __init__(self, states, width, height, *args, **kwargs):
        super().__init__(width, height, relative_to=kwargs["relative_to"])
        self._states = states
        self._slot_height = self.height // 20
        self._slots = []
        self._num_slots = 0
        self._current = 0
        self._start = None
        self._stop = None
        self._selected_slot = None
        self.update_slots()

    @property
    def selected_slot(self):
        return self._selected_slot

    @selected_slot.setter
    def selected_slot(self, slot):
        self._selected_slot = slot

    @property
    def states(self):
        return self._states

    @property
    def slots(self):
        return self._slots

    @property
    def slot_height(self):
        return self._slot_height

    @property
    def num_slots(self):
        return self._num_slots

    @num_slots.setter
    def num_slots(self, value):
        self._num_slots = value

    @property
    def current(self):
        return self._current

    @current.setter
    def current(self, value):
        self._current = value

    @property
    def start(self):
        return self._start

    @start.setter
    def start(self, value):
        self._start = value

    @property
    def stop(self):
        return self._stop

    @stop.setter
    def stop(self, value):
        self._stop = value

    def update_slots(self):
        if self.states.counter != self.num_slots:
            state = self.states.states[-1]
            slot = Surface(self.width, self.slot_height, relative_to=self)
            slot.surface.fill(GRAY_2 if state.color == 2 else GRAY_3)

            count = fonts.h5_t.render(f"{len(state.count)}. ", True, WHITE)
            count_rect = count.get_rect()
            count_rect.left = 20
            count_rect.centery = self.slot_height // 2

            time = fonts.h5_t.render(f"{state.time:.2f} ms", True, WHITE)
            time_rect = time.get_rect()
            time_rect.centerx = self.width - time_rect.width // 2 - 30
            time_rect.centery = self.slot_height // 2

            coords = fonts.h5_t.render(
                f'{"ABCDEFGHIJKLMNOPQRST"[state.move[0]]} - {state.move[1]+1}',
                True,
                WHITE,
            )
            coords_rect = coords.get_rect()
            coords_rect.left = 120
            coords_rect.centery = self.slot_height // 2

            draw_circle(
                slot.surface,
                90,
                self.slot_height // 2,
                8,
                WHITE if state.color == 2 else BLACK,
            )
            slot.surface.blit(count, count_rect)
            slot.surface.blit(coords, coords_rect)
            slot.surface.blit(time, time_rect)
            self.slots.append(slot)
            self.num_slots = self.states.counter

    def update(self, events):
        self.surface.fill(GRAY_1)

        button_down_pos = None
        for event in events:
            if event.type == pygame.MOUSEWHEEL and self.check_hover():
                if event.y == -1 and self.current < self.num_slots - 20:
                    self.current += 1
                elif event.y == 1 and self.current > 0:
                    self.current -= 1
            if event.type == pygame.MOUSEBUTTONDOWN and event.button == 1:
                button_down_pos = pygame.mouse.get_pos()

        self.update_slots()
        if self.num_slots > 20 and self.current < self.num_slots - 20:
            start = self.current
            stop = self.current + 20
        else:
            start = -20
            stop = None

        for i, slot in enumerate(self.slots[start:stop]):
            x, y = self.abs_rect.topleft
            slot_rect = slot.surface.get_rect()
            slot_rect.topleft = (0, i * self.slot_height)
            coll_rect = slot_rect.copy()
            coll_rect.topleft = (x, y + i * self.slot_height)
            if button_down_pos and coll_rect.collidepoint(button_down_pos):
                if start == -20:
                    if self.num_slots > 20:
                        self.selected_slot = self.num_slots - 20 + i
                    else:
                        self.selected_slot = i
                else:
                    self.selected_slot = start + i
            if coll_rect.collidepoint(pygame.mouse.get_pos()):
                replicate = slot.surface.copy()
                draw_circle(
                    replicate,
                    self.width - 15,
                    self.slot_height // 2,
                    4,
                    pygame.Color("#FFFF00"),
                )
                self.surface.blit(replicate, slot_rect)
            else:
                self.surface.blit(slot.surface, slot_rect)
