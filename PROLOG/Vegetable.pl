/* ====== Small Fruit / Vegetable KB ====== */

% --- BASIC FACTS ---

% fruit/1
fruit(apple).
fruit(orange).

% vegetable/1
vegetable(carrot).
vegetable(spinach).

% --- PROPERTIES ---

% color(Item, Color).
color(apple,   red).
color(orange,  orange).
color(carrot,  orange).
color(spinach, green).

% taste(Item, Taste).
taste(apple,   sweet).
taste(orange,  sour).
taste(carrot,  mild_sweet).
taste(spinach, bitter).

% grows_on(Item, Part).
% tree, plant, root, leafy
grows_on(apple,   tree).
grows_on(orange,  tree).
grows_on(carrot,  root).
grows_on(spinach, leafy).

% seeds_inside(Item, yes/no).
seeds_inside(apple,  yes).
seeds_inside(orange, yes).
seeds_inside(carrot, no).
seeds_inside(spinach,no).

/* ====== CLASSIFICATION RULES ====== */

is_fruit(X) :-
    fruit(X).

is_vegetable(X) :-
    vegetable(X).

% Root / leafy
root_vegetable(X) :-
    vegetable(X),
    grows_on(X, root).

leafy_vegetable(X) :-
    vegetable(X),
    grows_on(X, leafy).

% Citrus fruits
citrus_fruit(X) :-
    fruit(X),
    (X = orange).

% Sweet fruits
sweet_fruit(X) :-
    fruit(X),
    taste(X, sweet).

% Green vegetables
green_vegetable(X) :-
    vegetable(X),
    color(X, green).

% General produce
produce(X) :-
    fruit(X);
    vegetable(X).


