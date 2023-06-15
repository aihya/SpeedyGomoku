class State:
    """
    This class represents a board state read from the game logic.
    """

    __slots__ = ('_state', '_count', '_move', '_time', '_suggestion', '_captures')

    def __init__(self, state=None, time=0, move=None, captures=None):
        self._state = state if state else [['0' for j in range(19)] for i in range(19)]
        self._count = {}
        self._time  = time
        self._move  = move
        self._suggestion = None
        self._captures = captures

    def __getitem__(self, index):
        return self.state[index]
    
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
            print(''.join(row))

class States:

    __slots__ = ('_states', '_counter', '_index')

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
