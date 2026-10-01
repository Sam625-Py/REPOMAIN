
% BACKTRACKING Y SLD
% Grafo dirigido de ciudades
% HECHOS: conexion(Origen, Destino, Costo)


conexion(vancouver, edmonton, 16).
conexion(vancouver, calgary, 13).

conexion(calgary, edmonton, 4).
conexion(calgary, regina, 14).

conexion(edmonton, saskatoon, 12).

conexion(saskatoon, calgary, 9).
conexion(saskatoon, winnipeg, 20).

conexion(regina, saskatoon, 7).
conexion(regina, winnipeg, 4).



% REGLA 1: determinar si un nodo tiene aristas


tiene_aristas(X) :-
    conexion(X, _, _).



% REGLA 2: obtener los nodos conectados
% y el costo de cada conexión


conectado_directamente(X, Y, Costo) :-
    conexion(X, Y, Costo).



% REGLA 3: determinar si existe un camino
% entre dos nodos


camino(X, Z, Camino) :-
    camino_aux(X, Z, [X], Camino).

camino_aux(Z, Z, Visitados, Visitados).

camino_aux(X, Z, Visitados, Camino) :-
    conexion(X, Y, _),
    \+ member(Y, Visitados),
    camino_aux(Y, Z, [Y|Visitados], Camino).



% REGLA 4: determinar el costo para ir
% de X a Z pasando por Y


costo_pasando_por(X, Z, Y, CostoTotal) :-
    conexion(X, Y, CostoXY),
    conexion(Y, Z, CostoYZ),
    CostoTotal is CostoXY + CostoYZ.



% REGLA 5: verificar si es posible viajar
% de X a Z


es_posible_viajar(X, Z) :-
    camino(X, Z, _).




%conexion Saskatoon → Vancouver
%"?- es_posible_viajar(saskatoon, vancouver).
%el resultado es false, ya que no hay un camino directo ni indirecto desde Saskatoon hasta Vancouver en el grafo definido.

%nodos conectados a regina y costos de cada conexión
%"?- conectado_directamente(regina, Nodo, Costo).



%regla probar si nodo tiene aristas
%"?- tiene_aristas(calgary).

%Ver todos los nodos que tienen aristas
%"?- tiene_aristas(X).


%Costo de ir de X a Z pasando por Y
%"?- costo_pasando_por(X, Z, Y, Costo).

%existe camino de edmonton a calgary
%"?- es_posible_viajar(edmonton, calgary).
%el resultado es false, ya que no hay un camino directo ni indirecto desde Edmonton hasta Calgary en el grafo definido.