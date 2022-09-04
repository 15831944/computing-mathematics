import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os
import csv
from scipy import stats

fig = plt.figure()

def get_filename():
    path = './data'
    file_list = []
    for root, dirs, files in os.walk(path):
        return files

def plot_CPUtime(content):
    save_path = ""
    for t in content[0]:
        save_path += t + "_"
    save_path = "./fig/" + save_path + '.png'
    x = []
    t = []
    k = []
    for l in content[1:]:
        x.append(float(l[1]))
        t.append(float(l[0]))
    x = np.array(x)
    t = np.array(t)
    x = np.log2(x)
    t = -np.log2(t)
    for i in range(1, len(x)):
        k.append(abs((x[i] - x[i-1])/(t[i]-t[i-1])))
    res = stats.linregress(t, x)

    plt.clf()
    plt.plot(t, x,'r',label="$\\log_2(CPUtime)$")
    plt.plot(t, res.intercept + res.slope*t, '--', label='fitted line')
    plt.ylabel('$\\log_2(CPUtime)$')
    plt.xlabel('$-log_2(k)$')
    plt.legend()
    title = "grid refinement test (CPUtime) $k\\approx%.4f$"%abs(res.slope)
    plt.title(title)
    plt.savefig(save_path)

def plot_err(content):
    save_path = ""
    for t in content[0]:
        save_path += t + "_"
    save_path = "./fig/" + save_path + '.png'
    x = []
    t = []
    k = []
    for l in content[1:]:
        x.append(float(l[1]))
        t.append(float(l[0]))
    x = np.array(x)
    t = np.array(t)
    x = np.log2(x)
    t = -np.log2(t)
    res = stats.linregress(t, x)
    print(content[0][0], res.slope)
    for i in range(1, len(x)):
        k.append(abs((x[i] - x[i-1])/(t[i]-t[i-1])))
    plt.clf()
    plt.plot(t, x,'r',label="$\\log_2(||err||_\infty)$")
    plt.plot(t, res.intercept + res.slope*t, '--', label='fitted line')
    plt.ylabel('$\\log_2(||err||_\infty)$')
    plt.xlabel('$-log_2(k)$')
    plt.legend()
    title = "grid refinement test (error) $k\\approx%.4f$"%abs(res.slope)
    plt.title(title)
    plt.savefig(save_path)

def plot_2d(content):
    x = []
    y = []
    save_path = ""
    for t in content[0]:
        save_path += t + "_"
    save_path = "./fig/" + content[0][0]+"_"+content[0][len(content[0])-1] + '.png'
    title = content[0][1]
    if(int(content[0][2]) != 0):
        title += "(order = " + str(int(content[0][2])) + "), "
    else:
        title += ", "
    title += "T = " + content[0][4] + ", dt = " + content[0][5]
    for t in content[1]:
        x.append(float(t))
    for t in content[2]:
        y.append(float(t))
    plt.clf()
    plt.plot(x, y)
    plt.title(title)
    plt.savefig(save_path)

def plot(filename):
    path = './data/'+filename
    csv_reader = csv.reader(open(path))
    content = []
    for row in csv_reader:
        content.append(row)
    if(content[0][1] == "CPUtime"):
        plot_CPUtime(content)
        # return
    elif(content[0][1] == "error"):
        plot_err(content)
    else:
        plot_2d(content)
        # return

def plot_all():
    file_list = get_filename()
    for filename in file_list:
        # try:
        plot(filename)
        # except:
            # continue
    return 0

plot_all()
# csv_reader = csv.reader(open('./a.csv'))
# content = []
# for row in csv_reader:
#     content.append(row)
# print(len(content))