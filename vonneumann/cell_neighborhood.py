class CellNeighborhood:

    def __init__(self, cells):
        self.tl = cells[0].state
        self.tm = cells[1].state
        self.tr = cells[2].state
        self.ml = cells[3].state
        self.mm = cells[4].state
        self.mr = cells[5].state
        self.bl = cells[6].state
        self.bm = cells[7].state
        self.br = cells[8].state
