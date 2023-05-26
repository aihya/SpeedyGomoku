class State:
    """
    This class represents a board state read from the game logic.
    """

    __slots__ = ('_state', '_count', '_move', '_time')

    def __init__(self, state=None, time=0, move=None):
        self._state = state if state else [['0' for j in range(19)] for i in range(19)]
        self._count = {}
        self._time  = time
        self._move  = move

    def __getitem__(self, index):
        return self.state[index]

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
        
    def update(self, x, y, player, count):
        self.count[(x, y)] = count
        self.state[y][x] = player

    def print(self):
        for row in self.state:
            print(''.join(row))

class States:

    __slots__ = ('_states', '_counter')

    def __init__(self):
        self._states = [State()]
        self._counter = 0

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
            return self.states[-1]
        return None

    def add(self, state):
        self.counter = self.counter + 1
        state.count = self.current.count.copy()
        state.count[state.move] = self.counter
        self.states.append(state)