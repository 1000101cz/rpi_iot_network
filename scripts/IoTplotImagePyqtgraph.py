# Create plot from Last24 file

import time
import pyqtgraph as pg
import pyqtgraph.exporters

x_values = []
y_values = []

f = open("/home/pi/IoT/data/temperatureDataLast24", "r")
for line in f:
    x_values.append(float(line.split()[0]))
    y_values.append(float(line.split()[1]))

f.close()


plt = pg.plot(x_values, y_values, pen=pg.mkPen('red', width=3))

plt.setYRange(min(y_values) - 1.5, max(y_values) + 1.5)
plt.setXRange(-24,0)

exporter = pg.exporters.ImageExporter(plt.plotItem)
exporter.parameters()['width'] = 800
exporter.parameters()['height'] = 500

# save to file
exporter.export('fileName.png')



a=input()
