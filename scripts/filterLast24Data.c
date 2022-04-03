

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// read timestamp from line
long get_stamp(char buf[20]) {
    char new_buf[20] = {'\0'};

    for (int i = 0; i < 20 && buf[i] != ' '; i++) {
        new_buf[i] = buf[i];
    }

    return atol(new_buf);
}

// read temperature from file
float get_temp(char buf[20]) {
    char new_buf[20] = {'\0'};
    char character;
    int pointer = 0;

    for (int i = 0; i < 20; i++) {
        character = buf[i];
        if (character == ' ') {
            for (int j = i+1; j < 20 && buf[j] != '\0'; j++) {
                new_buf[pointer] = buf[j];
                pointer++;
            }
            break;
        }
    }
    return atof(new_buf);
}

int main() {
    int pointer = 0;
    int counter = 0;
    int number_of_valid_values = 0;
    long day_ago, timestamp;
    float temp;
    float sum_of_values = 0;
    float last_day_float[86400]; // one field for every sec
    float shorter_list[72] = { 0 }; // every 10 mins
    char buf[20];
    char charakter;
    char *data_path = "/home/pi/IoT/data/temperatureData";
    char *new_data_path = "/home/pi/IoT/data/temperatureDataLast24";
    FILE *all_data;
    FILE *new_data;

    for (int i = 0; i < 86400; i++) {
      last_day_float[i] = -280;
    }

    all_data = fopen(data_path, "r");

    time_t t;
    time(&t);
    day_ago = t - 86400;

    while (!feof(all_data)) {
        charakter = fgetc(all_data);
        if (charakter == EOF) {
            break;
        } else if (charakter == '\n') {
            timestamp = get_stamp(buf);

            // process data
            if (timestamp > day_ago) {
                if (timestamp <= t) {
                    last_day_float[timestamp - day_ago] = get_temp(buf);
                }
            }

            pointer = 0;
            for (int i = 0 ; i < 20; i++) {
                buf[i] = '\0';
            }
        } else {
            buf[pointer] = charakter;
            pointer++;
        }
    }
    fclose(all_data);

    // create shorter array with average values
    for (int i = 0; i < 72; i++) {
        for (int j = 0; j < 1200; j++) {
            temp = last_day_float[j+i*1200];
            if (temp >= -275) {
                sum_of_values = sum_of_values + temp;
                number_of_valid_values++;
            }
        }
        if (number_of_valid_values >= 1) {
            shorter_list[i] = sum_of_values / number_of_valid_values;
            number_of_valid_values = 0;
            sum_of_values = 0;
        }
    }

    // save to new data file and generate time data
    new_data = fopen(new_data_path, "w");
    for (double i = -24; i <= 0; i=i+0.33334) {
        fprintf(new_data,"%.2f %.2f\n",i,shorter_list[counter]);
        counter++;
    }
    fclose(new_data);

    return 0;
}
