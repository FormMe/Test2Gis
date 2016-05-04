#pragma once
#include <string>

namespace test
{
	/*коды определяющие результат работы*/
	enum ResultCode
	{
		error = -1,
		help = 0,
		checksum = 1,
		words = 2,
		success = 3
	};

	/*класс осуществляет разбор параметров командной строки
	класс хранит полученные из параметров значения*/
	class Parser
	{
	public:
		ResultCode try_parse(int argc, char* argv[]);

		const std::string& get_filename();
		const std::string& get_command();
		const std::string& get_word();
		const std::string& get_key();

	private:
		std::string filename;	//имя файла для работы
		std::string command;	//комманда для выполнения
		std::string word;	//слово для поиска
		std::string key;	//первый ключ -h или -f
	};
}
