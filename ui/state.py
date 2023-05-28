class State:
    """
    This class represents a board state read from the game logic.
    """

    __slots__ = ('_state',)

    def __init__(self):
        self._state = [['0' for j in range(19)] for i in range(19)]

    def __getitem__(self, index):
        return self.state[index]

    @property
    def state(self):
        return self._state

    @state.setter
    def state(self, new_state):
        self._state = new_state

    def update(self, x, y, player):
        self._state[y][x] = player