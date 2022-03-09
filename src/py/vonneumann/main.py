from time import sleep

import pygame

from cell_array import CellArray
from cell_rule import Rule
from cell_state import CellState as cs

window_surface = pygame.display.set_mode((700, 700))

pulser1 = [
    [cs.U, cs.U, cs.T_0_0_0, cs.T_0_0_0, cs.T_0_0_0, cs.T_0_0_0, cs.T_0_0_0],
    [cs.T_0_0_1, cs.T_0_0_0, cs.C_0_0, cs.T_0_0_0, cs.C_0_0, cs.T_0_0_0, cs.C_0_0]
]

pulser2 = [
    [cs.U, cs.T_0_0_0, cs.T_0_0_0, cs.T_0_0_0, cs.T_0_0_0, cs.T_0_0_0],
    [cs.U, cs.T_0_1_0, cs.U, cs.T_0_1_0, cs.U, cs.C_0_0],
    [cs.U, cs.T_0_1_0, cs.U, cs.T_0_1_0, cs.T_0_0_0, cs.T_0_1_0],
    [cs.U, cs.T_0_1_0, cs.U, cs.T_0_1_0, cs.T_0_1_0, cs.T_0_2_0],
    [cs.U, cs.T_0_1_0, cs.U, cs.T_0_1_0, cs.T_0_1_0, cs.T_0_2_0],
    [cs.U, cs.T_0_1_0, cs.T_0_0_0, cs.T_0_1_0, cs.T_0_0_0, cs.T_0_1_0],
    [cs.U, cs.T_0_1_0, cs.T_0_1_0, cs.T_0_2_0, cs.T_0_1_0, cs.T_0_2_0],
    [cs.T_0_0_1, cs.C_0_0, cs.T_0_0_0, cs.C_0_0, cs.T_0_0_0, cs.C_0_0],
]

ca = CellArray(7, 7, 10, 10, Rule(), pulser2, (1, 1))

while True:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit()

    cell_surf = ca.draw()
    cell_surf = pygame.transform.scale(cell_surf, (700, 700))
    window_surface.blit(cell_surf, (0, 0))

    sleep(1)
    pygame.display.flip()

    ca.evolve()
