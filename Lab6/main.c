#include <stdio.h>
#include <stdlib.h>

#include "forecast.h"

Data* load_data(char* filename){
    // open file with data
    FILE* fp = fopen(filename, "r");

    if(fp == NULL){
        fprintf(stderr, "'%s' not found\n", filename);
        exit(EXIT_FAILURE);
    }

    Data* first = NULL;

    long int dt;
    float pressure;
    float temp;
    int humidity;
    float speed;
    float deg;

    // dt temp pressure humidity speed deg
    while(fscanf(fp, "%ld %f %f %d %f %f", 
                &dt, &temp, &pressure, &humidity, &speed, &deg) != EOF){
        // your code goes here
        first = insert_data(first, dt, temp, pressure, humidity, speed, deg);
    }

    fclose(fp);
    return first;
}

int main(){
   Data* first = load_data("kosice.csv");
   int choice;

   do{

       printf("Menu:\n\
  1 - Print data\n\
  2 - Get average temperature\n\
  3 - Get forecast\n\
\n\
  0 - Quit\n");

       scanf("%d", &choice);

       switch(choice){
           case 1:  printf("Print data\n");
           			print_forecast_data(first);
                    break;

           case 2:  printf("Get average temperature\n");
                    break;

           case 3:  printf("Get forecast\n");
                    break;
       }

   }while(choice != 0);

   first = delete_all(first);
}
