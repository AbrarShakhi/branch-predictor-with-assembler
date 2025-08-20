#ifndef PREDICTOR_H
#define PREDICTOR_H

#include "bool.h"

typedef struct Saturated4BitCounter {
	int counter;
	int threshold;
} Predictor;

Predictor *predictor_create(int);
void predictor_distroy(Predictor *predictor);
bool predictor_predict(const Predictor *predictor);
void predictor_successful_prediction(Predictor *predictor);
void predictor_unsuccessful_prediction(Predictor *predictor);


#endif