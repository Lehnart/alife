from time import sleep

import pygame

from cell_array import CellArray
from cell_rule import Rule

window_surface = pygame.display.set_mode((700, 700))

ca = CellArray(7, 7, 10, 10, Rule())

while True:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()

    cell_surf = ca.draw()
    cell_surf = pygame.transform.scale(cell_surf, (700, 700))
    window_surface.blit(cell_surf, (0, 0))

    sleep(1)
    print("next")

    pygame.display.flip()

    ca.evolve()
