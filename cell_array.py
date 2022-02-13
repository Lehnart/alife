import pygame

from cell import Cell
from cell_neighborhood import CellNeighborhood
from cell_state import CellState


class CellArray:

    def __init__(self, cell_width, cell_height, n_row, n_col, rule):
        self.cell_width = cell_width
        self.cell_height = cell_height
        self.n_row = n_row
        self.n_col = n_col
        self.rule = rule
        self.cells = [[Cell(i * cell_width, j * cell_height, CellState.T_0_0_0) for i in range(n_col)] for j in range(n_row)]

        for i in range(n_col):
            self.cells[0][i] = Cell(i * cell_width, 0, CellState.T_0_3_1)
            self.cells[n_row - 1][i] = Cell(i * cell_width, (n_row - 1) * cell_height, CellState.T_0_1_1)

        for j in range(n_row):
            self.cells[j][0] = Cell(0, j * cell_height, CellState.C_1_0)
            self.cells[j][n_col - 1] = Cell((n_col - 1) * cell_width, j * cell_height, CellState.T_0_2_1)

        self.cells[5][5] = Cell(5 * cell_width, 5 * cell_height, CellState.U)

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
