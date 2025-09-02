#include "predictor.h"

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

#include "miscs.h"
#include "stb_ds.h"

Predictor *predictor_create(int thresholdValue) {
  if (thresholdValue <= 0 || thresholdValue >= 15) {
    fprintf(stderr, "For saturated 4-bit counter 'thresholdValue' has to be "
                    "between 1 and 14\n");
    shutdown(-1);
  }
  Predictor *predictor = (Predictor *)calloc(1, sizeof(Predictor));
  if (!predictor) {
    unable_to_allocate_memory_error("predictor");
  }
  predictor->threshold = thresholdValue;
  hmdefault(predictor->counter_entry, NULL);
  return predictor;
}

bool predictor_predict(Predictor *predictor, int instr) {
  CounterEntry *entry = hmgetp_null((predictor->counter_entry), instr);
  if (entry && entry->value) {
    return entry->value->counter >= predictor->threshold;
  }
  return false;
}

void predictor_learn_to_take(Predictor *predictor, int instr) {
  CounterEntry *entry = hmgetp_null((predictor->counter_entry), instr);
  if (entry && entry->value) {
    if (entry->value->counter < 15)
      entry->value->counter++;
  } else {
    Saturated4BitCounter *bitCounter = malloc(sizeof(Saturated4BitCounter));
    if (!bitCounter) {
      unable_to_allocate_memory_error("Saturated4BitCounter");
    }
    bitCounter->counter = 8;
    hmput(predictor->counter_entry, instr, bitCounter);
  }
}

void predictor_learn_not_to_take(Predictor *predictor, int instr) {
  CounterEntry *entry = hmgetp_null((predictor->counter_entry), instr);
  if (entry && entry->value) {
    if (entry->value->counter > 0)
      entry->value->counter--;
  } else {
    Saturated4BitCounter *bitCounter = malloc(sizeof(Saturated4BitCounter));
    if (!bitCounter) {
      unable_to_allocate_memory_error("Saturated4BitCounter");
    }
    bitCounter->counter = 7;
    hmput(predictor->counter_entry, instr, bitCounter);
  }
}

void predictor_destroy(Predictor *predictor) {
  if (predictor) {
    for (int i = 0; i < hmlen(predictor->counter_entry); ++i) {
      free_and_null(predictor->counter_entry[i].value);
    }
    hmfree(predictor->counter_entry);

    free_and_null(predictor);
  }
}
