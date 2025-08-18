#include "predictor.h"


Saturated4BitCounter::Saturated4BitCounter(int thresholdValue) {
	if (thresholdValue < 0 || thresholdValue > 15) {
		// SHow error
	}

	threshold = thresholdValue;
	counter = thresholdValue;
}

bool Saturated4BitCounter::predict() {
	if (counter < 8) {
		return false;
	} else {
		return true;
	}
}

bool Saturated4BitCounter::increment() {
	if (counter < 15) {
		counter++;
		return true;
	}
	return false;
}

bool Saturated4BitCounter::decrement() {
	if (counter > 0) {
		counter--;
		return true;
	}
	return false;
}

Saturated4BitCounter &Saturated4BitCounter::operator++() {
	increment();
	return *this;
}

Saturated4BitCounter &Saturated4BitCounter::operator--() {
	decrement();
	return *this;
}

int Saturated4BitCounter::getCounter() {
	return counter;
}

int Saturated4BitCounter::getThreshold() {
	return threshold;
}