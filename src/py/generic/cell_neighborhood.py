class CellNeighborhood:

    def __init__(self, m, t, r, b, l):
        self.m = m
        self.t = t
        self.r = r
        self.b = b
        self.l = l

    def tuple(self):
        return self.m, self.t, self.r, self.b, self.l
