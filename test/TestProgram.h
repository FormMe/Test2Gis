#pragma once
#include <string>
#include <fstream>
#include <iostream>

#include "Parser.h"


namespace test
{
	/*класс отвечающий за работу режимов программы*/
	class TestProgram
	{
	public:
		void set_filename(const std::string &filename);

		ResultCode TestProgram::checksum(uint32_t &checksum) const;

		ResultCode TestProgram::count(const std::string &word, int &cnt) const;

		static void help();

	private:
		std::string filename;
		bool try_open_file(bool isTextMode, std::ifstream &fin) const;
	};
}
