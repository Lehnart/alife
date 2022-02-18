import pygame

from cell import Cell
from cell_neighborhood import CellNeighborhood
from cell_state import CellState


class CellArray:

    def __init__(self, cell_width, cell_height, n_row, n_col, rule, cells, offset=(0, 0)):
        self.cell_width = cell_width
        self.cell_height = cell_height
        self.n_row = n_row
        self.n_col = n_col
        self.rule = rule
        self.cells = [[Cell(i * cell_width, j * cell_height, CellState.U) for i in range(n_col)] for j in range(n_row)]

        x0, y0 = offset
        for j in range(len(cells)):
            for i in range(len(cells[j])):
                self.cells[j + y0][i + x0] = Cell((i + x0) * cell_width, (j + y0) * cell_height, cells[j][i])

    def draw(self):

        empty_surf = pygame.Surface((self.cell_width * self.n_col, self.cell_height * self.n_row))
        cell_array = pygame.surfarray.pixels3d(empty_surf)

        for j in range(self.n_row):
            for i in range(self.n_col):
                c = self.cells[j][i]
                c.draw_cell(cell_array)

        cell_surf = pygame.Surface((self.cell_width * self.n_col, self.cell_height * self.n_row))
        pygame.surfarray.blit_array(cell_surf, cell_array)

        return cell_surf

    def evolve(self):
        next_cells = []
        for j in range(self.n_row):
            next_cells.append([])
            for i in range(self.n_col):

                if j == 0 or j == self.n_row - 1 or i == 0 or i == self.n_col - 1:
                    next_cells[-1].append(Cell.copy(self.cells[j][i]))
                    continue

                neighbor_cells = []
                neighbor_cells.append(self.cells[j - 1][i - 1])
                neighbor_cells.append(self.cells[j - 1][i])
                neighbor_cells.append(self.cells[j - 1][i + 1])
                neighbor_cells.append(self.cells[j][i - 1])
                neighbor_cells.append(self.cells[j][i])
                neighbor_cells.append(self.cells[j][i + 1])
                neighbor_cells.append(self.cells[j + 1][i - 1])
                neighbor_cells.append(self.cells[j + 1][i])
                neighbor_cells.append(self.cells[j + 1][i + 1])

                cn = CellNeighborhood(neighbor_cells)

                state = self.rule.apply(cn)
                state = cn.mm if state is None else state
                c = Cell(self.cells[j][i].x0, self.cells[j][i].y0, state)
                next_cells[-1].append(c)

        self.cells = next_cells
