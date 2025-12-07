/* ===== Simple Family Tree ===== */

% --- Gender ---
male(john).
male(david).
male(sam).

female(mary).
female(susan).
female(anu).

% --- Parent(Parent, Child) ---
parent(john, david).
parent(john, susan).
parent(mary, david).
parent(mary, susan).

parent(david, sam).
parent(anu, sam).

/* ===== Rules ===== */

% Father / Mother
father(X, Y) :-
    male(X),
    parent(X, Y).

mother(X, Y) :-
    female(X),
    parent(X, Y).

% Siblings
sibling(X, Y) :-
    parent(P, X),
    parent(P, Y),
    X \= Y.

brother(X, Y) :-
    male(X),
    sibling(X, Y).

sister(X, Y) :-
    female(X),
    sibling(X, Y).

% Grandparent
grandparent(X, Y) :-
    parent(X, Z),
    parent(Z, Y).

% Uncle / Aunt
uncle(X, Y) :-
    brother(X, P),
    parent(P, Y).

aunt(X, Y) :-
    sister(X, P),
    parent(P, Y).

% Ancestor
ancestor(X, Y) :-
    parent(X, Y).
ancestor(X, Y) :-
    parent(X, Z),
    ancestor(Z, Y).
