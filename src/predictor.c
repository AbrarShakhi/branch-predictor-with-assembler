#include "predictor.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "miscs.h"


Predictor *predictor_create(int thresholdValue) {
	if (thresholdValue <= 0 || thresholdValue >= 15) {
		fprintf(stderr,
		        "For saturated 4-bit counter 'thresholdValue' has to be "
		        "between 1 and 14\n");
		shutdown(-1);
	}
	Predictor *predictor = (Predictor *)malloc(sizeof(Predictor));
	if (!predictor) {
		unable_to_allocate_memory_error("assembler");
	}
	predictor->threshold = thresholdValue;
	predictor->counter = thresholdValue;
	return predictor;
}

void predictor_distroy(Predictor *predictor) {
	if (predictor) {
		free_and_null(predictor);
	}
}

bool predictor_predict(const Predictor *predictor) {
	return (predictor->counter >= predictor->threshold);
}

void predictor_successful_prediction(Predictor *predictor) {
	if (predictor->counter < 15) {
		(predictor->counter)++;
	}
}
void predictor_unsuccessful_prediction(Predictor *predictor) {
	if (predictor->counter > 0) {
		(predictor->counter)--;
	}
}
