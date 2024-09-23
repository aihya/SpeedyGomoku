import pygame


class Surface:
    """
    This class is an abstraction over pygame.Surface
    """

    QUIT = False

    __slots__ = (
        "_is_window",
        "_position",
        "_width",
        "_height",
        "_surface",
        "_rect",
        "_relative_to",
        "_abs_rect",
    )

    def __init__(
        self,
        width,
        height,
        position=(0, 0),
        relative_to=None,
        alpha=False,
        is_window=False,
    ):
        self._relative_to = relative_to

        # Surface alpha flag
        flags = pygame.SRCALPHA if alpha else 0

        if is_window:
            self._surface = pygame.display.set_mode((width, height), flags=flags)
        else:
            self._surface = pygame.Surface((width, height), flags=flags)

        self._rect = self._surface.get_rect()
        self._rect.move_ip(position)

        self._abs_rect = self._rect.copy()

        if relative_to is not None:
            self._abs_rect.move_ip(relative_to.abs_rect.topleft)

    @property
    def position(self):
        return self.rect.topleft

    @position.setter
    def position(self, coords: tuple):
        self._position = coords
        self.rect.move_ip(coords)
        self.abs_rect.move_ip(coords)

    @property
    def width(self):
        return self.rect.width

    @property
    def height(self):
        return self.rect.height

    @property
    def surface(self):
        return self._surface

    @property
    def rect(self):
        return self._rect

    @property
    def abs_rect(self):
        return self._abs_rect

    @property
    def relative_to(self):
        return self._relative_to

    def check_hover(self):
        return self.abs_rect.collidepoint(pygame.mouse.get_pos())
