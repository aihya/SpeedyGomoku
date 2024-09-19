import pygame
import sys
import time
import random
from enum import Enum


class ChessColor(Enum):
    WHITE = (255, 255, 255)
    BLACK = (0, 0, 0)


class HistoryTable:
    def __init__(
        self,
        width,
        height,
        row_width,
        row_height,
        max_entries,
        background_color,
        text_color,
    ):
        pygame.init()
        self.width = width
        self.height = height
        self.row_width = row_width
        self.row_height = row_height
        self.max_entries = max_entries

        self.screen = pygame.display.set_mode((width, height))
        pygame.display.set_caption("Chess Moves History")

        # Colors
        self.background_color = background_color
        self.light_background_color = self.lighten_color(background_color, 20)
        self.text_color = text_color

        # Fonts
        self.font = pygame.font.Font(None, 24)

        # History entries
        self.history = []

    def lighten_color(self, color, amount):
        return tuple(min(255, c + amount) for c in color)

    def add_entry(self, color, coordinate, time_ms):
        self.history.insert(0, (color, coordinate, time_ms))
        if len(self.history) > self.max_entries:
            self.history.pop()

    def draw_table(self):
        for i in range(self.max_entries):
            y = i * self.row_height
            if i < len(self.history):
                color, coordinate, time_ms = self.history[i]

                # Draw row background
                if i % 2 == 0:
                    pygame.draw.rect(
                        self.screen,
                        self.light_background_color,
                        (0, y, self.row_width, self.row_height),
                    )
                else:
                    pygame.draw.rect(
                        self.screen,
                        self.background_color,
                        (0, y, self.row_width, self.row_height),
                    )

                # Draw color indicator circle with transparent border
                piece_color = color.value
                border_color = (
                    ChessColor.WHITE.value
                    if color == ChessColor.BLACK
                    else ChessColor.BLACK.value
                )
                border_surface = pygame.Surface((22, 22), pygame.SRCALPHA)
                pygame.draw.circle(
                    border_surface, (*border_color, 128), (11, 11), 11
                )  # 128 is half opacity
                self.screen.blit(border_surface, (9, y + self.row_height // 2 - 11))
                pygame.draw.circle(
                    self.screen, piece_color, (20, y + self.row_height // 2), 9
                )

                # Render coordinate
                coord_surface = self.font.render(coordinate, True, self.text_color)
                coord_rect = coord_surface.get_rect(
                    midleft=(40, y + self.row_height // 2)
                )
                self.screen.blit(coord_surface, coord_rect)

                # Render time on the right
                time_str = f"{time_ms} ms"
                time_surface = self.font.render(time_str, True, self.text_color)
                time_rect = time_surface.get_rect(
                    midright=(self.row_width - 10, y + self.row_height // 2)
                )
                self.screen.blit(time_surface, time_rect)
            else:
                # Draw empty row with main background color
                pygame.draw.rect(
                    self.screen,
                    self.background_color,
                    (0, y, self.row_width, self.row_height),
                )

    def run(self):
        running = True
        clock = pygame.time.Clock()

        while running:
            for event in pygame.event.get():
                if event.type == pygame.QUIT:
                    running = False

            self.screen.fill(self.background_color)
            self.draw_table()
            pygame.display.flip()
            clock.tick(60)

        pygame.quit()
        sys.exit()


# Test code
if __name__ == "__main__":
    WINDOW_WIDTH = 400
    WINDOW_HEIGHT = 600
    ROW_WIDTH = 380
    ROW_HEIGHT = 40
    MAX_ENTRIES = 15

    # Define colors
    BACKGROUND_COLOR = (50, 50, 50)  # Dark gray
    TEXT_COLOR = (200, 200, 200)  # Light gray

    table = HistoryTable(
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        ROW_WIDTH,
        ROW_HEIGHT,
        MAX_ENTRIES,
        BACKGROUND_COLOR,
        TEXT_COLOR,
    )

    # List of chess coordinates
    coordinates = [
        "e4",
        "e5",
        "Nf3",
        "Nc6",
        "Bb5",
        "a6",
        "Ba4",
        "Nf6",
        "O-O",
        "Be7",
        "Re1",
        "b5",
        "Bb3",
        "d6",
        "c3",
        "O-O",
    ]

    # Add entries
    start_time = time.time()
    for i in range(len(coordinates)):
        current_time = time.time()
        elapsed_time_ms = int(
            (current_time - start_time) * 1000
        )  # Convert to milliseconds
        color = ChessColor.BLACK if i % 2 == 0 else ChessColor.WHITE  # Start with black
        coordinate = coordinates[i]
        table.add_entry(color, coordinate, elapsed_time_ms)
        time.sleep(0.07)  # Wait for 0.5 seconds between entries

    table.run()
