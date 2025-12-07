/* ===== Small Bird Knowledge Base ===== */

% --- Basic birds ---
bird(sparrow).
bird(eagle).
bird(penguin).
bird(duck).

% --- Abilities ---
can_fly(sparrow).
can_fly(eagle).
can_fly(duck).

cannot_fly(penguin).

% --- Habitat ---
aquatic(duck).
aquatic(penguin).

% --- Diet ---
carnivore(eagle).
carnivore(penguin).
omnivore(sparrow).
omnivore(duck).

/* ===== Classification Rules ===== */

flying_bird(X) :-
    bird(X),
    can_fly(X).

non_flying_bird(X) :-
    bird(X),
    cannot_fly(X).

aquatic_bird(X) :-
    bird(X),
    aquatic(X).

predator_bird(X) :-
    bird(X),
    carnivore(X).

omnivore_bird(X) :-
    bird(X),
    omnivore(X).

can_fly_classify(X) :-
    bird(X),
    can_fly(X),
    write(X), write(' can fly.'), nl.

can_fly_classify(X) :-
    bird(X),
    cannot_fly(X),
    write(X), write(' cannot fly.'),nl.