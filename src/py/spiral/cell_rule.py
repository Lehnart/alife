import bisect
import random


class CellRule:

    def __init__(self, cell_state_class):
        self.cls = cell_state_class
        self.decay_proba = 0.2
        self.claim_empty = 11
        self.claim_cell = 1
        self.claim_hyper = 100

    def apply(self, cn):
        states = cn.tuple()
        if states[0] != 0:
            r = random.random()
            if r < self.decay_proba:
                return self.cls(0)
            return states[0]

        else:
            m, t, r, b, l, tl, tr, br, bl = states
            hc = {0: 7, 1: 5, 2: 1, 3: 2, 4: 3, 5: 4}

            d = {c: 0 for c in self.cls}
            d[0] = self.claim_empty

            d[t] += self.claim_cell
            if hc[t] == tl: d[t] += self.claim_hyper
            if hc[t] == tr: d[t] += self.claim_hyper
            if hc[t] == l: d[t] += self.claim_hyper
            if hc[t] == r: d[t] += self.claim_hyper

            d[l] += self.claim_cell
            if hc[l] == tl: d[l] += self.claim_hyper
            if hc[l] == bl: d[l] += self.claim_hyper
            if hc[l] == t: d[l] += self.claim_hyper
            if hc[l] == b: d[l] += self.claim_hyper

            d[b] += self.claim_cell
            if hc[b] == l: d[b] += self.claim_hyper
            if hc[b] == r: d[b] += self.claim_hyper
            if hc[b] == bl: d[b] += self.claim_hyper
            if hc[b] == br: d[b] += self.claim_hyper

            d[r] += self.claim_cell
            if hc[r] == br: d[r] += self.claim_hyper
            if hc[r] == tr: d[r] += self.claim_hyper
            if hc[r] == t: d[r] += self.claim_hyper
            if hc[r] == b: d[r] += self.claim_hyper

            somm = sum(d[s] for s in d)
            probas = [0.]
            for s in d:
                probas.append(probas[-1] + (d[s] / somm))

            i = bisect.bisect_left(probas, random.random())

            return self.cls(i - 1)
