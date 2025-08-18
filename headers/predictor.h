#pragma once


class Predictor {
public:
	virtual bool predict() = 0;
};


class Saturated4BitCounter : Predictor {
private:
	int counter;
	int threshold;

public:
	Saturated4BitCounter(int);
	bool predict() override;
	bool increment();
	bool decrement();
	Saturated4BitCounter &operator++();
	Saturated4BitCounter &operator--();
	int getCounter();
	int getThreshold();
};
