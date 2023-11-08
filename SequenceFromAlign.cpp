#include "SequenceFromAlign.h"

#include <sstream>
#include <algorithm>

bool checkEqual(const uint32_t& a, const uint32_t& b, const uint32_t& c)
{
	return (a == b) || (a == c) || (b == c);
}

std::vector<std::pair<std::string, std::string>>* SequenceFromAlign(const uint32_t& row, const uint32_t& column, 
	AlignedSequenceResult* alignmentInfo,
	SequenceData* sequenceData,
	std::vector<std::pair<std::string, std::string>>* optimalPairs)
{
	//Base case end
	if (row == 0 || column == 0)
	{
		optimalPairs->push_back(std::pair<std::string, std::string>());
		auto& pair = optimalPairs->back();
		for (int32_t i = 0; i < row; i++)
		{
			pair.first.push_back('_');
		}
		for (int32_t i = 0; i < column; i++)
		{
			pair.second.push_back('_');
		}
		for (int32_t i = 0; i <= row; i++)
		{
			pair.second.push_back(sequenceData->_sequenceTwo[i]);
		}
		for (int32_t i = 0; i <= column; i++)
		{
			pair.first.push_back(sequenceData->_sequenceOne[i]);
		}
		return nullptr;
	}

	//intial case, begin
	if (optimalPairs == nullptr)
	{
		optimalPairs = new std::vector<std::pair<std::string, std::string>>;
	}

	uint32_t northWest = alignmentInfo->_subproblemMatrix[row - 1][column - 1];
	uint32_t north = alignmentInfo->_subproblemMatrix[row][column - 1];
	uint32_t west = alignmentInfo->_subproblemMatrix[row - 1][column];

	uint32_t min = std::min({ northWest, north, west });
	/*if (checkEqual(northWest, north, west))
	{
		if (northWest == min)
		{
			std::pair<std::string, std::string>
			SequenceFromAlign(row - 1, column - 1, alignmentInfo, sequenceData, optimalPairs);
			for (auto& pair : *optimalPairs)
			{
				std::string& one = pair.first;
				std::string& two = pair.second;

				one.push_back(sequenceData->_sequenceOne[column]);
				two.push_back(sequenceData->_sequenceTwo[row]);
			}
		}
		if (north == min)
		{
			SequenceFromAlign(row - 1, column, alignmentInfo, sequenceData, optimalPairs);
			for (auto& pair : *optimalPairs)
			{
				std::string& one = pair.first;
				std::string& two = pair.second;

				one.push_back('_');
				two.push_back(sequenceData->_sequenceTwo[row]);
			}
		}
		if (west == min)
		{
			SequenceFromAlign(row, column - 1, alignmentInfo, sequenceData, optimalPairs);
			for (auto& pair : *optimalPairs)
			{
				std::string& one = pair.first;
				std::string& two = pair.second;

				one.push_back(sequenceData->_sequenceOne[column]);
				two.push_back('_');
			}
		}
	}
	else
	{
		if (northWest == min)
		{
			SequenceFromAlign(row - 1, column - 1, alignmentInfo, sequenceData, optimalPairs);
			for (auto& pair : *optimalPairs)
			{
				std::string& one = pair.first;
				std::string& two = pair.second;

				one.push_back(sequenceData->_sequenceOne[column]);
				two.push_back(sequenceData->_sequenceTwo[row]);
			}
		}
		else if (north == min)
		{
			SequenceFromAlign(row - 1, column, alignmentInfo, sequenceData, optimalPairs);
			for (auto& pair : *optimalPairs)
			{
				std::string& one = pair.first;
				std::string& two = pair.second;

				one.push_back('_');
				two.push_back(sequenceData->_sequenceTwo[row]);
			}
		}
		else
		{
			SequenceFromAlign(row, column - 1, alignmentInfo, sequenceData, optimalPairs);
			for (auto& pair : *optimalPairs)
			{
				std::string& one = pair.first;
				std::string& two = pair.second;

				one.push_back(sequenceData->_sequenceOne[column]);
				two.push_back('_');
			}
		}
	}*/
	if (northWest == min)
	{
		SequenceFromAlign(row - 1, column - 1, alignmentInfo, sequenceData, optimalPairs);
		for (auto& pair : *optimalPairs)
		{
			std::string& one = pair.first;
			std::string& two = pair.second;

			one.push_back(sequenceData->_sequenceOne[column]);
			two.push_back(sequenceData->_sequenceTwo[row]);
		}
	}
	else if (north == min)
	{
		SequenceFromAlign(row, column - 1, alignmentInfo, sequenceData, optimalPairs);
		for (auto& pair : *optimalPairs)
		{
			std::string& one = pair.first;
			std::string& two = pair.second;

			one.push_back(sequenceData->_sequenceOne[column]);
			two.push_back('_');
		}
	}
	else
	{
		SequenceFromAlign(row - 1, column, alignmentInfo, sequenceData, optimalPairs);
		for (auto& pair : *optimalPairs)
		{
			std::string& one = pair.first;
			std::string& two = pair.second;

			one.push_back('_');
			two.push_back(sequenceData->_sequenceTwo[row]);
		}
	}

	return optimalPairs;
}