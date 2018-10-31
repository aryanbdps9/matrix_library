import numpy as np
from timeit import default_timer as timer

a = np.arange(10**8).reshape((1000, 100000))
b = np.arange(10**8).reshape((100000, 1000))
start = timer()
c = np.matmul(a, b)
end = timer()
print("time elapsed: ", end-start);