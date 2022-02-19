from generic.cell_array import CellArray
from generic.cell_drawer import CellDrawer
from generic.cell_rule import CellRule
from langton.cell_state import CellState

rule = CellRule("rule.txt", CellState)
array = CellArray("array.txt", CellState)

w, h = array.dimension()
drawer = CellDrawer((w * 4, h * 4), 4)

while True:
    array.evolve(rule)
    drawer.draw(array)
