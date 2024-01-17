import random
def main(tests):
    
    # sYear, sMonth, sDay = map(int, input().split())
    # dYear, dMonth, dDay = map(int, input().split())
    for i in range(tests):
        sYear = random.randint(1000,9500)
        sMonth = random.randint(10, 12)
        sDay = random.randint(10, 30)
        dYear = sYear + random.randint(1, 300)
        dMonth = random.randint(10, 12)
        dDay = random.randint(10, 30)
        with open(f"in/input{i}.txt", "w") as f:
            f.write(f"{sYear} {sMonth} {sDay}\n")
            f.write(f"{dYear} {dMonth} {dDay}\n")
        
    
        days = (dYear - sYear) * 360 + (dMonth - sMonth) * 30 + dDay - sDay
        with open(f"out/output{i}.txt", "w") as f:
            f.write(f"{days}\n")
            

if __name__ == "__main__":
    main(20)
