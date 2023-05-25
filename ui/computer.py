import signal
from pexpect.popen_spawn import PopenSpawn
from pexpect.exceptions import TIMEOUT
from init import EXE_PATH
from state import State, States

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
        self.process.send(what)
        self.expecting = True

    @property
    def expecting(self) -> bool:
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
            'time': float(buffer[0]),
            'coords': [int(c) for c in buffer[1].split()],
            'board': [],
        }

        self.invalid_move = None
        for r, line in enumerate(buffer[2:-2]):
            line = line.split()
            move['board'].append([])
            for c, value in enumerate(line[:-1]):
                if value == 'O':
                    move['board'][-1].append('1')
                elif value == 'X':
                    move['board'][-1].append('2')
                elif value == 'I':
                    self.invalid_move = (r, c)
                else:
                    move['board'][-1].append('0')
        return move

    def next_move(self):
        """
        Read the buffer from pexpect.popen_spawn.PopenSpawn, process the 
        content and create a move object.
        """

        if self.process:
            # Attempt an expect operation from subprocess.
            # Return None if no match found.
            index = self.expect(['Enter coords:\n', 'Illegal move\n', 'Player 1 wins!\n', 'Player 2 wins!\n', 'Tie\n'])

            if index == None or index < -1:
                return None
            if index >= 0 or index < 5:
                self.expecting = False
            if index == 0:
                # Read the content sent from the subprocess
                buffer = self.process.before.decode('utf-8').split('\n')

                if buffer:
                    # Extract the move informations and store it in a dictionary
                    return self.extract_move(buffer)

            return index

        return None


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
