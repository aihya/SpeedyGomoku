import pygame
from pygame import gfxdraw
from surface import Surface
from fonts import *
from init import *
import math

# type of button content
TEXT = 1
IMAGE = 2


def draw_circle(surface, x, y, radius, color):
    gfxdraw.aacircle(surface, x, y, radius + 1, BLACK)
    gfxdraw.aacircle(surface, x, y, radius, color)
    gfxdraw.filled_circle(surface, x, y, radius, color)


class Button(Surface):
    """
    Class representing an interactive button object
    """

    def __init__(
        self,
        fg,
        bg,
        content,
        font,
        width=None,
        height=None,
        hover_color=None,
        disabled=False,
        interactive=True,
        expand=False,
        *args,
        **kwargs
    ):

        self._font = font
        self._bg_str = bg
        self._fg_str = fg
        self._bg = pygame.Color(bg)
        self._fg = pygame.Color(fg)
        if hover_color:
            self._bg_hov = hover_color
        else:
            self._bg_hov = pygame.Color(bg)
            self._bg_hov.r = self.bg.r - 30 if self.bg.r >= 30 else self.bg.r
            self._bg_hov.b = self.bg.b - 30 if self.bg.b >= 30 else self.bg.b
            self._bg_hov.g = self.bg.g - 30 if self.bg.g >= 30 else self.bg.g
        if isinstance(content, str):
            self._content = self.font.render(content, True, self.fg)
        else:
            self._content = content

        if width == None:
            _width = (
                kwargs["relative_to"].width if expand else self.content.get_width() + 60
            )
        else:
            _width = width
        _height = self.content.get_height() + 30 if height == None else height
        super().__init__(_width, _height, *args, **kwargs)

        self._content_rect = self._content.get_rect()
        self._content_rect.center = (int(self.width / 2), int(self.height / 2))

        self._hover = False
        self._pressed = False
        self._disabled = disabled
        self._interactive = interactive

    @property
    def expand(self):
        return self._expand

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
    def content(self):
        return self._content

    @content.setter
    def content(self, value):
        self._content = value

    @property
    def content_rect(self):
        return self._content_rect

    @property
    def disabled(self):
        return self._disabled

    @disabled.setter
    def disabled(self, value):
        self._disabled = value

    def disable(self):
        self.disabled = True
        self.bg = self._bg_hov

    def unable(self):
        self.disabled = False
        self.bg = pygame.Color(self.bg_str)

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
        if self.check_hover():
            self.bg = pygame.Color(self.bg_str) if self.pressed else self._bg_hov
        else:
            self.bg = pygame.Color(self.bg_str)

    def clicked(self):
        if self.disabled:
            return False
        if self.check_hover():
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
        self.surface.blit(self.content, self.content_rect)


class CheckBox(Surface):

    HEIGHT = 40

    __slots__ = (
        "_pallet",
        "_label",
        "_box",
        "_value",
        "_filler",
        "_checked",
        "_label_rect",
        "_hovered",
        "_active",
        "_alignment",
    )

    def __init__(self, pallet, label, value, alignment=VERTICAL, *args, **kwargs):
        self._pallet = pallet
        self._value = value
        self._checked = False
        self._hovered = False
        self._active = True
        self._alignment = alignment

        if self.alignment == VERTICAL:
            self._label = h4_r.render(label, True, self.pallet.foreground)
            self._label_rect = self.label.get_rect()
            self._label_rect.left = 70
            self._label_rect.top = 5
            _height = self.HEIGHT
            _width = self._label.get_width() + 70
        else:
            self._label = h4_r.render(label, True, self.pallet.foreground)
            self._label_rect = self.label.get_rect()
            self._label_rect.left = 50
            self._label_rect.top = 5
            _height = self.HEIGHT
            _width = self._label.get_width() + 50

        super().__init__(_width, _height, *args, **kwargs)

    @property
    def pallet(self):
        return self._pallet

    @property
    def alignment(self):
        return self._alignment

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
        self.surface.fill(self.pallet.background)
        draw_circle(self.surface, self.height // 2, self.height // 2, 18, self.pallet.primary)
        if self.active:
            self.check_hover()
        if self.checked or self.hovered:
            if self.active:
                draw_circle(self.surface, self.height // 2, self.height // 2, 14, self.pallet.accent)
            else:
                draw_circle(self.surface, self.height // 2, self.height // 2, 14, self.pallet.accent_dimmed)
        self.surface.blit(self.label, self._label_rect)


class CheckBoxs(Surface):

    __slots__ = ("_pallet", "_container", "_anchor", "_active", "_alignment")

    def __init__(self, pallet, pairs: dict, alignment=VERTICAL, *args, **kwargs):
        self._pallet = pallet
        self._alignment = alignment
        _len = len(pairs)

        if self.alignment == VERTICAL:
            _height = CheckBox.HEIGHT * _len + (10 * (_len - 1) if _len > 1 else 0)
            _width = kwargs["relative_to"].width
        else:
            _height = CheckBox.HEIGHT
            _width = kwargs["relative_to"].width
            step = math.floor(kwargs["relative_to"].width / _len)

        super().__init__(width=_width, height=_height, **kwargs)

        # List containing all checkboxs
        self._container = []

        offset = 0
        for index, key in enumerate(pairs.keys()):
            if self.alignment == VERTICAL:
                cb_pos = (0, offset)
                self._container.append(
                    CheckBox(
                        pallet,
                        pairs[key],
                        key,
                        position=cb_pos,
                        alignment=alignment,
                        relative_to=self,
                        alpha=True,
                    )
                )
                offset += self._container[-1].height
                if index < _len - 1:
                    offset += 10
            else:
                cb_pos = (offset, 0)
                self._container.append(
                    CheckBox(
                        pallet,
                        pairs[key],
                        key,
                        position=cb_pos,
                        alignment=alignment,
                        relative_to=self,
                        alpha=True,
                    )
                )
                offset += step

        # Anchor to first element of container list or set to None
        if self._container:
            self._anchor = self._container[0]
            self._anchor.checked = True

        self._active = True

    @property
    def pallet(self):
        return self._pallet

    @property
    def alignment(self):
        return self._alignment

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


class ColorPallet:

    __slots__ = (
        "_rose",
        "_blue",
        "_green",
        "_pallets",
        "_pallet",
        "_accent",
        "_primary",
        "_secondary",
        "_background",
        "_foreground",
        "_black",
        "_white",
    )

    def __init__(self):
        self._white = pygame.Color("#FFFFFF")
        self._black = pygame.Color("#000000")
        self._rose = [
            pygame.Color("#E5405B"),
            pygame.Color("#323232"),
            pygame.Color("#4B4B4B"),
            pygame.Color("#E0E0E0"),
            pygame.Color("#252525"),
            pygame.Color("#666666"),
        ]
        self._blue = [
            pygame.Color("#178afc"),
            pygame.Color("#3D3D3D"),
            pygame.Color("#565656"),
            pygame.Color("#E7E7E7"),
            pygame.Color("#171717"),
            pygame.Color("#666666"),
        ]
        self._green = [
            pygame.Color("#EAE6E3"),
            pygame.Color("#6DD247"),
            pygame.Color("#CCCCCC"),
            pygame.Color("#E0E0E0"),
            pygame.Color("#252525"),
            pygame.Color("#666666"),
        ]
        self._pallets = [self._blue, self._rose, self._green]
        self._pallet = self.pallets[0]

    @property
    def pallet(self):
        return self._pallet

    @pallet.setter
    def pallet(self, index):
        if 0 <= index < 3:
            self._pallet = self.pallets[index]

    @property
    def pallets(self):
        return self._pallets

    @property
    def white(self):
        return self._white

    @property
    def black(self):
        return self._black

    @property
    def accent(self):
        return self.pallet[0]
    
    @property
    def accent_dimmed(self):
        return self.pallet[5]

    @property
    def primary(self):
        return self.pallet[1]

    @property
    def secondary(self):
        return self.pallet[2]

    @property
    def foreground(self):
        return self.pallet[3]

    @property
    def background(self):
        return self.pallet[4]
