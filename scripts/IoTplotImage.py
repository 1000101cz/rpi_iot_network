# Create plot from Last24 file

import time
import matplotlib
import matplotlib.pyplot as plt
import matplotlib.ticker as plticker

color1 = 'salmon'
color2 = 'grey'
matplotlib.rcParams['text.color'] = color1
matplotlib.rcParams['axes.labelcolor'] = color1
matplotlib.rcParams['xtick.color'] = color2
matplotlib.rcParams['ytick.color'] = color2
matplotlib.rcParams['grid.color'] = color2
fig,axes=plt.subplots(nrows=1,ncols=1,figsize=(8,5))

x_values = []
y_values = []

f = open("/home/pi/IoT/data/temperatureDataLast24", "r")
for line in f:
    x_values.append(float(line.split()[0]))
    y_values.append(float(line.split()[1]))

f.close()

locx=plticker.MultipleLocator(base=3)
locy=plticker.MultipleLocator(base=1)
axes.xaxis.set_major_locator(locx)
axes.yaxis.set_major_locator(locy)

axes.set_xlim(-24,0)
axes.set_ylim(min(y_values)-2,max(y_values)+2)
fig.set_facecolor('xkcd:black')
axes.set_facecolor('xkcd:black')
plt.plot(x_values,y_values,color=color1)
plt.grid()
plt.title("Posledních 24 hodin od %s"%time.ctime())
plt.xlabel("čas   [ h ]")
plt.ylabel("teplota   [ °C ]")
plt.savefig("/var/www/html/graph_temp.png")
