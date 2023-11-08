#include <iostream>
#include <cstring>

#include "SequenceData.h"
#include "SequenceAlign.h"
#include "SequenceFromAlign.h"

int main(int argc, char* argv[])
{
	SequenceData* data = nullptr;
	AlignedSequenceResult* alignmentResult = nullptr;
	std::vector<std::pair<std::string, std::string>>* alignedSequences = nullptr;
	char* _filePath = nullptr;
	bool _filePathAllocated = false;
	bool debugInfo = false;
	uint32_t sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
	uint32_t sequenceTwoSubLength = std::numeric_limits<uint32_t>::max();
	
	if (argc < 2)
	{
		std::string filePath;
		std::cout << "Enter a path to a file containing the sequence info\n >>> ";
		getline(std::cin, filePath);

		_filePath = new char[filePath.size() + 1];
		std::strcpy(_filePath, filePath.c_str());
		_filePathAllocated = true;
	}
	else
	{
		std::string secondArg = argv[1];
		if (secondArg == "-d")
		{
			debugInfo = true;

			_filePath = argv[2];

			if (argc == 4)
			{
				std::string arg3 = argv[4];
				try
				{
					sequenceOneSubLength = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence one default length" << std::endl;
					sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc == 5)
			{
				std::string arg3 = argv[4];
				try
				{
					sequenceOneSubLength = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence one default length" << std::endl;
					sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
				}

				std::string arg4 = argv[5];
				try
				{
					sequenceTwoSubLength = static_cast<uint32_t>(std::stoi(arg4));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence two default length" << std::endl;
					sequenceTwoSubLength = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc > 5)
			{
				std::cout << "More argument entered than needed. Ignoring excess..." << std::endl;

				std::string arg3 = argv[4];
				try
				{
					sequenceOneSubLength = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence one default length" << std::endl;
					sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
				}

				std::string arg4 = argv[5];
				try
				{
					sequenceTwoSubLength = static_cast<uint32_t>(std::stoi(arg4));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence two default length" << std::endl;
					sequenceTwoSubLength = std::numeric_limits<uint32_t>::max();
				}
			}
		}
		else
		{
			_filePath = argv[1];

			if (argc == 3)
			{
				std::string arg2 = argv[3];
				try
				{
					sequenceOneSubLength = static_cast<uint32_t>(std::stoi(arg2));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence one default length" << std::endl;
					sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc == 4)
			{
				std::string arg2 = argv[3];
				try
				{
					sequenceOneSubLength = static_cast<uint32_t>(std::stoi(arg2));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence one default length" << std::endl;
					sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
				}

				std::string arg3 = argv[4];
				try
				{
					sequenceTwoSubLength = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence two default length" << std::endl;
					sequenceTwoSubLength = std::numeric_limits<uint32_t>::max();
				}
			}
			else if (argc > 4)
			{
				std::cout << "More argument entered than needed. Ignoring excess..." << std::endl;

				std::string arg2 = argv[3];
				try
				{
					sequenceOneSubLength = static_cast<uint32_t>(std::stoi(arg2));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence one default length" << std::endl;
					sequenceOneSubLength = std::numeric_limits<uint32_t>::max();
				}

				std::string arg3 = argv[4];
				try
				{
					sequenceTwoSubLength = static_cast<uint32_t>(std::stoi(arg3));
				}
				catch (const std::exception& ex)
				{
					std::cerr << "Non-Critical Error: " << ex.what() << " reverting to sequence two default length" << std::endl;
					sequenceTwoSubLength = std::numeric_limits<uint32_t>::max();
				}
			}
		}
	}

	std::chrono::milliseconds total = std::chrono::milliseconds();
	std::chrono::_V2::system_clock::time_point startTime;
	std::chrono::_V2::system_clock::time_point endTime;
	std::chrono::milliseconds duration;
	try
	{
		if (debugInfo)
		{
			startTime = std::chrono::high_resolution_clock::now();
		}
		data = SequenceDataFromFile(std::filesystem::path(_filePath));
		if (debugInfo)
		{
			endTime = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

			std::cout << "Sequence loading from file took ~" << duration.count() << " milliseconds" << std::endl;
			std::cout << "Sequences read in...\nSequence One Length: " << data->_sequenceOneLength << "\n" << data->_sequenceOne <<
						 "\nSequence Two Length: " << data->_sequenceTwoLength << "\n" << data->_sequenceTwo << std::endl;
		}
	}
	catch (const std::invalid_argument& argEx)
	{
		std::cerr << "Error: " << argEx.what() << std::endl;
		if(_filePathAllocated)
			delete[] _filePath;
		
		return 1;
	}
	catch (const std::runtime_error& rntEx)
	{
		std::cerr << "Error: " << rntEx.what() << std::endl;
		if (_filePathAllocated)
			delete[] _filePath;

		return 1;
	}

	if (debugInfo)
	{
		startTime = std::chrono::high_resolution_clock::now();
	}
	alignmentResult = CalculateOptimalAlignment(data, sequenceOneSubLength, sequenceTwoSubLength);
	if (debugInfo)
	{
		endTime = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

		std::cout << "Calculating optimal alignment path(s) ~" << duration.count() << " milliseconds" << std::endl;
	}

	std::cout << "Optimal alignment score: " << alignmentResult->_optimalScore << std::endl;

	alignedSequences = SequenceFromAlign(sequenceTwoSubLength - 1, sequenceOneSubLength - 1, alignmentResult, data);

	uint32_t pairNum = 1;
	for (auto& pair : *alignedSequences)
	{
		std::cout << "Aligned Sequences num " << pairNum << " produced from process -\n" <<
			pair.first << "\n" << pair.second << "\n" << std::endl;
	}

	if(_filePathAllocated)
		delete[] _filePath;

	delete[] data->_sequenceOne;
	delete[] data->_sequenceTwo;
	delete data;

	for (uint32_t row = 0; row < sequenceTwoSubLength; row++)
	{
		delete[] alignmentResult->_subproblemMatrix[row];
	}
	delete[] alignmentResult->_subproblemMatrix;
	delete alignmentResult;

	delete alignedSequences;

	return 0;
}
