
% BACKTRACKING Y SLD
% Grafo dirigido de ciudades usando estructuras y listas.
% Cada ciudad guarda una lista de aristas: arista(Destino, Costo)

ciudad(vancouver, [arista(edmonton, 16), arista(calgary, 13)]).
ciudad(calgary, [arista(edmonton, 4), arista(regina, 14)]).
ciudad(edmonton, [arista(saskatoon, 12)]).
ciudad(saskatoon, [arista(calgary, 9), arista(winnipeg, 20)]).
ciudad(regina, [arista(saskatoon, 7), arista(winnipeg, 4)]).

% REGLA 1: determinar si un nodo tiene aristas
% (mantiene la consulta original: ?- tiene_aristas(calgary).)
tiene_aristas(X) :-
    ciudad(X, Rutas),
    Rutas \= [].

% REGLA 2: obtener los nodos conectados y el costo de cada conexión
% (mantiene la consulta original: ?- conectado_directamente(regina, Nodo, Costo).)
conectado_directamente(X, Y, Costo) :-
    ciudad(X, Rutas),
    miembro(arista(Y, Costo), Rutas).

% REGLA 3: determinar si existe un camino entre dos nodos
% (mantiene la consulta original: ?- es_posible_viajar(edmonton, calgary).)
camino(X, Z, Camino) :-
    camino_aux(X, Z, [X], Camino).

camino_aux(Z, Z, Visitados, Visitados).

camino_aux(X, Z, Visitados, Camino) :-
    ciudad(X, Rutas),
    miembro(arista(Y, _), Rutas),
    \+ miembro(Y, Visitados),
    camino_aux(Y, Z, [Y | Visitados], Camino).

% REGLA 4: determinar el costo para ir de X a Z pasando por Y
costo_pasando_por(X, Z, Y, CostoTotal) :-
    conectado_directamente(X, Y, CostoXY),
    conectado_directamente(Y, Z, CostoYZ),
    CostoTotal is CostoXY + CostoYZ.

% REGLA 5: verificar si es posible viajar de X a Z
es_posible_viajar(X, Z) :-
    camino(X, Z, _).

% Consultas originales:
% -?- es_posible_viajar(saskatoon, vancouver).
% -?- conectado_directamente(regina, Nodo, Costo).
% -?- tiene_aristas(calgary).
% -?- tiene_aristas(X).
% -?- costo_pasando_por(X, Z, Y, Costo).
% -?- es_posible_viajar(edmonton, calgary).

