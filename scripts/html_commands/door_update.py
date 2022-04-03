import time
import sys

last_state = 0    # 0 = closed | 1 = open


while (1):
    try:
        file_distance = open('/home/pi/IoT/sensors/distance', 'r')
        value = file_distance.readlines()
        file_distance.close()
        if (float(value[0]) < 6.0):
            if (last_state == 1):

                status = time.ctime() + '\n'

                # write data to log file
                hist_log = open('/home/pi/IoT/data/html_hist/door_log.txt','a')
                hist_log.write(status)
                hist_log.close()


            last_state = 0
        else:                          # change of state
            if (last_state == 0):
                with open('/var/www/html/index.nginx-debian.html', 'r') as file:
                    data = file.readlines()

                status = time.ctime()
                data[23] = status + '\n'

                # write data to log file
                hist_log = open('/home/pi/IoT/data/html_hist/door_log.txt','a')
                hist_log.write(status + '  -  ')
                hist_log.close()

                with open('/var/www/html/index.nginx-debian.html','w') as file:
                    file.writelines( data )
                    file.close()

            last_state = 1

    except:
        print("door log ERROR")

    time.sleep(1)
