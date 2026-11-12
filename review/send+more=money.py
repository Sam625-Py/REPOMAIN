class CriptoaritmeticaCSP:
   

    def __init__(self):
        
        self.variables = tuple("SENDMORY")
        self.dominio = set(range(10))
        self.dominios = {letra: self.dominio.copy() for letra in self.variables}
        # S y M no pueden ser cero; M es 1 porque el resultado tiene cinco cifras.
        self.dominios["S"] = set(range(1, 10))
        self.dominios["M"] = {1}

        # Restricciones aritméticas por columna(unidades, decenas, centenas y millares).
        self.columnas = [
            ("D", "E", "Y"),
            ("N", "R", "E"),
            ("E", "O", "N"),
            ("S", "M", "O"),
        ]

    def dominios_disponibles(self, asignacion):
        
        usados = set(asignacion.values())
        disponibles = {}
        for variable in self.variables:
            if variable not in asignacion:
                disponibles[variable] = self.dominios[variable] - usados
        return disponibles

    def columnas_validas(self, asignacion):
        
        acarreo = 0
        # Solo se puede validar en orden mientras estén asignadas todas las letras
        # de la columna actual; cada resultado alimenta el acarreo siguiente.
        for sumando1, sumando2, resultado in self.columnas:
            if not all(letra in asignacion for letra in (sumando1, sumando2, resultado)):
                break
            suma = asignacion[sumando1] + asignacion[sumando2] + acarreo
            if suma % 10 != asignacion[resultado]:
                return False
            acarreo = suma // 10
        return True

    def asignacion_valida(self, asignacion):
        
        if len(asignacion) != len(self.variables):
            return False
        if len(set(asignacion.values())) != len(self.variables):
            return False
        if asignacion["S"] == 0 or asignacion["M"] == 0:
            return False
        send = int("".join(str(asignacion[c]) for c in "SEND"))
        more = int("".join(str(asignacion[c]) for c in "MORE"))
        money = int("".join(str(asignacion[c]) for c in "MONEY"))
        return send + more == money

    def seleccionar_variable(self, asignacion, disponibles):
        
        pendientes = [v for v in self.variables if v not in asignacion]
        return min(pendientes, key=lambda v: len(disponibles[v]))

    def backtracking(self, asignacion=None):
      
        if asignacion is None:
            asignacion = {"M": 1}

        if len(asignacion) == len(self.variables):
            return asignacion.copy() if self.asignacion_valida(asignacion) else None

        disponibles = self.dominios_disponibles(asignacion)
        variable = self.seleccionar_variable(asignacion, disponibles)

        for valor in sorted(disponibles[variable]):
            siguiente = asignacion.copy()
            siguiente[variable] = valor
            if self.columnas_validas(siguiente):
                solucion = self.backtracking(siguiente)
                if solucion is not None:
                    return solucion
        return None

    def resolver(self):
       
        return self.backtracking()


def mostrar_solucion(solucion):
    
    if solucion is None:
        print("No se encontró una solución.")
        return

    send = "".join(str(solucion[c]) for c in "SEND")
    more = "".join(str(solucion[c]) for c in "MORE")
    money = "".join(str(solucion[c]) for c in "MONEY")
    print("Asignación:", ", ".join(f"{letra}={solucion[letra]}" for letra in sorted(solucion)))
    print(f"  {send}\n+ {more}\n-----\n {money}")


if __name__ == "__main__":
    problema = CriptoaritmeticaCSP()
    mostrar_solucion(problema.resolver())
