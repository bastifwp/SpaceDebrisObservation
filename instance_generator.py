import random

# Parámetros
num_n = 120
num_m = 5
filename = "huge_data.dat"

# Generar nombres de operaciones
N = [f"o{i}" for i in range(1, num_n + 1)]
M = [str(i) for i in range(1, num_m + 1)]

# Generar parámetros l, O y D
l_o_d = {}
for n in N:
    l = random.randint(1, 10)
    O = random.randint(0, 1000)
    D = O + random.randint(100, 1000)  # Asegurarse de que D >= O + 100
    l_o_d[n] = (l, O, D)

# Generar matriz giro
giro = {}
for ni in N:
    giro[ni] = {}
    for nj in N:
        giro[ni][nj] = 0 if ni == nj else random.randint(10, 100)

# Generar start_cost
start_cost = {n: random.randint(10, 100) for n in N}

# Escribir archivo
with open(filename, "w") as f:
    # Sets
    f.write("/* CONJUNTOS */\n\n")
    f.write(f"set N:= {' '.join(N)};\n\n")
    f.write(f"set M:= {' '.join(M)};\n\n")
    
    # Parámetros l, O, D
    f.write("param: l O D start_cost:=\n")
    for n in N:
        l, O, D = l_o_d[n]
        f.write(f"{n} {l} {O} {D} {start_cost[n]}\n")
    f.write(";\n\n")
    
    # Parámetro giro
    f.write("param giro\n:" + " ".join(N) + ":=\n")
    for ni in N:
        row = ni +  " " + " ".join(str(giro[ni][nj]) for nj in N)
        f.write(row + "\n")
    f.write(";\n\n")
    


print(f"Archivo '{filename}' generado con éxito.")