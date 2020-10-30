def menorPrecio(L, l, p):
	N, inf, M = len(l), 2**31, {}
	for l in range(1, N+1):
		M[0, l] = inf
	for i in range(1, N+1):
		for l in range(0, l[i]):
			M[i, l] = M[i-1, l]