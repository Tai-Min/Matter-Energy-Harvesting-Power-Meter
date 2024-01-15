#pragma once
#include <cmath>
#include <cstdint>
#include <numeric>

template <uint8_t bufSize> class RMS {
	float buf[bufSize] = { 0 };
	uint8_t bufCntr = 0;
	bool readyToPublish = false;

public:
	void addSample(float reading)
	{
		buf[bufCntr] = reading * reading;
		if (bufCntr >= bufSize) {
			readyToPublish = true;
			bufCntr = 0;
		}
	}

	float read()
	{
		float sum = std::accumulate(buf, buf + bufSize, 0) / static_cast<float>(bufSize);
		return sqrt(sum);
	}

	bool ready() { return readyToPublish; }

	void reset()
	{
		readyToPublish = false;
		bufCntr = 0;
	}
};