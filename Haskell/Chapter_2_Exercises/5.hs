First:

init xs = reverse(tail(reverse(xs)))

Seconde:

init xs = if (length xs == 1) then [] else [head(xs)] ++ init(tail(xs))
