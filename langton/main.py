from langton.cell_array import CellArray
from langton.cell_drawer import CellDrawer
from langton.cell_rule import CellRule

rule = CellRule("rule.txt")
array = CellArray("array.txt")

w, h = array.dimension()
drawer = CellDrawer((w * 4, h * 4), 4)

while True:
    array.evolve(rule)
    drawer.draw(array)
