import signal
from pexpect.popen_spawn import PopenSpawn
from pexpect.exceptions import TIMEOUT, EOF
from init import EXE_PATH

class Computer:
    """
    This class represents the computer player.
    """

    __slots__ = ('_process', '_executable', '_args', '_expecting', '_invalid_move')

    def __init__(self, *args):
        self._process = None
        self._executable = ' '.join([EXE_PATH, *args])
        self._expecting = False
        self._invalid_move = None

    @property
    def process(self):
        return self._process

    @process.setter
    def process(self, value):
        self._process = value

    @property
    def executable(self):
        return self._executable

    @property
    def invalid_move(self):
        return self._invalid_move
    
    @invalid_move.setter
    def invalid_move(self, coords):
        self._invalid_move = coords

    def start(self):
        if self.process:
            self.stop()
        self.process = PopenSpawn(self.executable)
        print('Started process', self.process)

    def stop(self):
        if self.process:
            print('Stopped process', self.process)
            self.process.kill(signal.SIGKILL)
            self.process = None

    def pause(self):
        """
        Trigger SIGSTOP signal to stop the process temporarly.
        """
        if self.process:
            self.process.kill(signal.SIGSTOP)

    def resume(self):
        """
        Trigger SIGCONT signal to continue the execution of the process.
        """
        if self.process:
            self.process.kill(signal.SIGCONT)

    def send(self, what: str):
        print('Sending:', what)
        self.process.send(what)
        self.expecting = True

    @property
    def expecting(self):
        return self._expecting

    @expecting.setter
    def expecting(self, value: bool):
        self._expecting = value

    def expect(self, what: list):
        """
        This simple implementation does not support multiple expects.
        """
        if self.process:
            try:
                return self.process.expect(what, timeout=0.00001)
            except TIMEOUT:
                pass
        return

    def extract_move(self, buffer):
        if len(buffer) == 1:
            return None

        move = {
            'time': 0,
            'move': [],
            'board': [],
        }
        start, end = 2, -1
        if len(buffer) - 1 == 20: # Human output
            move['time'] = 0
            move['move'] = tuple(int(c) for c in buffer[0].split())
            start, end = 1, -1
        else:
            move['time'] = float(buffer[0])
            move['move'] = tuple(int(c) for c in buffer[1].split())

        for line in buffer[start:end]:
            move['board'].append(['.XO'.find(c) for c in line if c in '.XO'])

        return move

    def next_move(self):
        """
        Read the buffer from pexpect.popen_spawn.PopenSpawn, process the 
        content and create a move object.
        """

        if not self.process:
            return None

        # Attempt an expect operation from subprocess.
        # Return None if no match found.
        index = self.expect([
            f'{"-" * 37}\n',
            'Player 1 wins!\n',
            'Player 2 wins!\n',
            'Tie\n',
            'Illegal move\n',
            EOF,
        ])

        if index is None:
            return None

        if index == 5:
            self.expecting = False

        elif index in (0, 1, 2):
            # Read the content sent from the subprocess
            buffer = self.process.before.decode('utf-8').split('\n')

            if buffer:
                # Extract the move informations and store it in a dictionary
                return self.extract_move(buffer)

        return index


class Player:

    __slots__ = ('_player', '_turn')

    def __init__(self, player, turn):
        self._player = player
        self._turn = turn

    @property
    def player(self):
        return self._player
    
    @property
    def turn(self):
        return self._turn
