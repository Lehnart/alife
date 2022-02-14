from cell_neighborhood import CellNeighborhood
from cell_state import CellState


class AlphaTransitionRule:

    def apply(self, cn: CellNeighborhood):

        if cn.tm.is_t_bot() \
                and not cn.mm.is_t_top() \
                and cn.tm.u() != cn.mm.u() \
                and cn.tm.e() == 1:
            return CellState.U

        if cn.ml.is_t_right() \
                and not cn.mm.is_t_left() \
                and cn.ml.u() != cn.mm.u() \
                and cn.ml.e() == 1:
            return CellState.U

        if cn.bm.is_t_top() \
                and not cn.mm.is_t_bot() \
                and cn.bm.u() != cn.mm.u() \
                and cn.bm.e() == 1:
            return CellState.U

        if cn.mr.is_t_left() \
                and not cn.mm.is_t_right() \
                and cn.mr.u() != cn.mm.u() \
                and cn.mr.e() == 1:
            return CellState.U

        return None


class BetaTransitionRule:

    def apply(self, cn: CellNeighborhood):

        if (cn.tm.is_t_bot() or cn.tm.is_c_state()) \
                and cn.tm.e() == 1 \
                and not cn.mm.is_t_top():
            return cn.mm.set_e()

        if (cn.ml.is_t_right() or cn.ml.is_c_state()) \
                and cn.ml.e() == 1 \
                and not cn.mm.is_t_left():
            return cn.mm.set_e()

        if (cn.bm.is_t_top() or cn.bm.is_c_state()) \
                and cn.bm.e() == 1 \
                and not cn.mm.is_t_bot():
            return cn.mm.set_e()

        if (cn.mr.is_t_left() or cn.mr.is_c_state()) \
                and cn.mr.e() == 1 \
                and not cn.mm.is_t_right():
            return cn.mm.set_e()

        return None


class TransitionRule:

    def __init__(self):
        self.alpha_rule = AlphaTransitionRule()
        self.beta_rule = BetaTransitionRule()

    def apply(self, cn: CellNeighborhood):

        if not cn.mm.is_t_state():
            return None

        alpha = self.alpha_rule.apply(cn)
        if alpha is not None:
            return alpha

        beta = self.beta_rule.apply(cn)
        if beta is not None:
            return beta

        return cn.mm.unset_e()


class AlphaConfluentRule:

    def apply(self, cn: CellNeighborhood):

        if cn.tm.is_t_bot() \
                and cn.tm.e() == 1 \
                and cn.tm.u() == 1:
            return CellState.U

        if cn.ml.is_t_right() \
                and cn.ml.e() == 1 \
                and cn.ml.u() == 1:
            return CellState.U

        if cn.bm.is_t_top() \
                and cn.bm.e() == 1 \
                and cn.bm.u() == 1:
            return CellState.U

        if cn.mr.is_t_left() \
                and cn.mr.e() == 1 \
                and cn.mr.u() == 1:
            return CellState.U

        return None


class BetaConfluentRule:

    def apply(self, cn: CellNeighborhood):

        if cn.tm.is_t_bot() \
                and cn.tm.e() == 0 \
                and cn.tm.u() == 0:
            return None

        if cn.ml.is_t_right() \
                and cn.ml.e() == 0 \
                and cn.ml.u() == 0:
            return None

        if cn.bm.is_t_top() \
                and cn.bm.e() == 0 \
                and cn.bm.u() == 0:
            return None

        if cn.mr.is_t_left() \
                and cn.mr.e() == 0 \
                and cn.mr.u() == 0:
            return None

        if cn.tm.is_t_bot() \
                and cn.tm.e() == 1 \
                and cn.tm.u() == 0:
            if cn.mm.e_prime() == 1:
                return CellState.C_1_1
            return CellState.C_0_1

        if cn.ml.is_t_right() \
                and cn.ml.e() == 1 \
                and cn.ml.u() == 0:
            if cn.mm.e_prime() == 1 :
                return CellState.C_1_1
            return CellState.C_0_1

        if cn.bm.is_t_top() \
                and cn.bm.e() == 1 \
                and cn.bm.u() == 0:
            if cn.mm.e_prime() == 1 :
                return CellState.C_1_1
            return CellState.C_0_1

        if cn.mr.is_t_left() \
                and cn.mr.e() == 1 \
                and cn.mr.u() == 0:
            if cn.mm.e_prime() == 1 :
                return CellState.C_1_1
            return CellState.C_0_1

        return None


class ConfluentRule:

    def __init__(self):
        self.alpha_rule = AlphaConfluentRule()
        self.beta_rule = BetaConfluentRule()

    def apply(self, cn: CellNeighborhood):

        if not cn.mm.is_c_state():
            return None

        alpha = self.alpha_rule.apply(cn)
        if alpha is not None:
            return alpha

        beta = self.beta_rule.apply(cn)
        if beta is not None:
            return beta

        c = cn.mm.unset_e()
        if c.e_prime() == 1:
            return CellState.C_1_0
        else:
            return CellState.C_0_0


class AlphaUnexcitableRule:

    def apply(self, cn: CellNeighborhood):

        if cn.tm.is_t_bot() \
                and cn.tm.e() == 1:
            return CellState.S_o

        if cn.ml.is_t_right() \
                and cn.ml.e() == 1:
            return CellState.S_o

        if cn.bm.is_t_top() \
                and cn.bm.e() == 1:
            return CellState.S_o

        if cn.mr.is_t_left() \
                and cn.mr.e() == 1:
            return CellState.S_o

        return None


class UnexcitableRule:

    def __init__(self):
        self.alpha_rule = AlphaUnexcitableRule()

    def apply(self, cn: CellNeighborhood):
        if not cn.mm.is_u_state():
            return None

        alpha = self.alpha_rule.apply(cn)
        if alpha is not None:
            return alpha

        return CellState.U


class AlphaSensitizedRule:

    def apply(self, cn: CellNeighborhood):

        if cn.tm.is_t_bot() \
                and cn.tm.e() == 1:
            return cn.mm.add_1()

        if cn.ml.is_t_right() \
                and cn.ml.e() == 1:
            return cn.mm.add_1()

        if cn.bm.is_t_top() \
                and cn.bm.e() == 1:
            return cn.mm.add_1()

        if cn.mr.is_t_left() \
                and cn.mr.e() == 1:
            return cn.mm.add_1()

        return None


class SensitizedRule:

    def __init__(self):
        self.alpha_rule = AlphaSensitizedRule()

    def apply(self, cn: CellNeighborhood):
        if not cn.mm.is_s_state():
            return None

        alpha = self.alpha_rule.apply(cn)
        if alpha is not None:
            return alpha

        return cn.mm.add_0()


class Rule:

    def __init__(self):
        self.transition_rule = TransitionRule()
        self.confluent_rule = ConfluentRule()
        self.unexcitable_rule = UnexcitableRule()
        self.sensitized_rule = SensitizedRule()

    def apply(self, cn: CellNeighborhood):
        c = self.transition_rule.apply(cn)
        if c is not None:
            return c

        c = self.confluent_rule.apply(cn)
        if c is not None:
            return c

        c = self.unexcitable_rule.apply(cn)
        if c is not None:
            return c

        return self.sensitized_rule.apply(cn)
