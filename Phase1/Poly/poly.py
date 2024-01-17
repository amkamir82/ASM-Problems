import random
def mult(arr1, arr2):
        ans = [0 for i in range(len(arr1) + len(arr2) - 1)]
        for i in range(len(arr1)):
                for j in range(len(arr2)):
                        ans[i+j] += arr1[i]*arr2[j]
        return (ans)

def tester(tests):
        for j in range(tests):
                # generate n1 random numbers
                n1 = random.randint(0, 1000)
                arr1 = []
                for i in range(n1+1):
                        arr1.append(random.randint(-1000, 1000))
                n2 = random.randint(0, 1000)
                arr2 = []
                for i in range(n2+1):
                        arr2.append(random.randint(-1000, 1000))     
                # write testcase to file
                with open(f"in/in{j}.txt", "w") as f:
                        f.write(f"{n1}\n")
                        for i in arr1:
                                f.write(f"{i} ")
                        f.write("\n")
                        f.write(f"{n2}\n")
                        for i in arr2:
                                f.write(f"{i} ")
                        f.write("\n")
                arr1.reverse()
                arr2.reverse()   
                # write testcase answer to file       
                with open(f"out/out{j}.txt", "w") as f:
                        sum = n1+n2
                        for index, item in enumerate(reversed(mult(arr1, arr2))):
                                if item == 0:
                                        continue
                                power = index
                                if (sum - power) != 0:
                                        if item > 0:
                                                f.write(f"+{item}x^{sum - power}")
                                        else:
                                                f.write(f"{item}x^{sum - power}")
                                else:
                                        if item > 0:
                                                f.write(f"+{item}")
                                        else:
                                                f.write(f"{item}")    
                        f.write("\n")

def main():
        tester(30)


if __name__ == "__main__":
        main()


# def mult(arr1, arr2):
#         ans = [0 for i in range(len(arr1) + len(arr2) - 1)]
#         for i in range(len(arr1)):
#                 for j in range(len(arr2)):
#                         ans[i+j] += arr1[i]*arr2[j]
#         return (ans)

# def main():
#         n1 = int(input())
#         arr1 = list(reversed(list(map(int, input().split()))))
#         n2 = int(input())
#         arr2 = list(reversed(list(map(int, input().split()))))
#         sum = n1+n2
#         for index, item in enumerate( reversed(mult(arr1, arr2))):
#                 power = index
#                 if item > 0:
#                         print("+", item, f"x^{sum - power}", sep = "", end="")
#                 else:
#                         print("-",item, f"x^{sum - power}", sep = "", end="")


# if __name__ == "__main__":
#         main()