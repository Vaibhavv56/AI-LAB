

:- dynamic(known/1).       % Facts for symptoms user has
:- dynamic(not_known/1).   % Facts for symptoms user does NOT have

% Ask the user about a symptom
ask(Symptom) :-
    known(Symptom), !.
ask(Symptom) :-
    not_known(Symptom), !, fail.
ask(Symptom) :-
    format('Do you have ~w? (yes/no): ', [Symptom]),
    read(Response),
    nl,
    ( Response == yes -> assertz(known(Symptom));
      assertz(not_known(Symptom)), fail ).

% Check if user has the symptom
has_symptom(S) :- ask(S).

% Knowledge Base: Symptoms of diseases
symptom(flu, fever).
symptom(flu, head_ache).
symptom(flu, runny_nose).

symptom(cold, cough).
symptom(cold, sneezing).
symptom(cold, runny_nose).


% Rule: Disease is diagnosed if all its symptoms are present
disease(D) :-
    symptom(D, _),
    \+ (symptom(D, S), \+ has_symptom(S)).

% Start the expert system
start :-
    retractall(known(_)),
    retractall(not_known(_)),
    write('--- Simple Medical Expert System ---'), nl,
    write('Answer the following questions:'), nl, nl,
    (   disease(D) ->
        format('You may have ~w.~n', [D]);
        write('Sorry, no diagnosis could be made based on the given symptoms.'), nl
    ),
    write('--- End ---'), nl.
