#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define REST_TIME 10

FILE *temp_stream;
FILE *temp_data;

char *temp_stream_file = "/home/pi/IoT/sensors/temperature";
char *database_adr = "/home/pi/IoT/data/temperatureData";

// sleep function
void rest(int time) {
    usleep(time*1000*1000);
}

// reset value in temperature stream file
void rst_tmp_stream() {
  temp_stream = fopen(temp_stream_file, "w");
  fprintf(temp_stream, "-280.00");
  fclose(temp_stream);
}

// get temperature
float get_tmp_stream() {
  float temp = -280;
  if ( access(temp_stream_file, F_OK) == 0 ) {
    temp_stream = fopen(temp_stream_file, "r");
    fscanf(temp_stream,"%f",&temp);
    fclose(temp_stream);
  }
  return temp;
}

// write temperature to log file
void write_data(float temp) {
  time_t t; // timestamp
  time(&t);
  if ( access(database_adr, F_OK) == 0 ) {
    temp_data = fopen(database_adr, "a");
    fprintf(temp_data,"\n%d %.2f",t,temp);
    fclose(temp_data);
  } else {
    temp_data = fopen(database_adr, "w");
    fprintf(temp_data,"%d %.2f",t,temp);
    fclose(temp_data);
  }
}

// create new graph
void update_graph() {
  system("/home/pi/IoT/scripts/fl24d");
  system("python3 /home/pi/IoT/scripts/IoTplotImage.py");
  system("rm /var/www/html/graph.png");
  system("mv /var/www/html/graph_temp.png /var/www/html/graph.png");
  system("rm /var/www/html/graph_temp.png");
}

int main() {
  int count = 0;
  float temp = -280;
  rst_tmp_stream();
  rest(REST_TIME);

  while (1) {
    temp = get_tmp_stream();
    rst_tmp_stream();
    if (temp != -280) {
      write_data(temp);
    }
    if (count%60 == 0) {
      update_graph();
      count = 0;
    }
    count++;

    rest(REST_TIME);
  }
  return 0;
}
