#include "TestProgram.h"

namespace test
{
	//ìåòîä çàäàåò èìÿ ôàéëà ñ êîòîðûì ðàáîòàåì
	void TestProgram::set_filename(const std::string& filename)
	{
		this->filename = filename;
	}

	/*ìåòîä ñ÷èòàåò ÷åêñóììó çàäàííîãî ðàíåå ôàéëà
	ïðèíèìàåò åäèíñòâåííûé ïàðàìåòð êóäà äîëæíî áûòü çàïèñàíî çíà÷åíèå ÷åêñóììû
	âîçâðàùàåò success â ñëó÷àå óñïåõà
	âîçâðàùàåò error â ñëó÷àå êîãäà ôàéë íå óäàëîñü îòêðûòü*/
	ResultCode TestProgram::checksum(uint32_t &checksum) const
	{
		std::ifstream fin;
		if (!try_open_file(false, fin))
			return ResultCode::error;
		checksum = 0;
		//ïîî÷åðåäíî ñ÷èòûâàåì 32áèòíûå ñëîâà, ñ÷èòàÿ ÷åêñóììó ïî çàäííîé ôîðìóëå
		while (!fin.eof())
		{
			std::uint32_t word32bit = 0;
			fin.read(reinterpret_cast<char*>(&word32bit), 4);
			checksum += word32bit;
		}
		fin.close();
		return ResultCode::success;
	}

	/*ìåòîä ïîäñ÷èòûâàåò êîëè÷åñâî âõîæäåíèé ñëîâà word â çàäàííîì ðàíåå ôàéëå
	âòîðûì ïàðàìåòðîì ïðèíèìàåò ïåðåìåííóþ êóäà äîëæíî áûòü çàïèñàíî êîëè÷åñòâî âõîæäåíèé
	âîçâðàùàåò success â ñëó÷àå óñïåõà
	âîçâðàùàåò error â ñëó÷àå êîãäà ôàéë íå óäàëîñü îòêðûòü*/
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
			/*ñ÷èòûâàåì ôàéë ïîñòðî÷íî ÷òîáû èçáåæàòü
			âîçìîæíîãî ïåðåïîëíåíèÿ â ñëó÷àå ñ÷èòûâàíèÿ ôàéëà öåëèêîì
			òàêîå ñ÷èòûâàíèå íèêàê íå ïîâëèÿåò íà ðåçóëüòàò*/
			getline(fin, line);
			for (auto foundedPos = 0; notFound; ++foundedPos)				//ïîèñê ñëåäóþùåãî âõîæäåíèå íà÷èíàåòñÿ ñ +1 ñèìâîëà
			{
				foundedPos = line.find(word, foundedPos);
				if ((notFound = foundedPos != std::string::npos)) ++cnt;	//åñëè ñëîâî íàéäåíî óâåëè÷èâàåì êîëè÷åñòâî
			}
		}
		
		fin.close();
		return ResultCode::success;
	}

	/*ñòàòè÷åñêèé ìåòîä ïå÷àòàåò èíôîðìàöèþ î ïðîãðàììå
	èñïîëüçîâàíèå ìîäèôèêàòîðà static îáóñëîâëåíî òåì,
	÷òî íåò íåîîáõîäèìîñòè ñîçäàâàòü ýêçåìëÿð êëàññà äëÿ ýòîé öåëè
	òàê êàê íåò ðàáîòû ñ ôàéëîì*/
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

	/*ìåòîä îñóùåñòâëÿåò ïîïûòêó îòêðûòü ðàíåå çàäàííûé ôàéë
	isTextMode = true åñëè åãî íåáõîäèìî îòêðûòü â òåêñòîâîì ðåæèìå
	isTextMode = false åñëè åãî íåáõîäèìî îòêðûòü â äâîè÷íîì ðåæèìå
	fin - ïîòîê êîòîðûé îñóùåñòâëÿåò îòêðûòèå ôàéëà
	âîçðàùàåò false â ñëó÷àå íåóäà÷è
	âîçðàùàåò true â ñëó÷àå óñïåõà*/
	bool TestProgram::try_open_file(bool isTextMode, std::ifstream& fin) const
	{
		fin.open(filename, isTextMode ? std::fstream::in : std::ios::binary);
		return !(!fin);
	}
}

