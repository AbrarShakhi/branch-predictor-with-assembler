#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <stdbool.h>

typedef struct Saturated4BitCounter {
  int counter;
} Saturated4BitCounter;

typedef struct CounterEntry {
  int key;
  Saturated4BitCounter *value;
} CounterEntry;

typedef struct Predictor {
  CounterEntry *counter_entry;
  int threshold;
} Predictor;

/**
 * Creates and initializes a new Predictor instance with a given threshold.
 *
 * The threshold value must be between 1 and 14 (inclusive) because it is
 * used for a saturated 4-bit counter. If the threshold is out of range,
 * the program prints an error message and exits.
 *
 * @param thresholdValue The threshold value for the saturated 4-bit counter (1
 * to 14).
 * @return A pointer to the newly allocated and initialized Predictor instance.
 * @throws Calls unable_to_allocate_memory_error if memory allocation fails.
 * @throws Terminates the program if `thresholdValue` is not within valid range.
 */
Predictor *predictor_create(int thresholdValue);

/**
 * Predicts the outcome of an instruction based on its saturated counter value.
 *
 * Looks up the counter entry for the given instruction in the Predictor's hash
 * map. Returns true if the counter exists and its value is greater than or
 * equal to the threshold. Returns false if no counter entry exists or the
 * counter value is below the threshold.
 *
 * @param predictor Pointer to the Predictor instance.
 * @param instr The instruction identifier to predict for.
 * @return true if the prediction threshold is met or exceeded, false otherwise.
 */
bool predictor_predict(Predictor *predictor, int instr);

/**
 * Updates the Predictor to learn a "taken" branch outcome for the given
 * instruction.
 *
 * If a counter entry for the instruction exists and its value is below the
 * maximum (15), the counter is incremented to strengthen the prediction for
 * "taken". Otherwise, a new saturated 4-bit counter is allocated and
 * initialized with a neutral counter value (8) indicating moderate confidence,
 * and inserted into the predictor.
 *
 * @param predictor Pointer to the Predictor instance.
 * @param instr The instruction identifier to update the prediction for.
 * @throws Calls unable_to_allocate_memory_error if memory allocation for the
 * counter fails.
 */
void predictor_learn_to_take(Predictor *predictor, int instr);

/**
 * Updates the Predictor to learn a "not taken" branch outcome for the given
 * instruction.
 *
 * If a counter entry for the instruction exists and its value is above 0,
 * the counter is decremented to weaken the prediction for "taken".
 * Otherwise, a new saturated 4-bit counter is allocated and initialized with a
 * neutral counter value (7) indicating moderate confidence against taking,
 * and inserted into the predictor.
 *
 * @param predictor Pointer to the Predictor instance.
 * @param instr The instruction identifier to update the prediction for.
 * @throws Calls unable_to_allocate_memory_error if memory allocation for the
 * counter fails.
 */
void predictor_learn_not_to_take(Predictor *predictor, int instr);

/**
 * Frees all memory associated with the given Predictor instance.
 *
 * This includes freeing each Saturated4BitCounter in the counter entry hashmap,
 * freeing the hashmap itself, and freeing the Predictor structure.
 * Does nothing if the predictor pointer is NULL.
 *
 * @param predictor Pointer to the Predictor instance to destroy.
 */
void predictor_destroy(Predictor *predictor);

#endif