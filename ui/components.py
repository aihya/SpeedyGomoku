import pygame
from surface import Surface
from fonts import *
from init import *

class Button(Surface):
    """
    Class representing an interactive button object
    """
    def __init__(self, fg: str, bg: str, text: str, font, disabled=False, interactive=True, *args, **kwargs):

        # Load font
        self._font = font

        self._bg_str = bg
        self._fg_str = fg
        self._bg = pygame.Color(bg)
        self._fg = pygame.Color(fg)
        self._bg_hov = pygame.Color(bg)
        self._bg_hov.r = self.bg.r - 30 if self.bg.r >= 30 else self.bg.r
        self._bg_hov.b = self.bg.b - 30 if self.bg.b >= 30 else self.bg.b
        self._bg_hov.g = self.bg.g - 30 if self.bg.g >= 30 else self.bg.g

        self._orig_text = text
        self._text = self.font.render(text, True, pygame.Color(self.fg), pygame.Color(self.bg))

        self.surf_width = self.text.get_width()
        self.surf_height = self.text.get_height()

        super().__init__(self.surf_width + 60, self.surf_height + 30, *args, **kwargs)
        self._text_rect = self.text.get_rect()
        self._text_rect.center = (int(self.width / 2), int(self.height / 2))

        self._hover = False
        self._pressed = False
        self._disabled = disabled
        self._interactive = interactive

    @property
    def bg(self):
        return self._bg

    @bg.setter
    def bg(self, value: pygame.Color):
        self._bg = value

    @property
    def fg(self):
        return self._fg

    @property
    def bg_str(self):
        return self._bg_str

    @property
    def fg_str(self):
        return self._fg_str

    @property
    def font(self):
        return self._font

    @property
    def orig_text(self):
        return self._orig_text

    @property
    def text(self):
        return self._text

    @text.setter
    def text(self, value):
        self._text = value

    @property
    def text_rect(self):
        return self._text_rect

    @property
    def disabled(self):
        return self._disabled

    @disabled.setter
    def disabled(self, value):
        self._disabled = value

    def disable(self):
        self.bg = self._bg_hov
        self.text = self.font.render(self.orig_text, True, pygame.Color(self.fg), pygame.Color(self.bg))

    @property
    def hover(self):
        return self._hover

    @hover.setter
    def hover(self, value):
        self._hover = value

    @property
    def pressed(self):
        return self._pressed

    @pressed.setter
    def pressed(self, value):
        self._pressed = value

    @property
    def interactive(self):
        return self._interactive

    def set_hover(self):
        if self.abs_rect.collidepoint(pygame.mouse.get_pos()):
            self.bg = pygame.Color(self.bg_str) if self.pressed else self._bg_hov
            self.text = self.font.render(self.orig_text, True, pygame.Color(self.fg), pygame.Color(self.bg))
            return 
        self.bg = pygame.Color(self.bg_str)
        self.text = self.font.render(self.orig_text, True, pygame.Color(self.fg), pygame.Color(self.bg))

    def clicked(self):
        if self.disabled:
            return False
        if self.abs_rect.collidepoint(pygame.mouse.get_pos()):
            if self.interactive:
                self.bg = pygame.Color(self.bg_str) if self.pressed else self._bg_hov
                self.pressed = not self.pressed
            return True
        return False

    def update(self):
        if not self.disabled:
            self.set_hover()
        else:
            self.disable()
        self.surface.fill(self.bg)
        self.surface.blit(self.text, self.text_rect)


class CheckBox(Surface):

    HEIGHT = 40

    __slots__ = ('_label', '_box', '_value', '_filler', '_checked', '_label_rect', '_hovered', '_active')
    
    def __init__(self, label, value, *args, **kwargs):
        self._label = h3_t.render(label, True, BLACK, DEFAULT_BG)
        self._label_rect = self.label.get_rect()
        self._label_rect.left = 70
        self._value = value
        self._checked = False
        self._hovered = False
        self._active = True

        super().__init__(
            self._label.get_width() + 70, 
            self.HEIGHT,
            *args,
            alpha=True,
            **kwargs
        )

        self._box = Surface(self.HEIGHT, self.HEIGHT, (0, 0), self)
        self._filler = Surface(self.HEIGHT-10, self.HEIGHT-10, (5, 5), self)

    @property
    def active(self):
        return self._active
    
    @active.setter
    def active(self, value: bool):
        self._active = value

    @property
    def label(self):
        return self._label

    @property
    def label_rect(self):
        return self._label_rect

    @property
    def value(self):
        return self._value

    @property
    def box(self):
        return self._box

    @property
    def filler(self):
        return self._filler

    @property
    def checked(self):
        return self._checked

    def check_hover(self):
        self.hovered = False
        if self.abs_rect.collidepoint(pygame.mouse.get_pos()):
            self.hovered = True
        return self.hovered

    @property
    def hovered(self):
        return self._hovered

    @hovered.setter
    def hovered(self, value):
        self._hovered = value

    @checked.setter
    def checked(self, value):
        self._checked = value

    def check_clicked(self):
        if self.active and self.abs_rect.collidepoint(pygame.mouse.get_pos()):
            self.checked = True

    def update(self):
        self.surface.blit(self.box.surface, self.box.rect)
        if self.active:
            self.check_hover()
        if self.checked or self.hovered:
            if self.active:
                self.filler.surface.fill(BOARD_COLOR)
            else:
                self.filler.surface.fill((120, 120, 120))
            self.surface.blit(self.filler.surface, self.filler.rect)
        self.surface.blit(self.label, self._label_rect)


class CheckBoxs(Surface):

    __slots__ = ('_container', '_anchor', '_active')

    def __init__(self, pairs: dict, *args, **kwargs):

        _len    = len(pairs)
        _height = CheckBox.HEIGHT * _len + (10 * (_len-1) if _len > 1 else 0)
        _width  = kwargs['relative_to'].width

        super().__init__(width=_width, height=_height, alpha=True, **kwargs)
        self.surface.fill((0, 0, 0, 0))

        # List containing all checkboxs
        self._container = []

        # Create instances of CheckBox and set containers' max height accordingly
        offset = 0
        for index, key in enumerate(pairs.keys()):
            cb_position = (0, offset)
            self._container.append(CheckBox(pairs[key], key, position=cb_position, relative_to=self))
            offset += self._container[-1].height
            if index < _len - 1:
                offset += 10

        # Anchor to first element of container list or set to None
        if self._container:
            self._anchor = self._container[0]
            self._anchor.checked = True

        self._active = True

    @property
    def active(self):
        return self._active
    
    @active.setter
    def active(self, value: bool):
        self._active = value
        for box in self.container:
            box.active = value

    @property
    def container(self):
        return self._container

    @property
    def anchor(self):
        return self._anchor

    @anchor.setter
    def anchor(self, value):
        self._anchor = value

    def update(self):
        for box in self.container:
            box.update()
            if box.active and box.checked and box is not self.anchor:
                self.anchor.checked = False
                self.anchor = box
                box.checked = True
            self.surface.blit(box.surface, box.rect)
