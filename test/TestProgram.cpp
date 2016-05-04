#include "TestProgram.h"

namespace test
{
	//����� ������ ��� ����� � ������� ��������
	void TestProgram::set_filename(const std::string& filename)
	{
		this->filename = filename;
	}

	/*����� ������� �������� ��������� ����� �����
	��������� ������������ �������� ���� ������ ���� �������� �������� ��������
	���������� success � ������ ������
	���������� error � ������ ����� ���� �� ������� �������*/
	ResultCode TestProgram::checksum(uint32_t &checksum) const
	{
		std::ifstream fin;
		if (!try_open_file(false, fin))
			return ResultCode::error;
		checksum = 0;
		//���������� ��������� 32������ �����, ������ �������� �� ������� �������
		while (!fin.eof())
		{
			std::uint32_t word32bit = 0;
			fin.read(reinterpret_cast<char*>(&word32bit), 4);
			checksum += word32bit;
		}
		fin.close();
		return ResultCode::success;
	}

	/*����� ������������ ��������� ��������� ����� word � �������� ����� �����
	������ ���������� ��������� ���������� ���� ������ ���� �������� ���������� ���������
	���������� success � ������ ������
	���������� error � ������ ����� ���� �� ������� �������*/
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
			/*��������� ���� ��������� ����� ��������
			���������� ������������ � ������ ���������� ����� �������
			����� ���������� ����� �� �������� �� ���������*/
			getline(fin, line);
			for (auto foundedPos = 0; notFound; ++foundedPos)				//����� ���������� ��������� ���������� � +1 �������
			{
				foundedPos = line.find(word, foundedPos);
				if ((notFound = foundedPos != std::string::npos)) ++cnt;	//���� ����� ������� ����������� ����������
			}
		}
		fin.close();
		return ResultCode::success;
	}

	/*����������� ����� �������� ���������� � ���������
	������������� ������������ static ����������� ���,
	��� ��� �������������� ��������� �������� ������ ��� ���� ����
	��� ��� ��� ������ � ������*/
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

	/*����� ������������ ������� ������� ����� �������� ����
	isTextMode = true ���� ��� ��������� ������� � ��������� ������
	isTextMode = false ���� ��� ��������� ������� � �������� ������
	fin - ����� ������� ������������ �������� �����
	��������� false � ������ �������
	��������� true � ������ ������*/
	bool TestProgram::try_open_file(bool isTextMode, std::ifstream& fin) const
	{
		fin.open(filename, isTextMode ? std::fstream::in : std::ios::binary);
		return !(!fin);
	}
}

