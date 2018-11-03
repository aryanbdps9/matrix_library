import numpy as np
from timeit import default_timer as timer
print("import done")
a = np.arange(10**6).reshape((1000, 1000))
b = np.arange(10**6).reshape((1000, 1000))
start = timer()
c = np.matmul(a, b)
end = timer()
print("time elapsed: ", end-start);
