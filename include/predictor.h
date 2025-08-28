#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdbool.h>

typedef struct Saturated4BitCounter {
  int counter;
} Saturated4BitCounter;

typedef struct CounterEntry{
  int key;
  Saturated4BitCounter *value;
} CounterEntry;

typedef struct Predictor {
  CounterEntry *counter_entry;
  int threshold;
} Predictor;

Predictor *predictor_create(int);

bool predictor_predict(Predictor *, int);
void predictor_successful_prediction(Predictor *, int);
void predictor_unsuccessful_prediction(Predictor *, int);

void predictor_distroy(Predictor *);

#endif