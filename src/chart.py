import matplotlib.pyplot as plt; plt.rcdefaults()
from matplotlib.pyplot import figure
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import squarify

plt.rcParams['toolbar'] = 'None'
plt.rcParams["figure.figsize"] = (30,15)
plt.rcParams['font.size'] = 9
data = pd.read_csv("output_file.csv")

pew = {}
objects = []
frequency = []

with open("whitelist.txt") as p:
    for word in p.readlines():
        for x in range(data.index.stop):
            if data.loc[x].WORD == word.strip():
                pew.update({word.strip(): data.loc[x].FREQUENCY})

sortingitems = dict(sorted(pew.items(), key=lambda x: x[1]))
for sortitems in sortingitems.items():

    objects.append(sortitems[0])
    frequency.append(sortitems[1])





# y_pos = np.arange(len(objects))
# y = np.array(frequency)

# pie graph
# plt.pie(y, labels = objects)

# Horizantel Bar Graph
# plt.barh(y_pos, frequency, align='center', alpha=0.5)
# plt.yticks(y_pos, objects)
# plt.xlabel('Frequency')

squarify.plot(sizes=frequency, label=objects, alpha=.7 )
plt.axis('off')
plt.show()
