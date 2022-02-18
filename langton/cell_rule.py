from typing import Tuple

from langton.cell_state import CellState


class CellRule:

    def __init__(self, filename : str):
        f = open(filename, 'r')
        self.rules = {}
        for line in f.readlines():
            c, t, r, b, l, d = (CellState(int(ch)) for ch in line[:6])
            self.rules[(c, t, r, b, l)] = d
            self.rules[(c, l, t, r, b)] = d
            self.rules[(c, b, l, t, r)] = d
            self.rules[(c, r, b, l, t)] = d

    def apply(self, states: Tuple):

        return self.rules[states]
