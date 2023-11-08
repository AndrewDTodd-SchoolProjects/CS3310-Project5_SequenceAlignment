#ifndef SEQUENCE_FROM_ALIGN_H
#define SEQUENCE_FROM_ALIGN_H

#include <string>
#include <vector>
#include <cstdint>

#include "SequenceAlign.h"
#include "SequenceData.h"

std::vector<std::pair<std::string, std::string>>* SequenceFromAlign(const uint32_t& row, const uint32_t &column, 
	AlignedSequenceResult* alignmentInfo,
	SequenceData* sequenceData, 
	std::vector<std::pair<std::string, std::string>>* optimalPair = nullptr);
#endif // !SEQUENCE_FROM_ALIGN_H
