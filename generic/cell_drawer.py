from time import sleep
from typing import Tuple

import pygame

from generic.cell_array import CellArray

STATE_COLORS = [
    (0, 0, 0),
    (128, 0, 0),
    (0, 128, 0),
    (0, 0, 128),
    (128, 0, 128),
    (128, 128, 0),
    (0, 128, 128),
    (128, 128, 128)
]


class CellDrawer:

    def __init__(self, dimension: Tuple[int,int], scale : int):
        pygame.init()
        self.scale = scale
        self.window_surface = pygame.display.set_mode(dimension)

    def draw(self, cell_array: CellArray):

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                exit()

        w, h = cell_array.dimension()
        empty_surf = pygame.Surface((w, h))
        cell_pixarray = pygame.surfarray.pixels3d(empty_surf)

        for j in range(h):
            for i in range(w):
                state = cell_array.get_cell_state(i, j)
                cell_pixarray[i][j] = STATE_COLORS[state]

        cell_surf = pygame.Surface((w, h))
        pygame.surfarray.blit_array(cell_surf, cell_pixarray)
        cell_surf = pygame.transform.scale(
            cell_surf,
            (cell_surf.get_rect().w*self.scale, cell_surf.get_rect().h*self.scale)
        )

        self.window_surface.blit(cell_surf, (0, 0))
        sleep(0.025)
        pygame.display.flip()
