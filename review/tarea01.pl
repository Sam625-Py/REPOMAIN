
% HECHOS


% Abraham y Mona
padre(abraham, herbert).
padre(abraham, homero).

madre(mona, herbert).
madre(mona, homero).

% Clancy y Jacqueline
padre(clancy, marge).
padre(clancy, patty).
padre(clancy, selma).

madre(jacqueline, marge).
madre(jacqueline, patty).
madre(jacqueline, selma).

% Homero y Marge
padre(homero, bart).
padre(homero, lisa).
padre(homero, maggie).

madre(marge, bart).
madre(marge, lisa).
madre(marge, maggie).

% Selma
madre(selma, ling).


% REGLAS


% Una persona es progenitor si es padre o madre
progenitor(X, Y) :-
    padre(X, Y).

progenitor(X, Y) :-
    madre(X, Y).


% Abuelo
abuelo(X, Z) :-
    padre(X, Y),
    progenitor(Y, Z).


% Abuela
abuela(X, Z) :-
    madre(X, Y),
    progenitor(Y, Z).