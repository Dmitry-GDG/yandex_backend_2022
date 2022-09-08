#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Disciplines
{
	std::string	disciplineName;
	unsigned	maxQtyParticipants;
};

struct Participants
{
	std::string	identifier;
	std::string	disciplineName;
	unsigned	numberOfTicks;
	unsigned	penalty;
};

void tokenize(std::string const &str, const char delim,
            std::vector<std::string> &out)
{
    size_t start;
    size_t end = 0;
 
    while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = str.find(delim, start);
        out.push_back(str.substr(start, end - start));
    }
}

// Компаратор
bool comp(Participants a, Participants b)
{
	if (a.numberOfTicks == b.numberOfTicks)
		return a.penalty < b.penalty;
	else
		return a.numberOfTicks > b.numberOfTicks;
}

bool comp2(Participants a, Participants b)
{
	return a.identifier < b.identifier;
}

void fillData(std::vector<std::string> inpt_tmp, std::vector<Disciplines> & disciplines, std::vector<Participants> & participants, const char delim)
{
	std::vector<std::string> inpt;
	int n, k;
	std::string tmp;

	n = stoi(inpt_tmp[0]);
	std::vector<std::string>::iterator iter = inpt_tmp.begin() + 1;
	for (int i = 0; i < n; i++)
	{
		inpt.clear();
		tmp = (*iter);
		tokenize(tmp, delim, inpt);
		Disciplines disciplines_inpt;
		disciplines_inpt.disciplineName = inpt[0];
		disciplines_inpt.maxQtyParticipants = stoi(inpt[1]);
		disciplines.push_back(disciplines_inpt);
		iter++;
	}
	k = stoi(*iter);
	for (int i = 0; i < k; i++)
	{
		iter++;
		inpt.clear();
		tmp = (*iter);
		tokenize(tmp, delim, inpt);
		tokenize(tmp, delim, inpt);
		Participants participants_inpt;
		participants_inpt.identifier = inpt[0];
		participants_inpt.disciplineName = inpt[1];
		participants_inpt.numberOfTicks = stoi(inpt[2]);
		participants_inpt.penalty = stoi(inpt[3]);
		participants.push_back(participants_inpt);
	}
}

int main (int argc, char **argv)
{
	int n, k;
	std::vector<Disciplines> disciplines;
	std::vector<Participants> participants;
	std::string tmp;
	const char delim = ',';
	std::vector<std::string> inpt;
	std::vector<Participants> participants_tmp;
	std::vector<Participants> outp;
	std::vector<Disciplines>::iterator iterD;
	std::vector<Participants>::iterator iterP;

	if (argc == 1)
	{
		std::fstream fileToRead;
		fileToRead.open("input.txt");
		if (!fileToRead.is_open())
		{
			// std::cout << "number of disciplines = ";
			std::cin >> n;
			for (int i = 0; i < n; i++)
			{
				inpt.clear();
				// std::cout << "discipline " << i + 1 << "\t= ";
				std::cin >> tmp;
				tokenize(tmp, delim, inpt);
				Disciplines disciplines_inpt;
				disciplines_inpt.disciplineName = inpt[0];
				disciplines_inpt.maxQtyParticipants = stoi(inpt[1]);
				disciplines.push_back(disciplines_inpt);
			}

			// std::cout << "number of participants = ";
			std::cin >> k;
			for (int i = 0; i < k; i++)
			{
				inpt.clear();
				// std::cout << "participant " << i + 1 << "\t= ";
				std::cin >> tmp;
				tokenize(tmp, delim, inpt);
				Participants participants_inpt;
				participants_inpt.identifier = inpt[0];
				participants_inpt.disciplineName = inpt[1];
				participants_inpt.numberOfTicks = stoi(inpt[2]);
				participants_inpt.penalty = stoi(inpt[3]);
				participants.push_back(participants_inpt);
			}
		}
		else
		{
			std::string buf;
			std::vector<std::string> inpt_tmp;
			while (1)
			{
				std::getline(fileToRead, buf);
				inpt_tmp.push_back(buf);
				if (fileToRead.eof())
					break;
			}
			fileToRead.close();

			fillData(inpt_tmp, disciplines, participants, delim);
		}
	}
	else
	{
		std::string buf;
		std::vector<std::string> inpt_tmp;
		std::fstream fileToRead;
		fileToRead.open(argv[1]);
		while (1)
		{
			std::getline(fileToRead, buf);
			inpt_tmp.push_back(buf);
			if (fileToRead.eof())
				break;
		}
		fileToRead.close();

		fillData(inpt_tmp, disciplines, participants, delim);
	}

	// for (std::vector<Disciplines>::iterator iter = disciplines.begin(); iter < disciplines.end(); iter++)
	// 	std::cout << (*iter).disciplineName << "  " << (*iter).maxQtyParticipants << std::endl;
	// for (std::vector<Participants>::iterator iter = participants.begin(); iter < participants.end(); iter++)
	// 	std::cout << (*iter).identifier << "  " << (*iter).disciplineName << "  " << (*iter).numberOfTicks << "  " << (*iter).penalty << std::endl;

	for (iterD = disciplines.begin(); iterD < disciplines.end(); iterD++)
	{
		participants_tmp.clear();
		for (iterP = participants.begin(); iterP < participants.end(); iterP++)
		{
			if ((*iterD).disciplineName == (*iterP).disciplineName)
				participants_tmp.push_back(*iterP);
		}
		sort (participants_tmp.begin(), participants_tmp.end(), comp);
		int j = 0;
		std::vector<Participants>::iterator iter = participants_tmp.begin();
		while (j < (*iterD).maxQtyParticipants)
		{
			j++;
			outp.push_back(*iter);
			iter++;
		}
	}

	sort (outp.begin(), outp.end(), comp2);

	// std::cout << "Output:" << std::endl;
	for (std::vector<Participants>::iterator iter = outp.begin(); iter < outp.end(); iter++)
		std::cout << (*iter).identifier << std::endl;

	return 0;
}

// c++ main.cpp && ./a.out
// OR
// c++ main.cpp && ./a.out < input.txt
// OR
// c++ main.cpp && ./a.out input.txt