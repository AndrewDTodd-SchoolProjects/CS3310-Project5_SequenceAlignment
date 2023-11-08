#ifndef SEQUENCE_ALIGN_H
#define SEQUENCE_ALIGN_H

#include <cstdint>

#include "SequenceData.h"

struct AlignedSequenceResult
{
	uint32_t _optimalScore;
	uint32_t** _subproblemMatrix = nullptr;
};

AlignedSequenceResult* CalculateOptimalAlignment(SequenceData* sequenceData,
	uint32_t& sequenceOneSubarrayLength,
	uint32_t& sequenceTwoSubarrayLength);
#endif // !SEQUENCE_ALIGN_H
