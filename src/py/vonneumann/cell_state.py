from enum import Enum


class CellState(Enum):
    T_0_0_0 = 1
    T_0_1_0 = 2
    T_0_2_0 = 3
    T_0_3_0 = 4
    T_0_0_1 = 5
    T_0_1_1 = 6
    T_0_2_1 = 7
    T_0_3_1 = 8
    T_1_0_0 = 9
    T_1_1_0 = 10
    T_1_2_0 = 11
    T_1_3_0 = 12
    T_1_0_1 = 13
    T_1_1_1 = 14
    T_1_2_1 = 15
    T_1_3_1 = 16

    C_0_0 = 17
    C_1_0 = 18
    C_0_1 = 19
    C_1_1 = 20

    U = 21

    S_o = 22
    S_0 = 23
    S_1 = 24
    S_00 = 25
    S_01 = 26
    S_10 = 27
    S_11 = 28
    S_000 = 29

    def e(self):
        if self.value in [5, 6, 7, 8, 13, 14, 15, 16, 18, 20]:
            return 1
        if self.value in [0, 1, 2, 3, 9, 10, 11, 12, 17, 19]:
            return 0
        return None

    def e_prime(self):
        if self.value in [17, 18]:
            return 0
        if self.value in [19, 20]:
            return 1
        return None

    def u(self):
        if 1 <= self.value <= 8:
            return 0
        if 9 <= self.value <= 16:
            return 1
        return None

    def add_0(self):

        if self.value == 22:
            return CellState.S_0

        if self.value == 23:
            return CellState.S_00

        if self.value == 24:
            return CellState.S_10

        if self.value == 25:
            return CellState.S_000

        if self.value == 26:
            return CellState.T_0_3_0

        if self.value == 27:
            return CellState.T_1_1_0

        if self.value == 28:
            return CellState.T_1_3_0

        if self.value == 29:
            return CellState.T_0_0_0

        return None

    def add_1(self):

        if self.value == 22:
            return CellState.S_1

        if self.value == 23:
            return CellState.S_01

        if self.value == 24:
            return CellState.S_11

        if self.value == 25:
            return CellState.T_0_2_0

        if self.value == 26:
            return CellState.T_1_0_0

        if self.value == 27:
            return CellState.T_1_2_0

        if self.value == 28:
            return CellState.C_0_0

        if self.value == 29:
            return CellState.T_0_1_0

        return None

    def set_e(self):
        if self.value <= 4 or 9 <= self.value <= 12:
            return CellState(self.value + 4)
        return self

    def unset_e(self):
        if 5 <= self.value <= 8 or 13 <= self.value <= 16:
            return CellState(self.value - 4)
        return self

    def unset_e_prime(self):
        if self.value in [19, 20]:
            return CellState(self.value - 2)
        return self

    def is_t_right(self):
        return self.value in [1, 5, 9, 13]

    def is_t_top(self):
        return self.value in [2, 6, 10, 14]

    def is_t_left(self):
        return self.value in [3, 7, 11, 15]

    def is_t_bot(self):
        return self.value in [4, 8, 12, 16]

    def is_t_state(self):
        return 1 <= self.value <= 16

    def is_c_state(self):
        return 17 <= self.value <= 20

    def is_u_state(self):
        return self.value == 21

    def is_s_state(self):
        return self.value >= 22

    def draw_state(self, x0, y0, ca):
        if self.value <= 16:
            self._draw_t_state(x0, y0, ca)
        elif self.value <= 20:
            self._draw_c_state(x0, y0, ca)
        elif self.value == 21:
            self._draw_u_state(x0, y0, ca)
        else:
            self._draw_s_state(x0, y0, ca)

    def _draw_t_state(self, x0, y0, ca):

        input_color = (0, 128, 0)
        output_color = (128, 0, 0)

        active_color = (0, 255, 0)
        sleep_color = (255, 0, 0)
        color = active_color if self.e() == 1 else sleep_color
        ca[x0 + 0][y0 + 0] = color

        color = (0, 128, 128)
        if self.u() == 0:
            color = (128, 128, 0)

        ca[x0 + 2][y0 + 2] = color
        ca[x0 + 3][y0 + 2] = color
        ca[x0 + 4][y0 + 2] = color
        ca[x0 + 3][y0 + 3] = color
        ca[x0 + 3][y0 + 4] = color

        color = output_color if self.is_t_top() else input_color
        ca[x0 + 2][y0] = color
        ca[x0 + 3][y0] = color
        ca[x0 + 4][y0] = color

        color = output_color if self.is_t_bot() else input_color
        ca[x0 + 2][y0 + 6] = color
        ca[x0 + 3][y0 + 6] = color
        ca[x0 + 4][y0 + 6] = color

        color = output_color if self.is_t_left() else input_color
        ca[x0][y0 + 2] = color
        ca[x0][y0 + 3] = color
        ca[x0][y0 + 4] = color

        color = output_color if self.is_t_right() else input_color
        ca[x0 + 6][y0 + 2] = color
        ca[x0 + 6][y0 + 3] = color
        ca[x0 + 6][y0 + 4] = color

    def _draw_c_state(self, x0, y0, ca):
        active_color = (0, 255, 0)
        sleep_color = (255, 0, 0)
        color = active_color if self.e() == 1 else sleep_color
        ca[x0 + 0][y0 + 0] = color

        color = active_color if self.e_prime() == 1 else sleep_color
        ca[x0 + 6][y0 + 0] = color

        ca[x0 + 3][y0 + 2] = (255, 255, 255)
        ca[x0 + 4][y0 + 2] = (255, 255, 255)
        ca[x0 + 2][y0 + 3] = (255, 255, 255)
        ca[x0 + 3][y0 + 4] = (255, 255, 255)
        ca[x0 + 4][y0 + 4] = (255, 255, 255)

    def _draw_u_state(self, x0, y0, ca):
        return

    def _draw_s_state(self, x0, y0, ca):
        S_o = 22
        S_0 = 23
        S_1 = 24
        S_00 = 25
        S_01 = 26
        S_10 = 27
        S_11 = 28
        S_000 = 29

        ca[x0 + 3][y0 + 1] = (255, 255, 255)
        ca[x0 + 4][y0 + 1] = (255, 255, 255)
        ca[x0 + 2][y0 + 2] = (255, 255, 255)
        ca[x0 + 3][y0 + 3] = (255, 255, 255)
        ca[x0 + 4][y0 + 4] = (255, 255, 255)
        ca[x0 + 2][y0 + 5] = (255, 255, 255)
        ca[x0 + 3][y0 + 5] = (255, 255, 255)

        no_color = (0, 0, 0)
        zero_color = (64, 64, 64)
        one_color = (192, 192, 192)

        color = no_color
        color = zero_color if self in [CellState.S_00, CellState.S_0, CellState.S_01, CellState.S_000] else color
        color = one_color if self in [CellState.S_1, CellState.S_11, CellState.S_10] else color
        ca[x0 + 2][y0 + 6] = color

        color = no_color
        color = zero_color if self in [CellState.S_00, CellState.S_10, CellState.S_000] else color
        color = one_color if self in [CellState.S_01, CellState.S_11] else color
        ca[x0 + 3][y0 + 6] = color

        color = no_color
        color = zero_color if self in [CellState.S_00, CellState.S_10, CellState.S_000] else color
        ca[x0 + 4][y0 + 6] = color
