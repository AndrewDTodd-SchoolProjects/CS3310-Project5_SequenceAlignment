#ifndef SEQUENCE_DATA_H
#define SEQUENCE_DATA_H

#include <cstdint>
#include <filesystem>

struct SequenceData
{
	uint16_t _gapPenalty;
	uint16_t _mismatchPenalty;

	uint32_t _sequenceOneLength;
	char* _sequenceOne = nullptr;
	uint32_t _sequenceTwoLength;
	char* _sequenceTwo = nullptr;
};

SequenceData* SequenceDataFromFile(const std::filesystem::path& path);
#endif // !SEQUENCE_DATA_H
