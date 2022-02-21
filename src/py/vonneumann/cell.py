from cell_state import CellState


class Cell:

    def __init__(self, x0: int, y0: int, state: CellState):
        self.x0 = x0
        self.y0 = y0

        self.state = state

    def draw_cell(self, ca):
        self.state.draw_state(self.x0, self.y0, ca)

    @classmethod
    def copy(cls, cell):
        return Cell(cell.x0, cell.y0, cell.state)

    def __eq__(self, other):
        return self.x0 == other.x0 and self.y0 == other.y0 and self.state == other.state
