import random

from src.py.generic.cell_array import CellArray
from src.py.generic.cell_drawer import CellDrawer
from src.py.spiral.cell_rule import CellRule
from src.py.spiral.cell_state import CellState


def run():
    array = CellArray.random(150, 150, (0, 1, 2, 3, 4, 5), CellState, (0., 0.5, 0.6, 0.7, 0.8, 0.9, 1.))
    array.set_ex_neighborhood()
    rule = CellRule(CellState)
    w, h = array.dimension()
    drawer = CellDrawer((w * 3, h * 3), 3)

    i = 0
    while True:
        print(i)
        i += 1
        drawer.draw(array)
        array.evolve(rule)

        w, h = array.dimension()
        for x in range(0, w, 2):
            for y in range(0, h, 2):
                tl = array.get_cell_state(x, y)
                tr = array.get_cell_state(x + 1, y)
                bl = array.get_cell_state(x, y + 1)
                br = array.get_cell_state(x + 1, y + 1)

                if random.random() < 0.5:
                    array.set_cell_state(x, y, tr)
                    array.set_cell_state(x, y + 1, tl)
                    array.set_cell_state(x + 1, y + 1, bl)
                    array.set_cell_state(x + 1, y, br)

                else:
                    array.set_cell_state(x, y, bl)
                    array.set_cell_state(x, y + 1, br)
                    array.set_cell_state(x + 1, y + 1, tr)
                    array.set_cell_state(x + 1, y, tl)

        for x in range(1, w, 2):
            for y in range(1, h, 2):
                tl = array.get_cell_state(x, y)
                tr = array.get_cell_state(x + 1, y)
                bl = array.get_cell_state(x, y + 1)
                br = array.get_cell_state(x + 1, y + 1)

                if random.random() < 0.5:
                    array.set_cell_state(x, y, tr)
                    array.set_cell_state(x, y + 1, tl)
                    array.set_cell_state(x + 1, y + 1, bl)
                    array.set_cell_state(x + 1, y, br)

                else:
                    array.set_cell_state(x, y, bl)
                    array.set_cell_state(x, y + 1, br)
                    array.set_cell_state(x + 1, y + 1, tr)
                    array.set_cell_state(x + 1, y, tl)


if __name__ == "__main__":
    run()
