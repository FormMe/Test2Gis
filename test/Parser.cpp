#include "Parser.h"

namespace test
{
	/*метод осуществляет разбор параметров*/
	ResultCode Parser::try_parse(int argc, char* argv[])
	{
		if (argc == 1) return ResultCode::help;									   //если параметры не заданы результат - help

		key = argv[1];

		if (key == "-h") return ResultCode::help;								   //если заданы каке то другие параметры 
		if (key != "-f") return ResultCode::error;								   //отличные от -h или -f то данные некорректны

		if (argc < 5 || strcmp(argv[3], "-m")) return ResultCode::error;		   //далее должны быть заданы параментры "имя файла", "-m", "название команды"
																				   //то есть не менее  4. если это не так то данные некорректны
		filename = argv[2];
		command = argv[4];

		if (command == "checksum")	return ResultCode::checksum;				   //если заданы каке то другие команды 
		if (command != "words") return ResultCode::error;						   //отличные от words или checksum то данные некорректны

		if (argc != 7 || strcmp(argv[5], "-v"))  return ResultCode::error;		   //далее для команды words должны быть заданы параментры 
																				   //"-v", "слово для поиска"
		word = argv[6];															   //то есть общее количество параметров должно быть равно 6
		return ResultCode::words;												   //если это не так то данные некорректны
	}

	const std::string& Parser::get_filename()
	{
		return filename;
	}

	const std::string& Parser::get_command()
	{
		return command;
	}

	const std::string& Parser::get_word()
	{
		return word;
	}

	const std::string& Parser::get_key()
	{
		return key;
	}
}
