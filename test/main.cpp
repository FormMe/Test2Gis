#include "TestProgram.h"

using namespace test;

int main(int argc, char* argv[])
{
	try
	{
		Parser argvParser;
		auto commandKey = argvParser.try_parse(argc, argv); //парсинг параметров командной строки
		switch (commandKey)									//в зависимости от результат парсинга выполняем соответвующую команду
		{
		case ResultCode::checksum:
		{
			TestProgram test;
			test.set_filename(argvParser.get_filename());
			uint32_t result = 0;
			if (test.checksum(result) == ResultCode::error)
				throw std::invalid_argument("Error: can`t open file");
			std::cout << "checksum: " << std::hex << result;
			break;
		}
		case ResultCode::words:
		{
			TestProgram test;
			test.set_filename(argvParser.get_filename());
			auto result = 0;
			auto word = argvParser.get_word();
			if (test.count(word, result) == ResultCode::error)
				throw std::invalid_argument("Error: can`t open file");
			std::cout << result << " words '" << word << "' in file";
			break;
		}
		case ResultCode::help:
			TestProgram::help();
			break;
		case ResultCode::error:
			throw std::invalid_argument("Error: unknown or not full command");
		default:
			throw std::logic_error("Error: unexpected result code");
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what();
	}
	return 0;
}

