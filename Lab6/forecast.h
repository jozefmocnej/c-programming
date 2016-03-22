typedef struct data {
    long dt;
    float temp;
    float pressure;
    int humidity;
    float speed;
    float deg;

    struct data* next;
} Data;


Data* insert_data(Data* first, long int dt, float temp, float pressure, int humidity, float speed, float deg);
void print_forecast_data(Data* first);
Data* delete_all(Data* first);
