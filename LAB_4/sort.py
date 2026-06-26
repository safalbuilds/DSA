import random
import time
import matplotlib.pyplot as plt
import numpy as np

def bubble(x):
    for i in range(len(x)-1):
        for j in range(len(x)-i-1):
            if x[j] > x[j+1]:
                x[j], x[j+1] = x[j+1], x[j]
    return x

def insertion(x):
    for i in range(1, len(x)):
        key = x[i]
        j = i - 1

        while j >= 0 and x[j] > key:
            x[j + 1] = x[j]
            j -= 1

        x[j + 1] = key

    return x

def selection(x):
    n = len(x)

    for i in range(n - 1):
        min_index = i

        for j in range(i + 1, n):
            if x[j] < x[min_index]:
                min_index = j

        x[i], x[min_index] = x[min_index], x[i]

    return x

def graph(func):
    numbers, times = [], []
    for n in range(0, 10000, 100):
        arr = [random.randint(1, 1000) for _ in range(n)]
        start = time.time()
        func(arr)
        end = time.time()
        numbers.append(n)
        times.append(end-start)
    plt.plot(numbers, times)


    numbers = np.array(numbers)
    times = np.array(times)

    plt.plot(numbers, times, label=func.__name__)
    
def plot_all():
    time1 = time.time()
    graph(bubble)
    time2 = time.time()
    print(f"time for bubble : {time2-time1:.9}")

    time1 = time.time()
    graph(insertion)
    time2 = time.time()
    print(f"time for insertion : {time2-time1:.9}")

    time1 = time.time()
    graph(selection)
    time2 = time.time()
    print(f"time for selection : {time2-time1:.9}")

    plt.xlabel("No of elements")
    plt.ylabel("Time")
    plt.title("Comparision of Sorting algorithms")
    plt.grid(True)
    plt.legend()
    plt.show()

def main():
    arr = [random.randint(0, 100000) for _ in range(30)]
    print(arr)
    time1 = time.time()
    sorted = insertion(arr)
    time2 = time.time()
    print(sorted)
    print(f"time : {(time2-time1)*1e6:.5}ns")

if __name__ == "__main__":
    main()