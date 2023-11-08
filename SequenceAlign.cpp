#include "SequenceAlign.h"

#include <algorithm>

AlignedSequenceResult* CalculateOptimalAlignment(SequenceData* sequenceData,
	uint32_t& sequenceOneSubarrayLength,
	uint32_t& sequenceTwoSubarrayLength)
{
	if (sequenceOneSubarrayLength == std::numeric_limits<uint32_t>::max())
	{
		sequenceOneSubarrayLength = sequenceData->_sequenceOneLength;
	}

	if (sequenceTwoSubarrayLength == std::numeric_limits<uint32_t>::max())
	{
		sequenceTwoSubarrayLength = sequenceData->_sequenceTwoLength;
	}

	AlignedSequenceResult* result = new AlignedSequenceResult;

	result->_subproblemMatrix = new uint32_t * [sequenceTwoSubarrayLength];
	for (uint32_t row = 0; row < sequenceTwoSubarrayLength; row++)
	{
		result->_subproblemMatrix[row] = new uint32_t[sequenceOneSubarrayLength];
	}

	//base case for sequenceOne being empty
	for (uint32_t row = 0; row < sequenceTwoSubarrayLength; row++)
	{
		result->_subproblemMatrix[row][0] = row * sequenceData->_gapPenalty;
	}

	//Base case for sequenceTwo being empty
	for (uint32_t column = 0; column < sequenceOneSubarrayLength; column++)
	{
		result->_subproblemMatrix[0][column] = column * sequenceData->_gapPenalty;
	}

	//Tabulate all the subproblems. Fill the matrix
	for (uint32_t row = 1; row < sequenceTwoSubarrayLength; row++)
	{
		for (uint32_t column = 1; column < sequenceOneSubarrayLength; column++)
		{
			uint8_t intersectionPenalty = sequenceData->_sequenceTwo[row] == sequenceData->_sequenceOne[column] ? 0 : sequenceData->_mismatchPenalty;

			result->_subproblemMatrix[row][column] =
				std::min
				({
				  result->_subproblemMatrix[row - 1][column - 1] + intersectionPenalty,
				  result->_subproblemMatrix[row - 1][column] + sequenceData->_gapPenalty,
				  result->_subproblemMatrix[row][column - 1] + sequenceData->_gapPenalty
				});
		}
	}

	result->_optimalScore = result->_subproblemMatrix[sequenceTwoSubarrayLength - 1][sequenceOneSubarrayLength - 1];
	return result;
}