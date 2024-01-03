import random
def main(tests):
    for i in range(tests):
        n = random.randint(1, 10000)
        k = 0  # count of ones
        with open(f"in/input{i}.txt", "w") as f:
            f.write(f"{n}")

        while n != 0:
            if n % 2 != 0:
                k += 1
            n = n // 2

        with open(f"out/output{i}.txt", "w") as f:
            f.write(f"{k}")



if __name__ == "__main__":
    main(20)