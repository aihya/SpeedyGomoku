import pygame
from pygame.locals import *
import math

# Initialize Pygame
# pygame.init()


class Dropdown:
    def __init__(
        self,
        x,
        y,
        width,
        height,
        options,
        label="Select an option",
        colors=None,
        disabled=False,
    ):
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.options = options
        self.label = label
        self.is_open = False
        self.selected_option = None
        self.is_collapsed = True
        self.triangle_angle = 0
        self.animation_progress = 0
        self.hover_option = None
        self.disabled = disabled

        # Set arrow size to height and calculate its x-position
        self.arrow_size = self.height
        self.arrow_x = self.x + self.width - self.arrow_size

        # Default colors
        default_colors = {
            "primary": (200, 200, 200),  # Light gray (dropdown background)
            "accent": (150, 150, 150),  # Darker gray (arrow background)
            "text": (50, 50, 50),  # Dark gray (text and arrow color)
            "label": (100, 100, 100),  # Medium gray (label color)
        }

        # Update with user-provided colors
        self.colors = default_colors
        if colors:
            self.colors.update(colors)

        # Create fonts
        self.font = self.create_fitted_font()
        self.label_font = self.create_fitted_font(is_label=True)

        # Create disabled overlay
        self.disabled_overlay = pygame.Surface((width, height))
        self.disabled_overlay.fill((255, 255, 255))  # White
        self.disabled_overlay.set_alpha(128)  # 50% opacity

    def create_fitted_font(self, is_label=False):
        font_size = 100
        max_width = self.width - self.arrow_size - 20
        max_height = self.height - 10
        while font_size > 1:
            font = pygame.font.Font(None, font_size)
            if is_label:
                font.set_bold(False)  # Make label font thinner
            text_width, text_height = font.size(
                max(self.options + [self.label], key=len)
            )
            if text_width <= max_width and text_height <= max_height:
                return font
            font_size -= 1
        return pygame.font.Font(None, 1)  # Fallback to smallest size if nothing fits

    def draw_main(self, screen):
        # Draw main dropdown box
        pygame.draw.rect(
            screen, self.colors["primary"], (self.x, self.y, self.width, self.height)
        )

        # Draw arrow background
        pygame.draw.rect(
            screen,
            self.colors["accent"],
            (self.arrow_x, self.y, self.arrow_size, self.arrow_size),
        )

        # Draw text (label or selected option)
        if self.selected_option:
            text = self.font.render(self.selected_option, True, self.colors["text"])
        else:
            text = self.label_font.render(self.label, True, self.colors["label"])
        text_rect = text.get_rect(midleft=(self.x + 10, self.y + self.height // 2))
        text_rect.width = self.width - self.arrow_size - 20  # Limit text width
        screen.blit(text, text_rect)

        # Draw rotating triangle
        triangle_x = self.arrow_x + self.arrow_size // 2
        triangle_y = self.y + self.arrow_size // 2
        triangle_size = self.arrow_size // 6

        # Calculate triangle points
        points = [
            (0, -triangle_size),
            (triangle_size * math.sqrt(3) / 2, triangle_size / 2),
            (-triangle_size * math.sqrt(3) / 2, triangle_size / 2),
        ]

        # Rotate points
        rotated_points = [
            (
                p[0] * math.cos(self.triangle_angle)
                - p[1] * math.sin(self.triangle_angle)
                + triangle_x,
                p[0] * math.sin(self.triangle_angle)
                + p[1] * math.cos(self.triangle_angle)
                + triangle_y,
            )
            for p in points
        ]

        pygame.draw.polygon(screen, self.colors["text"], rotated_points)

        # Draw disabled overlay if dropdown is disabled
        if self.disabled:
            screen.blit(self.disabled_overlay, (self.x, self.y))

    def draw_options(self, screen):
        # print('drawing options')
        if self.is_open and not self.disabled:
            option_height = self.height * self.animation_progress
            for i, option in enumerate(self.options):
                option_y = self.y + self.height + (i * option_height)
                option_rect = pygame.Rect(self.x, option_y, self.width, option_height)

                # Use primary color for options, slightly darker for hover
                if self.hover_option == i:
                    hover_color = tuple(max(0, c - 20) for c in self.colors["primary"])
                    pygame.draw.rect(screen, hover_color, option_rect)
                else:
                    pygame.draw.rect(screen, self.colors["primary"], option_rect)

                text = self.font.render(option, True, self.colors["text"])
                text_rect = text.get_rect(
                    midleft=(self.x + 10, option_y + option_height // 2)
                )
                screen.blit(text, text_rect)

            # Draw disabled overlay for options if dropdown is disabled
            if self.disabled:
                options_height = (
                    self.height * len(self.options) * self.animation_progress
                )
                screen.blit(
                    self.disabled_overlay,
                    (self.x, self.y + self.height),
                    (0, 0, self.width, options_height),
                )

    def handle_event(self, event):
        if self.disabled:
            return
        if event.type == pygame.MOUSEBUTTONDOWN:
            dropdown_rect = pygame.Rect(self.x, self.y, self.width, self.height)
            print(dropdown_rect, event.pos)
            if dropdown_rect.collidepoint(event.pos):
                print(event)
                self.is_open = not self.is_open
                self.is_collapsed = not self.is_open
            elif self.is_open:
                for i, option in enumerate(self.options):
                    option_rect = pygame.Rect(
                        self.x,
                        self.y + self.height + (i * self.height),
                        self.width,
                        self.height,
                    )
                    if option_rect.collidepoint(event.pos):
                        self.selected_option = option
                        self.is_open = False
                        self.is_collapsed = True
                        self.animation_progress = 0
            else:
                self.is_open = False
                self.is_collapsed = True
                self.animation_progress = 0
        elif event.type == pygame.MOUSEMOTION:
            if self.is_open:
                for i, option in enumerate(self.options):
                    option_rect = pygame.Rect(
                        self.x,
                        self.y + self.height + (i * self.height),
                        self.width,
                        self.height,
                    )
                    if option_rect.collidepoint(event.pos):
                        self.hover_option = i
                        break
                else:
                    self.hover_option = None

    def update(self):
        if self.disabled:
            self.is_open = False
            self.animation_progress = 0
            return

        if self.is_open and self.animation_progress < 1:
            self.animation_progress = min(1, self.animation_progress + 0.05)
        elif not self.is_open and self.animation_progress > 0:
            self.animation_progress = max(0, self.animation_progress - 0.05)

        target_angle = math.pi if self.is_open else 0
        self.triangle_angle += (target_angle - self.triangle_angle) * 0.2

    def set_disabled(self, disabled):
        self.disabled = disabled
        if disabled:
            self.is_open = False
            self.animation_progress = 0


# Example usage
# screen = pygame.display.set_mode((400, 300))
# clock = pygame.time.Clock()

# Custom colors (optional)
custom_colors = {
    "primary": (40, 40, 40),  # Light gray (dropdown background)
    "accent": (150, 0, 30),  # Darker gray (arrow background)
    "text": (250, 250, 250),  # Dark gray (text and arrow color)
    "label": (100, 100, 100),  # Medium gray (label color)
}

# dropdown1 = Dropdown(
#     50,
#     50,
#     200,
#     40,
#     ["Option 1", "Option 2", "Option 3"],
#     label="Choose an option",
#     colors=custom_colors,
# )
# dropdown2 = Dropdown(
#     50,
#     150,
#     200,
#     40,
#     ["A", "B", "C"],
#     label="Another dropdown",
#     colors=custom_colors,
#     disabled=True,
# )

# # Example button (to demonstrate z-index)
# button_rect = pygame.Rect(100, 100, 100, 50)

# running = True
# while running:
#     for event in pygame.event.get():
#         if event.type == QUIT:
#             running = False
#         dropdown1.handle_event(event)
#         dropdown2.handle_event(event)

#     dropdown1.update()
#     dropdown2.update()

#     screen.fill((240, 240, 240))  # Set global background color

#     # Draw main parts of dropdowns
#     dropdown1.draw_main(screen)
#     dropdown2.draw_main(screen)

#     # Draw example button
#     pygame.draw.rect(screen, (255, 0, 0), button_rect)

#     # Draw dropdown options last to ensure they're on top
#     dropdown1.draw_options(screen)
#     dropdown2.draw_options(screen)

#     pygame.display.flip()
#     clock.tick(60)

# pygame.quit()
