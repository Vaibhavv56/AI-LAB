% Gender facts
male(john).
male(david).
male(raj).

female(mary).
female(susan).
female(rita).

% Parent relationships
parent(john, mary).
parent(john, david).
parent(mary, susan).
parent(mary, raj).
parent(rita, mary).

% X is the father of Y if X is male and X is a parent of Y
father(X, Y) :- male(X), parent(X, Y).

% X is the mother of Y if X is female and X is a parent of Y
mother(X, Y) :- female(X), parent(X, Y).

% X is grandparent of Y if X is parent of Z and Z is parent of Y
grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

% X is sibling of Y if they share the same parent and are not the same person
sibling(X, Y) :- parent(Z, X), parent(Z, Y), X \= Y.

% brother and sister
brother(X, Y) :- male(X), sibling(X, Y).
sister(X, Y) :- female(X),sibling(X, Y).

===============================================================2code=======================
% --- Facts ---
father(john, david).
father(john, emma).
mother(susan, david).
mother(susan, emma).

father(david, lily).
mother(anna, lily).

% --- Rules ---
parent(X,Y) :- father(X,Y).
parent(X,Y) :- mother(X,Y).

sibling(X,Y) :- parent(P,X), parent(P,Y), X \= Y.

grandfather(X,Y) :- father(X,Z), parent(Z,Y).
grandmother(X,Y) :- mother(X,Z), parent(Z,Y).

% --- Helper to check relationships ---
check_relation(father, X, Y) :- father(X,Y).
check_relation(mother, X, Y) :- mother(X,Y).
check_relation(sibling, X, Y) :- sibling(X,Y).
check_relation(grandfather, X, Y) :- grandfather(X,Y).
check_relation(grandmother, X, Y) :- grandmother(X,Y).

% --- Start Expert System ---
start :-
    write('--- Family Tree Expert System ---'), nl,
    write('Answer names in lowercase, ending with a period (e.g., john.)'), nl,
    write('Which relationship do you want to check? (father/mother/sibling/grandfather/grandmother)'), nl,
    read(Rel),
    write('Enter the first person: '), read(P1),
    write('Enter the second person: '), read(P2),
    (   check_relation(Rel, P1, P2)
    ->  write('Yes, the relationship exists.'), nl
    ;   write('No such relationship found.'), nl
).
