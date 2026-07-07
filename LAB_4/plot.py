import matplotlib.pyplot as plt
import csv

def plott(filepath):
    x = []
    y = []
    func_name = filepath.replace("data/", "").replace(".csv", "").capitalize()
    with open (filepath) as file:
        reader = csv.reader(file)
        next(reader)
        for row in reader:
            x.append(int(row[0]))
            y.append(int(row[1]))
    
    plt.plot(x,y, label=func_name)
    print(f"{func_name} plotted successfully.")

def main():
    plott("data/bubble.csv")
    plott("data/insertion.csv")
    plott("data/selection.csv")

    plt.xlabel("No of elements")
    plt.ylabel("Time")
    plt.title("Comparision of Sorting algorithms")
    plt.grid(True)
    plt.legend()
    
    plt.show()  

if __name__ == "__main__":
    main()