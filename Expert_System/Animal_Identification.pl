% ===== Simple Animal Expert System (Short Version) =====

:- dynamic known/2.

start :-
    retractall(known(_, _)),
    writeln('=== Animal Expert System ==='),
    writeln('Answer with yes. or no.'),
    nl,
    (   animal(Animal)
    ->  format('I think the animal is: ~w~n', [Animal])
    ;   writeln('Sorry, I could not identify the animal.')
    ),
    nl.

% ------------ Animal rules ------------

animal(tiger) :-
    mammal,
    carnivore,
    has_stripes.

animal(lion) :-
    mammal,
    carnivore,
    has_mane.

animal(elephant) :-
    mammal,
    herbivore,
    very_large,
    has_trunk.

animal(dog) :-
    mammal,
    carnivore,
    domestic,
    barks.

animal(cat) :-
    mammal,
    carnivore,
    domestic,
    meows.

animal(eagle) :-
    bird,
    carnivore,
    flies.

% ------------ Category rules ------------

mammal  :- ask(has_hair).
bird    :- ask(has_feathers).

carnivore   :- ask(eats_meat).
herbivore   :- ask(eats_plants).

has_stripes :- ask(has_stripes).
has_mane    :- ask(has_mane).
has_trunk   :- ask(has_trunk).
very_large  :- ask(is_very_large).
domestic    :- ask(is_domestic).
barks       :- ask(barks).
meows       :- ask(meows).
flies       :- ask(can_fly).

% ------------ Asking / memory ------------

ask(Prop) :-
    known(Prop, yes), !.

ask(Prop) :-
    known(Prop, no), !, fail.

ask(Prop) :-
    format('Does the animal have property "~w"? (yes/no): ', [Prop]),
    read(Ans),
    ( Ans == yes
    -> assertz(known(Prop, yes))
    ;  assertz(known(Prop, no)), fail
).
