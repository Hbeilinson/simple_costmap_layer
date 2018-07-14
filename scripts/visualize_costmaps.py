from PIL import Image
from matplotlib import *

def rgb(minimum, maximum, value):
    minimum, maximum = float(minimum), float(maximum)
    ratio = 2 * (value-minimum) / (maximum - minimum)
    b = int(max(0, 255*(1 - ratio)))
    r = int(max(0, 255*(ratio - 1)))
    g = 255 - b - r
    return r, g, b

def visualize_a_costmap(file_name):
    string_lst = []
    with open(file_name, "r") as filestream:
        for line in filestream:
            currentline = line.split(",")
            string_lst.append(currentline)

    number_lst = []
    # print(string_lst)
    # del string_lst[-1]
    for i in range(len(string_lst) -1):
        # for j in i:
        #print(i)
        # if ( != '100]\n'):
        number_lst.append(int(string_lst[i]))
        # else:
        #     number_lst.append(100)
    number_lst.append(100)
    print (len(string_lst))
    # print (len(string_lst[0]))

    # for i in range(200):
    #     for j in range(200):
            #do stuff with cm plotting


    img = Image.new("RGBA", (200, 200));
    pixels = img.load()
    for i in range(200):
        for j in range(200):
            # print 1.0/number_lst[i*100 + j]
            # print colors.is_color_like(str(1.0/number_lst[i*100 + j]))
            rgb = colors.colorConverter.to_rgb(str(1.0/number_lst[i*100 + j]))
            r = int(rgb[0] * 255)
            g = int(rgb[1] * 255)
            b = int(rgb[2] * 255)
            # print [r, g, b]
            pixels[i,j] = (r, g, b) #1/number_lst[i*100 + j]
    img.save(file_name[:-4] + "_image.jpg")
    print("here")

visualize_a_costmap("willow_compressed_costs.txt")
