#include "Parser.h"

namespace test
{
	/*����� ������������ ������ ����������*/
	ResultCode Parser::try_parse(int argc, char* argv[])
	{
		if (argc == 1) return ResultCode::help;									   //���� ��������� �� ������ ��������� - help

		key = argv[1];

		if (key == "-h") return ResultCode::help;								   //���� ������ ���� �� ������ ��������� 
		if (key != "-f") return ResultCode::error;								   //�������� �� -h ��� -f �� ������ �����������

		if (argc < 5 || strcmp(argv[3], "-m")) return ResultCode::error;		   //����� ������ ���� ������ ���������� "��� �����", "-m", "�������� �������"
																				   //�� ���� �� �����  4. ���� ��� �� ��� �� ������ �����������
		filename = argv[2];
		command = argv[4];

		if (command == "checksum")	return ResultCode::checksum;				   //���� ������ ���� �� ������ ������� 
		if (command != "words") return ResultCode::error;						   //�������� �� words ��� checksum �� ������ �����������

		if (argc != 7 || strcmp(argv[5], "-v"))  return ResultCode::error;		   //����� ��� ������� words ������ ���� ������ ���������� 
																				   //"-v", "����� ��� ������"
		word = argv[6];															   //�� ���� ����� ���������� ���������� ������ ���� ����� 6
		return ResultCode::words;												   //���� ��� �� ��� �� ������ �����������
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
