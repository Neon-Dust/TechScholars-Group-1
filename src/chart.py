import matplotlib.pyplot as plt; plt.rcdefaults()
from matplotlib.pyplot import figure
import numpy as np
import matplotlib.pyplot as plt
from matplotlib import interactive
import pandas as pd
import squarify


plt.rcParams['toolbar'] = 'None'
plt.rcParams["figure.figsize"] = (30,15)
data = pd.read_csv("/home/ahmedalnoor/Ts/TechScholars-Group-1/src/output_file.csv")

dicts = {}
objects = []
objectBar = []
frequency = []

with open("/home/ahmedalnoor/Ts/TechScholars-Group-1/src/whitelist.txt") as p:
    for word in p.readlines():
        for x in range(data.index.stop):
            if data.loc[x].WORD == word.strip():
                dicts.update({word.strip(): data.loc[x].FREQUENCY})

sortingitems = dict(sorted(dicts.items(), key=lambda x: x[1]))
for sortitems in sortingitems.items():
    objects.append(sortitems[0]+ "\n" + str(sortitems[1]))
    objectBar.append(sortitems[0])
    frequency.append(sortitems[1])





y_pos = np.arange(len(objectBar))
y = np.array(frequency)


plt.figure(1)
plt.rcParams['font.size'] = 5
plt.pie(y, labels = objectBar, autopct='%1.1f%%')
interactive(True)
plt.show()

plt.figure(2)
plt.rcParams['font.size'] = 6
plt.barh(y_pos, frequency, align='center', alpha=0.5)
plt.yticks(y_pos, objects)
plt.xlabel('Frequency')
plt.show()

plt.figure(3)
plt.rcParams['font.size'] = 9
squarify.plot(sizes=frequency, label=objects, alpha=.7)
plt.axis('off')

interactive(False)
plt.show()
