#include <stdio.h>
#include <stdbool.h>
#include "hof.h"

#define HOF_FILE "score"

int load(PLAYER list[]){
    // open the hall of fame file
    FILE *fp = fopen(HOF_FILE, "r");
    if(fp == NULL){
        return -1;
    }

    // read the content of hall of fame
    int idx = 0;
    while(fscanf(fp, "%29s %d", list[idx].name, &list[idx].score) != EOF && idx < 10){
        idx++;
    }

    fclose(fp);
    return idx;
}


bool save(const PLAYER list[], const int size){
    FILE *fp = fopen(HOF_FILE, "w");
    if(fp == NULL){
        return false;
    }

    // save the content of the list
    for(int idx = 0; idx < size && idx < 10; idx++){
        fprintf(fp, "%s %d\n", list[idx].name, list[idx].score);
    }

    fclose(fp);
    return true;
}
