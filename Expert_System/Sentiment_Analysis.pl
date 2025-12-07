:- dynamic has/1.   % Allow adding/removing facts during runtime

% ---- Knowledge Base ----
feature(positive, happy).
feature(positive, joyful).
feature(positive, excited).
feature(positive, wonderful).
feature(positive, pleasant).

feature(negative, sad).
feature(negative, angry).
feature(negative, terrible).
feature(negative, horrible).
feature(negative, disappointed).

feature(neutral, okay).
feature(neutral, average).
feature(neutral, fine).
feature(neutral, normal).
feature(neutral, unsure).

% ---- Ask user about emotion words ----
ask(Feature) :-
    format('Do you feel ~w? (yes/no): ', [Feature]),
    read(Response),
    (Response == yes -> assert(has(Feature)) ; true).

% ---- Check if all features of sentiment are present ----
has_all_features(Sentiment) :-
    feature(Sentiment, Feature),
    \+ has(Feature),
    !, fail.
has_all_features(_).

% ---- Identify sentiment ----
analyze(Sentiment) :-
    feature(Sentiment, _),
    has_all_features(Sentiment).

% ---- Start the Expert System ----
start :-
    retractall(has(_)),  % clear previous responses
    write('--- Sentiment Analysis Expert System ---'), nl,
    write('Answer the following questions with yes. or no.'), nl,
    forall(feature(_, F), (ask(F))),
    (analyze(S) ->
        format('Your sentiment appears to be ~w.~n', [S])
    ;
        write('No clear sentiment identified based on your responses.'), nl).
