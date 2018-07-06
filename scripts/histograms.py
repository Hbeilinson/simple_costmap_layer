import numpy as np
from matplotlib import pyplot as plt

def make_histogram(file_name):
    string_lst = []
    with open(file_name, "r") as filestream:
        for line in filestream:
            currentline = line.split(",")
            string_lst.append(currentline)

    number_lst = []
    #print(string_lst)
    for i in string_lst:
        for j in i:
            number_lst.append(int(j))

    plt.hist(number_lst)

make_histogram("compressed_costs.txt")
