import random
import sys
def ackermann(m, n):
    if m == 0:
        return n + 1
    elif n == 0:
        return ackermann(m - 1, 1)
    else:
        return ackermann(m - 1, ackermann(m, n - 1))

def tester(tests):
    c = 0
    for i in range(tests):
        m = i
        if i < 4:
            for _ in range(10):
                n = random.randint(0, 10**(tests - i - 1))
                
                with open(f"in/in{c}.txt", "w") as f:
                    f.write(f"{m}\n{n}")
                
                with open(f"out/out{c}.txt", "w") as f:
                    f.write(f"{ackermann(m, n)}")
                c += 1

        else: 
            n = random.randint(0, 4)
            with open(f"in/in{c}.txt", "w") as f:
                    f.write(f"{m}\n{n}")
                
            with open(f"out/out{c}.txt", "w") as f:
                    f.write(f"{ackermann(m, n)}")
            c += 1
            

def main():
    sys.setrecursionlimit(1000000000)
    tester(5)

if __name__ == "__main__":
    main()
