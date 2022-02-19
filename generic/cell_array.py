from typing import List, Tuple

from generic.cell import Cell
from generic.cell_neighborhood import CellNeighborhood
from generic.cell_rule import CellRule


class CellArray:

    def __init__(self, filename: str, cell_state_class):
        self.array = []
        self.cell_state_class = cell_state_class
        f = open(filename, "r")
        for line in f.readlines():
            line = line.strip()
            row = [Cell(i, len(self.array), cell_state_class(int(c))) for i, c in enumerate(line)]
            self.array.append(row)

    def dimension(self) -> Tuple[int, int]:
        return len(self.array[0]), len(self.array)

    def cells(self) -> List[Cell]:
        return [c for row in self.array for c in row]

    def get_cell_state(self, x: int, y: int):
        if x < 0 or x >= len(self.array[0]) or y < 0 or y >= len(self.array):
            return self.cell_state_class(0)

        return self.array[y][x].state

    def neighborhood(self, cell: Cell) -> CellNeighborhood:
        x, y = cell.x0, cell.y0

        m = self.get_cell_state(x, y)
        t = self.get_cell_state(x, y - 1)
        r = self.get_cell_state(x + 1, y)
        b = self.get_cell_state(x, y + 1)
        l = self.get_cell_state(x - 1, y)

        return CellNeighborhood(m, t, r, b, l)

    def evolve(self, rule: CellRule):
        next_cells_states = []
        for cell in self.cells():
            n = self.neighborhood(cell)
            s = rule.apply(n.tuple())
            next_cells_states.append(s)

        for i, cell in enumerate(self.cells()):
            cell.state = next_cells_states[i]

    def show(self):
        for row in self.array:
            c_list = "".join([str(c.state.value) for c in row])
            c_list = c_list.replace("0", " ")
            print(c_list)
