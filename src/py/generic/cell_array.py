import bisect
import random
from typing import List, Tuple

from src.py.generic.cell import Cell
from src.py.generic.cell_ex_neighborhood import CellExNeighborhood
from src.py.generic.cell_neighborhood import CellNeighborhood
from src.py.generic.cell_rule import CellRule


class CellArray:

    def __init__(self, cell_state_class):
        self.array = []
        self.cell_state_class = cell_state_class
        self.neighborhood_func = self.neighborhood

    def set_ex_neighborhood(self):
        self.neighborhood_func = self.ex_neighborhood

    @classmethod
    def copy(cls, ca):
        ca = CellArray(ca.cell_state_class)
        for row in ca.array:
            ca.array.append([])
            for cell in row:
                ca.array[-1].append(Cell.copy(cell))
        return ca

    @classmethod
    def from_file(cls, filename: str, cell_state_class):
        ca = CellArray(cell_state_class)
        f = open(filename, "r")
        for line in f.readlines():
            line = line.strip()
            row = [Cell(i, len(ca.array), cell_state_class(int(c))) for i, c in enumerate(line)]
            ca.array.append(row)
        return ca

    @classmethod
    def random(cls, w: int, h: int, values: Tuple, cell_state_class, cumulative_prob=None):
        if cumulative_prob is None:
            cumulative_prob = [0.]
            for i in range(len(values)):
                cumulative_prob.append(cumulative_prob[-1] + (1. / len(values)))

        ca = CellArray(cell_state_class)
        for y in range(h):
            ca.array.append([])
            for x in range(w):
                r = random.random()
                i = bisect.bisect_left(cumulative_prob, r)
                state = cell_state_class(values[i - 1])
                ca.array[-1].append(Cell(x, y, state))
        return ca

    def dimension(self) -> Tuple[int, int]:
        return len(self.array[0]), len(self.array)

    def cells(self) -> List[Cell]:
        return [c for row in self.array for c in row]

    def get_cell_state(self, x: int, y: int):
        if x < 0 or x >= len(self.array[0]) or y < 0 or y >= len(self.array):
            return self.cell_state_class(0)

        return self.array[y][x].state

    def set_cell_state(self, x: int, y: int, s: int):
        if x < 0 or x >= len(self.array[0]) or y < 0 or y >= len(self.array):
            return

        self.array[y][x].state = self.cell_state_class(s)

    def neighborhood(self, cell: Cell) -> CellNeighborhood:
        x, y = cell.x0, cell.y0

        m = self.get_cell_state(x, y)
        t = self.get_cell_state(x, y - 1)
        r = self.get_cell_state(x + 1, y)
        b = self.get_cell_state(x, y + 1)
        l = self.get_cell_state(x - 1, y)

        return CellNeighborhood(m, t, r, b, l)

    def ex_neighborhood(self, cell: Cell) -> CellExNeighborhood:
        x, y = cell.x0, cell.y0

        m = self.get_cell_state(x, y)
        t = self.get_cell_state(x, y - 1)
        r = self.get_cell_state(x + 1, y)
        b = self.get_cell_state(x, y + 1)
        l = self.get_cell_state(x - 1, y)
        tl = self.get_cell_state(x - 1, y - 1)
        tr = self.get_cell_state(x + 1, y - 1)
        br = self.get_cell_state(x + 1, y + 1)
        bl = self.get_cell_state(x - 1, y + 1)

        return CellExNeighborhood(m, t, r, b, l, tl, tr, br, bl)

    def evolve(self, rule: CellRule):
        next_cells_states = []
        for cell in self.cells():
            n = self.neighborhood_func(cell)
            s = rule.apply(n)
            next_cells_states.append(s)

        for i, cell in enumerate(self.cells()):
            cell.state = next_cells_states[i]


    def show(self):
        for row in self.array:
            c_list = "".join([str(c.state.value) for c in row])
            c_list = c_list.replace("0", " ")
            print(c_list)
