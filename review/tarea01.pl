% EJERCICIO 1: FAMILIA SIMPSON
% Se reescribe usando estructuras y listas para representar
% la información de cada persona y sus relaciones parentales.

% Estructura: persona(Nombre, [padre(Padre), madre(Madre)])
persona(herbert, [padre(abraham), madre(mona)]).
persona(homero, [padre(abraham), madre(mona)]).
persona(marge, [padre(clancy), madre(jacqueline)]).
persona(patty, [padre(clancy), madre(jacqueline)]).
persona(selma, [padre(clancy), madre(jacqueline)]).
persona(bart, [padre(homero), madre(marge)]).
persona(lisa, [padre(homero), madre(marge)]).
persona(maggie, [padre(homero), madre(marge)]).
persona(ling, [madre(selma)]).

% Se mantienen las consultas originales mediante las reglas que
% extraen la información de la estructura/lista.
padre(X, Y) :-
    persona(Y, Relaciones),
    miembro(padre(X), Relaciones).

madre(X, Y) :-
    persona(Y, Relaciones),
    miembro(madre(X), Relaciones).

% Una persona es progenitor si es padre o madre.
progenitor(X, Y) :-
    padre(X, Y).

progenitor(X, Y) :-
    madre(X, Y).

% Abuelo.
abuelo(X, Z) :-
    padre(X, Y),
    progenitor(Y, Z).

% Abuela.
abuela(X, Z) :-
    madre(X, Y),
    progenitor(Y, Z).

% Consultas originales:
% -?- abuelo(X, bart).
% -?- abuela(X, bart).

% ------------------------------------------------------------------
% EJERCICIO 2: CRIMINAL
% Se conserva la misma lógica de inferencia, sin cambiar
% la consulta principal.

estadounidense(west).

hostil(corea_del_sur).

arma(misiles).

vendio(west, misiles, corea_del_sur).

criminal(X) :-
    estadounidense(X),
    vendio(X, Y, Z),
    arma(Y),
    hostil(Z).

% -?- criminal(west).
