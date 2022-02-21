class CellExNeighborhood:

    def __init__(self, m, t, r, b, l, tr, br, bl, tl):
        self.m = m
        self.t = t
        self.r = r
        self.b = b
        self.l = l
        self.tl = tl
        self.tr = tr
        self.br = br
        self.bl = bl

    def tuple(self):
        return self.m, self.t, self.r, self.b, self.l, self.tl, self.tr, self.br, self.bl
