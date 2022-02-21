from src.py.generic.cell_array import CellArray
from src.py.generic.cell_drawer import CellDrawer
from src.py.generic.cell_rule import CellRule
from src.py.byl.cell_state import CellState

rule = CellRule("rule.txt", CellState)
array = CellArray.from_file("array.txt", CellState)

w, h = array.dimension()
drawer = CellDrawer((w * 4, h * 4), 4)

i = 0
while True:
    drawer.draw(array)
    array.evolve(rule)