import numpy as np
from matplotlib import pyplot as plt

def make_histogram(file_name):
    string_lst = []
    with open(file_name, "r") as filestream:
        for line in filestream:
            currentline = line.split(",")
            string_lst.append(currentline)

    number_lst = []
    print(string_lst[0])
    # del string_lst[-1]
    for i in range(len(string_lst[0]) -1):
        # for j in i:
        #print(i)
        # if ( != '100]\n'):
        number_lst.append(int(string_lst[0][i]))
        # else:
        #     number_lst.append(100)
    # number_lst.append(100)
    print(number_lst)

    bin_size = 1;
    #min_edge = min(number_lst); max_edge = max(number_lst)
    min_edge = 0; max_edge = 100
    N = (max_edge-min_edge)/bin_size; Nplus1 = N + 1
    bin_list = np.linspace(min_edge, max_edge, Nplus1)

    plt.hist(number_lst, bin_list)
    plt.show()

make_histogram("costmap_720.txt")
