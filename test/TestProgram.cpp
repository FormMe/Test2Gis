#include "TestProgram.h"

namespace test
{
	//метод задает им€ файла с которым работаем
	void TestProgram::set_filename(const std::string& filename)
	{
		this->filename = filename;
	}

	/*метод считает чексумму заданного ранее файла
	принимает единственный параметр куда должно быть записано значение чексуммы
	возвращает success в случае успеха
	возвращает error в случае когда файл не удалось открыть*/
	ResultCode TestProgram::checksum(uint32_t &checksum) const
	{
		std::ifstream fin;
		if (!try_open_file(false, fin))
			return ResultCode::error;
		checksum = 0;
		//поочередно считываем 32битные слова, счита€ чексумму по заднной формуле
		while (!fin.eof())
		{
			std::uint32_t word32bit = 0;
			fin.read(reinterpret_cast<char*>(&word32bit), 4);
			checksum += word32bit;
		}
		fin.close();
		return ResultCode::success;
	}

	/*метод подсчитывает количесво вхождений слова word в заданном ранее файле
	вторым параметром принимает переменную куда должно быть записано количество вхождений
	возвращает success в случае успеха
	возвращает error в случае когда файл не удалось открыть*/
	ResultCode TestProgram::count(const std::string &word, int &cnt) const
	{
		std::ifstream fin;
		if (!try_open_file(false, fin))
			return ResultCode::error;
		std::string line;
		cnt = 0;
		while (!fin.eof())
		{
			auto notFound = true;
			/*считываем файл построчно чтобы избежать
			возможного переполнени€ в случае считывани€ файла целиком
			такое считывание никак не повли€ет на результат*/
			getline(fin, line);
			for (auto foundedPos = 0; notFound; ++foundedPos)				//поиск следующего вхождение начинаетс€ с +1 символа
			{
				foundedPos = line.find(word, foundedPos);
				if ((notFound = foundedPos != std::string::npos)) ++cnt;	//если слово найдено увеличиваем количество
			}
		}
		fin.close();
		return ResultCode::success;
	}

	/*статический метод печатает информацию о программе
	использование модификатора static обусловлено тем,
	что нет неообходимости создавать экземл€р класса дл€ этой цели
	так как нет работы с файлом*/
	void TestProgram::help()
	{
		std::cout << std::endl << std::endl
			<< "test - Test programm 2Gis. Created by Ovchinnikov Ilya Dmitrievich." << std::endl << std::endl <<

			"Usage" << std::endl << std::endl <<
			"\t test [-h | -f] " << std::endl <<
			"\t [filename] " << std::endl <<
			"\t [-m] [checksum | words] " << std::endl <<
			"\t [-v] [someword]" << std::endl << std::endl <<

			"Parameters" << std::endl << std::endl <<
			"\t -h" << "\t\t Help  " << std::endl <<
			"\t -f" << "\t\t Set file  " << std::endl <<
			"\t filename " << "\t name of the file" << std::endl <<
			"\t -m" << "\t\t Mode sets the command" << std::endl <<
			"\t checksum" << "\t Calulate 32bit checksum" << std::endl <<
			"\t words" << "\t\t Calulate the number of occurrences of the word" << std::endl <<
			"\t -v" << "\t\t Set word" << std::endl <<
			"\t someword" << "\t Word for search" << std::endl <<

			"Examples" << std::endl << std::endl <<
			"\t Print the count of word 'mother' in file 'Test.tst'" << std::endl <<
			"\t test -f Test.tst -m words -v mother" << std::endl << std::endl <<

			"\t Print 32bit checksum checksum = word1 + word2 + ... + wordN(word1...wordN - 32bit words if file)" << std::endl <<
			"\t test -f Test.tst -m checksum" << std::endl << std::endl <<

			"\t Print information about programm and description of parameters" << std::endl <<
			"\t test -h";
	}

	/*метод осуществл€ет попытку открыть ранее заданный файл
	isTextMode = true если его небходимо открыть в текстовом режиме
	isTextMode = false если его небходимо открыть в двоичном режиме
	fin - поток который осуществл€ет открытие файла
	возращает false в случае неудачи
	возращает true в случае успеха*/
	bool TestProgram::try_open_file(bool isTextMode, std::ifstream& fin) const
	{
		fin.open(filename, isTextMode ? std::fstream::in : std::ios::binary);
		return !(!fin);
	}
}

