import numpy as np

def lev(a, b, threshold=4):
    d = np.zeros([len(a)+1,len(b)+1])
    for i in range(len(a)+1):
        d[i,0] = i
    for j in range(len(b)+1):
        d[0,j] = j
    for i in range(1, len(a)+1):
        for j in range(1, min(i+threshold, len(b))+1): # condición de cercanía a diagonal
            d[i,j] = min(d[i-1,j]  + 1,       #borrado
                         d[i,j-1]   + 1,       #insercion
                         d[i-1,j-1] + (not a[i-1]==b[j-1])) # sustitucion
        if np.min(d[i,:]) > threshold: # condición del umbral
            return "None"
    return d[len(a),len(b)]

def dam_lev(a, b, threshold=4):
    d = np.zeros([len(a)+1,len(b)+1])
    for i in range(len(a)+1):
        d[i,0] = i
    for j in range(len(b)+1):
        d[0,j] = j
    for i in range(1, len(a)+1):
        for j in range(1, min(i+1+threshold, len(b))+1):# condición de cercanía a diagonal
            d[i,j] = min(d[i-1,j]  + 1,                             #borrado
                         d[i,j-1]   + 1,                             #insercion
                         d[i-1,j-1] + (not a[i-1]==b[j-1]))          #sustitucion
            if i>1 and j>1 and a[i-2] == b[j-1] and a[i-1] == b[j-2]: # condición restringida
                    d[i,j] = min(d[i,j], d[i-2,j-2] + 1)
        if np.min(d[i,:]) > threshold:# condición del umbral
            return "None"
    return d[len(a),len(b)]

def intermedia(a, b,threshold=4):
    CTE = 3
    d = np.zeros([len(a)+1,len(b)+1])
    for i in range(len(a)+1):
        d[i,0] = i
    for j in range(len(b)+1):
        d[0,j] = j
    for i in range(1, len(a)+1):
        for j in range(1, min(i+1+threshold, len(b))+1):# condición de cercanía a diagonal
            d[i,j] = min(d[i-1,j]  + 1,                             #borrado
                         d[i,j-1]   + 1,                             #insercion
                         d[i-1,j-1] + (not a[i-1]==b[j-1]))          #sustitucion
            if i>1 and j>1 and a[i-2] == b[j-1] and a[i-1] == b[j-2]: # condición restringida
                    d[i,j] = min(d[i,j], d[i-2,j-2] + 1)
            if i>2 and j>1 and a[i-3] == b[j-1] and a[i-1] == b[j-2]: # condición intermedia
                    d[i,j] = min(d[i,j], d[i-3,j-2] + 2)
            if i>1 and j>2 and a[i-1] == b[j-3] and a[i-2] == b[j-1]: # condición intermedia
                    d[i,j] = min(d[i,j], d[i-2,j-3] + 2)
        if np.min(d[i,:]) > threshold:# condición del umbral
            return "None"
    return d[len(a),len(b)]



test = [("algoritmo","algortimo"),
        ("algoritmo","algortximo"),
        ("algoritmo","lagortimo"),
        ("algoritmo","agaloritom"),
        ("algoritmo","algormio"),
        ("acb","ba")]

for x,y in test:
    print(f"{x:12} {y:12}",end="")
    for dist,name in ((lev,"levenshtein"),
                      (dam_lev,"restricted"),
                      (intermedia,"intermediate")):
        print(f" {name} {dist(x,y):2}",end="")
    print()
                 
"""
Salida del programa:

algoritmo    algortimo    levenshtein  2 restricted  1 intermediate  1
algoritmo    algortximo   levenshtein  3 restricted  3 intermediate  2
algoritmo    lagortimo    levenshtein  4 restricted  2 intermediate  2
algoritmo    agaloritom   levenshtein  5 restricted  4 intermediate  3
algoritmo    algormio     levenshtein  3 restricted  3 intermediate  2
acb          ba           levenshtein  3 restricted  3 intermediate  2
"""         