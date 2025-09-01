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
void predictor_learn_to_take(Predictor *, int);
void predictor_learn_not_to_take(Predictor *, int);

void predictor_destroy(Predictor *);

#endif