def lev(a, b):
    d=dict()
    for i in range(len(a)+1):
        d[i]=dict()
        d[i][0] = i
    for j in range(len(b)+1):
        d[0][j] = j
    for i in range(1, len(a)+1):
        for j in range(1, len(b)+1):
            d[i][j] = min(d[i-1][j]  + 1,       #borrado
                         d[i][j-1]   + 1,       #insercion
                         d[i-1][j-1] + (not a[i-1]==b[j-1]))   #sustitucion
    return d[len(a)][len(b)]

def dam_lev(a, b):
    d=dict()
    for i in range(len(a)+1):
        d[i]=dict()
        d[i][0] = i
    for j in range(len(b)+1):
        d[0][j] = j
    for i in range(1, len(a)+1):
        for j in range(1, len(b)+1):
            d[i][j] = min(d[i-1][j]  + 1,                             #borrado
                         d[i][j-1]   + 1,                             #insercion
                         d[i-1][j-1] + (not a[i-1]==b[j-1]))          #sustitucion
            if i>1 and j>1 and a[i-2] == b[j-1] and a[i-1] == b[j-2]: # condición restringida
                    d[i][j] = min(d[i][j], d[i-2][j-2] + 1)
    return d[len(a)][len(b)]

def intermedia(a, b):
    CTE = 3
    d=dict()
    for i in range(len(a)+1):
        d[i]=dict()
        d[i][0] = i
    for j in range(len(b)+1):
        d[0][j] = j
    for i in range(1, len(a)+1):
        for j in range(1, len(b)+1):
            d[i][j] = min(d[i-1][j]  + 1,                             #borrado
                         d[i][j-1]   + 1,                             #insercion
                         d[i-1][j-1] + (not a[i-1]==b[j-1]))          #sustitucion
            if i>1 and j>1 and a[i-2] == b[j-1] and a[i-1] == b[j-2]: # condición restringida
                    d[i][j] = min(d[i][j], d[i-2][j-2] + 1)
            if i>2 and j>1 and a[i-3] == b[j-1] and a[i-1] == b[j-2]: # condición intermedia
                    d[i][j] = min(d[i][j], d[i-3][j-2] + 2)
            if i>1 and j>2 and a[i-1] == b[j-3] and a[i-2] == b[j-1]: # condición intermedia
                    d[i][j] = min(d[i][j], d[i-2][j-3] + 2)
    return d[len(a)][len(b)]
print(intermedia("acb", "bda"))
