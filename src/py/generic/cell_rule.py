from src.py.generic.cell_neighborhood import CellNeighborhood


class CellRule:

    def __init__(self, filename: str, cell_state_class):
        f = open(filename, 'r')
        self.rules = {}
        for line in f.readlines():
            c, t, r, b, l, d = (cell_state_class(int(ch)) for ch in line[:6])
            self.rules[(c, t, r, b, l)] = d
            self.rules[(c, l, t, r, b)] = d
            self.rules[(c, b, l, t, r)] = d
            self.rules[(c, r, b, l, t)] = d

    def apply(self, cn: CellNeighborhood):
        return self.rules[cn.tuple()]
