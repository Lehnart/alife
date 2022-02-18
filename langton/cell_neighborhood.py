from langton.cell_state import CellState


class CellNeighborhood:

    def __init__(self, m: CellState, t: CellState, r: CellState, b: CellState, l: CellState):
        self.m = m
        self.t = t
        self.r = r
        self.b = b
        self.l = l

    def tuple(self):
        return self.m, self.t, self.r, self.b, self.l
