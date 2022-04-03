from gpiozero import CPUTemperature
import time

while (1):
    with open('/var/www/html/index.nginx-debian.html', 'r') as file:
        data = file.readlines()
        file.close()

    string = str(CPUTemperature().temperature) + ' °C\n'
    data[26] = string

    with open('/var/www/html/index.nginx-debian.html','w') as file:
        file.writelines( data )
        file.close()

    with open('/var/www/html/cpu_temp.txt', 'w') as file:
        file.write(string)
        file.close()

    time.sleep(5)
