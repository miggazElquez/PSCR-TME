TME 4
=====

Q2)
---

Le comportement est correct, il n'y a pas de dataraces.


Q5)
---

Le mutex n'est pas réentrant : une fois qu'on a lock dans transfert, on ne peut plus le reprendre dans débiter.

Q6)
---

Si un thread veut faire 0 -> 1, et un autre 1 -> 0, il peut y avoir un deadlock.

Q7)
---

Il peut y avoir une transaction pendant qu'on fait la somme des soldes.

Q8)
---

