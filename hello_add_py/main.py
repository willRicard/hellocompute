import time

N = 1 << 20
x = [1.0] * N 
y = [2.0] * N

start = time.time()
for i, z in enumerate(zip(x, y)):
    xi, yi = z
    y[i] = xi + yi
end = time.time()

print(f"{1000.0 * (end - start)} ms")

err = 0.0
for yi in y:
    err = max(err, abs(yi - 3.0))

print(f"Max error: {err}")

