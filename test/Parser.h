#pragma once
#include <string>

namespace test
{
	/*���� ������������ ��������� ������*/
	enum ResultCode
	{
		error = -1,
		help = 0,
		checksum = 1,
		words = 2,
		success = 3
	};

	/*����� ������������ ������ ���������� ��������� ������
	����� ������ ���������� �� ���������� ��������*/
	class Parser
	{
	public:
		ResultCode try_parse(int argc, char* argv[]);

		const std::string& get_filename();
		const std::string& get_command();
		const std::string& get_word();
		const std::string& get_key();

	private:
		std::string filename;	//��� ����� ��� ������
		std::string command;	//�������� ��� ����������
		std::string word;		//����� ��� ������
		std::string key;		//������ ���� -h ��� -f
	};
}
