import time

with open('/var/www/html/X_dela.html', 'r') as file:
    data = file.readlines()

print("Novy status pro X: ")
status=input()
status = status + '\n'
data[5] = status

with open('/var/www/html/X_dela.html','w') as file:
    file.writelines( data )
    file.close()

string = "%s: %s\n" % (time.ctime(),status)
with open('/home/pi/IoT/data/html_hist/X.txt','a') as file:
    file.write(string)
