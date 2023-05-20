class State:
    """
    This class represents a board state read from the game logic.
    """

    __slots__ = ('_state', '_counts', '_counter')

    def __init__(self):
        self._counter = 0
        self._counts = {}
        self._state = [['0' for j in range(19)] for i in range(19)]

    def __getitem__(self, index):
        return self.state[index]

    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, new_state):
        self._state = new_state

    @property
    def counter(self):
        return self._counter
    
    @counter.setter
    def counter(self, value):
        self._counter = value

    @property
    def counts(self):
        return self._counts
    
    @counts.setter
    def counts(self, value):
        self._counts = value

    def update(self, x, y, player):
        self.counter = self.counter + 1
        self.counts[(x, y)] = self.counter
        self.state[y][x] = player

    def reset(self):
        self.counter = 0
        self.counts = {}
        self.state = [['0' for j in range(19)] for i in range(19)]

    def print(self):
        for row in self.state:
            print(''.join(row))