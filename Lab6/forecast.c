#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "forecast.h"

Data* insert_data(Data* first, long int dt, float temp, float pressure, int humidity, float speed, float deg) {
		Data *data = malloc(sizeof(Data));
		data->dt = dt;
		data->temp =temp;
		data->pressure = pressure;
		data->humidity = humidity;
		data->speed = speed;
		data->deg = deg;
		data->next = NULL;
		
		if(first == NULL) {
			return data;
		}
		
		Data *ptr = first;
		while(ptr->next != NULL) {
			ptr = ptr->next;
		}
		ptr->next = data;
		
		return first;
}


void print_forecast_data(Data* first) {
	char buffer[100];
	Data *ptr = first;
	while(ptr != NULL) {
		struct tm* dt = gmtime(&ptr->dt);
		strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M", dt);
		printf("%s %7.2fC %10.2fhPa %3d%% %8.2fm/s %3.0f\n", buffer, ptr->temp, ptr->pressure, ptr->humidity, ptr->speed, ptr->deg);
		ptr = ptr->next;
	}
}

Data* delete_all(Data* first) {
	Data *ptr = first;
	while(ptr != NULL) {
		Data *temp = ptr->next;
		free(ptr);
		ptr = temp;
	}
	
	return NULL;
}




