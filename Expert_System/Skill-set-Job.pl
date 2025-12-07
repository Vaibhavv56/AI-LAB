% ============================
% Short Skillset–Job Matching ES
% ============================

:- dynamic known/3.

start :-
    writeln('=== Skillset – Job Matching Expert System ==='),
    writeln('Answer with yes. / no.'),
    nl,
    reset_answers,
    findall(JobId, fits(JobId), Jobs),
    nl,
    (   Jobs == []
    ->  writeln('No matching job found based on your current skills.')
    ;   writeln('Based on your skills, you may be suitable for:'),
        print_jobs(Jobs)
    ),
    nl,
    writeln('Thank you for using the expert system !').

% -------- Jobs (reduced) --------

job(web_dev,        'Web Developer').
job(data_scientist, 'Data Scientist').
job(sys_admin,      'System Administrator').

required_skills(web_dev,
    [ html, css, javascript ]).

required_skills(data_scientist,
    [ python, statistics, sql ]).

required_skills(sys_admin,
    [ linux, networking_basics, troubleshooting ]).

% -------- Matching rule --------

fits(JobId) :-
    required_skills(JobId, SkillList),
    all_skills_present(SkillList).

all_skills_present([]).
all_skills_present([Skill | Rest]) :-
    has_skill(Skill),
    all_skills_present(Rest).

% -------- Asking about skills --------

has_skill(Skill) :-
    known(yes, Skill, user), !.
has_skill(Skill) :-
    known(no, Skill, user), !, fail.
has_skill(Skill) :-
    ask_skill(Skill).

ask_skill(Skill) :-
    format('Do you have skill "~w"? (yes/no): ', [Skill]),
    read(Response),
    nl,
    ( Response == yes ; Response == y ->
        asserta(known(yes, Skill, user))
    ;   asserta(known(no, Skill, user)), fail ).

% -------- Utils --------

reset_answers :-
    retractall(known(_, _, _)).

print_jobs([]).
print_jobs([JobId | Rest]) :-
    job(JobId, Name),
    format('- ~w (~w)~n', [Name, JobId]),
    print_jobs(Rest).
