#include "SequenceData.h"

#include <stdexcept>
#include <fstream>

SequenceData* SequenceDataFromFile(const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path))
		throw std::invalid_argument("Provided path doesnt exist \"" + path.string() + "\"");

	std::ifstream _stream(path);

	if (!_stream.is_open())
		throw std::runtime_error("Was unable to open file at \"" + path.string() + "\"");

	SequenceData* _data = new SequenceData;

	try
	{
		std::string line;
		if (!(_stream >> _data->_sequenceOneLength >> _data->_sequenceTwoLength >> _data->_gapPenalty >> _data->_mismatchPenalty))
			throw std::runtime_error("Error reading sequence information from file.\nEnsure the file is properly formatted with sequence lengths followed by penalty costs, followed by sequences");

		std::getline(_stream, line);

		_data->_sequenceOne = new char[_data->_sequenceOneLength + 1];
		_data->_sequenceTwo = new char[_data->_sequenceTwoLength + 1];

		if (!std::getline(_stream, line))
			throw std::runtime_error("Error reading sequence one from file. Ensure the sequence length recorded in file is correct, and sequence is correct");
		
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); // remove all whitespace
		
		if (line.length() != _data->_sequenceOneLength)
			throw std::runtime_error("Error reading sequence one from file. Ensure the sequence length recorded in file is correct, and sequence is correct");
		
		std::copy(line.begin(), line.end(), _data->_sequenceOne);
		_data->_sequenceOne[line.length()] = '\0'; // null terminate the string

		if (!std::getline(_stream, line))
			throw std::runtime_error("Error reading sequence two from file. Ensure the sequence length recorded in file is correct, and sequence is correct");
		
		line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end()); // remove all whitespace
		
		if (line.length() != _data->_sequenceTwoLength)
			throw std::runtime_error("Error reading sequence two from file. Ensure the sequence length recorded in file is correct, and sequence is correct");
		
		std::copy(line.begin(), line.end(), _data->_sequenceTwo);
		_data->_sequenceTwo[line.length()] = '\0'; // null terminate the string
	}
	catch (const std::exception& ex)
	{
		if(_data->_sequenceOne != nullptr)
			delete[] _data->_sequenceOne;

		if(_data->_sequenceTwo != nullptr)
			delete[] _data->_sequenceTwo;

		delete _data;
		throw ex;
	}

	return _data;
}