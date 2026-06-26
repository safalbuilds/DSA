import matplotlib.pyplot as plt
import csv

def plott(filename):
    x = []
    y = []

    with open (filename) as file:
        reader = csv.reader(file)
        next(reader)
        for row in reader:
            x.append(int(row[0]))
            y.append(int(row[1]))
    
    plt.plot(x,y, label=filename.replace(".csv", ""))
    print(f"{filename} plotted successfully.")

def main():
    plott("bubble.csv")
    plott("insertion.csv")
    plott("selection.csv")

    plt.xlabel("No of elements")
    plt.ylabel("Time")
    plt.title("Comparision of Sorting algorithms")
    plt.grid(True)
    plt.legend()
    
    plt.show()  

if __name__ == "__main__":
    main()