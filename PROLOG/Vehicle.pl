/* ====== Small Vehicle Knowledge Base ====== */

% ---- BASIC VEHICLES ----
vehicle(car).
vehicle(bike).
vehicle(bus).
vehicle(boat).

% ---- WHEELS ----
wheels(car, 4).
wheels(bike, 2).
wheels(bus, 6).
wheels(boat, 0).

% ---- MEDIUM ----
% road, water
medium(car, road).
medium(bike, road).
medium(bus, road).
medium(boat, water).

% ---- ENGINE ----
engine(car, yes).
engine(bike, yes).
engine(bus, yes).
engine(boat, yes).

% ---- FUEL ----
fuel(car, petrol).
fuel(bike, petrol).
fuel(bus, diesel).
fuel(boat, diesel).

% ---- USAGE ----
usage(car, personal).
usage(bike, personal).
usage(bus, public_transport).
usage(boat, goods).

/* ====== CLASSIFICATION RULES ====== */

road_vehicle(V) :-
    vehicle(V),
    medium(V, road).

water_vehicle(V) :-
    vehicle(V),
    medium(V, water).

motor_vehicle(V) :-
    vehicle(V),
    engine(V, yes).

two_wheeler(V) :-
    vehicle(V),
    wheels(V, 2).

four_wheeler(V) :-
    vehicle(V),
    wheels(V, 4).

personal_vehicle(V) :-
    vehicle(V),
    usage(V, personal).

public_transport_vehicle(V) :-
    vehicle(V),
    usage(V, public_transport).

goods_vehicle(V) :-
    vehicle(V),
    usage(V, goods).
