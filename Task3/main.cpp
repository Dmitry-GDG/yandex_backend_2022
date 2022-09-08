#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>

struct Product
{
	unsigned	id;
	std::string	name;
	unsigned	price;
	tm			productDate;
};

void tokenize(std::string prod_inpt, std::vector<std::string> & tmp)
{
	
//     size_t start;
//     size_t end = 0;
 
//     while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
//     {
//         end = str.find(delim, start);
//         out.push_back(str.substr(start, end - start));
//     }
}

// // Компаратор
// bool comp(Participants a, Participants b)
// {
// 	if (a.numberOfTicks == b.numberOfTicks)
// 		return a.penalty < b.penalty;
// 	else
// 		return a.numberOfTicks > b.numberOfTicks;
// }

// bool comp2(Participants a, Participants b)
// {
// 	return a.identifier < b.identifier;
// }

void fillData(std::string prod_inpt, std::vector<Product> & products)
{
	std::vector<std::string> tmp;
	
	tokenize(prod_inpt, tmp);
	for (std::string::iterator iter = )

// 	std::vector<std::string> inpt;
// 	int n, k;
// 	std::string tmp;

// 	n = stoi(inpt_tmp[0]);
// 	std::vector<std::string>::iterator iter = inpt_tmp.begin() + 1;
// 	for (int i = 0; i < n; i++)
// 	{
// 		inpt.clear();
// 		tmp = (*iter);
// 		tokenize(tmp, delim, inpt);
// 		Disciplines disciplines_inpt;
// 		disciplines_inpt.disciplineName = inpt[0];
// 		disciplines_inpt.maxQtyParticipants = stoi(inpt[1]);
// 		disciplines.push_back(disciplines_inpt);
// 		iter++;
// 	}
// 	k = stoi(*iter);
// 	for (int i = 0; i < k; i++)
// 	{
// 		iter++;
// 		inpt.clear();
// 		tmp = (*iter);
// 		tokenize(tmp, delim, inpt);
// 		tokenize(tmp, delim, inpt);
// 		Participants participants_inpt;
// 		participants_inpt.identifier = inpt[0];
// 		participants_inpt.disciplineName = inpt[1];
// 		participants_inpt.numberOfTicks = stoi(inpt[2]);
// 		participants_inpt.penalty = stoi(inpt[3]);
// 		participants.push_back(participants_inpt);
// 	}
}

int main (int argc, char **argv)
{
	int n, k;
	std::vector<Product> products;
	unsigned	PRICE_LESS_THAN;
	tm			DATE_AFTER;
	std::string	pods;
	unsigned	PRICE_GREATER_THAN;
	tm			DATE_BEFORE;
	std::string	prod_inpt;
	std::vector<std::string> filter_inpt;
	std::string buf;

	std::fstream fileToRead;
	fileToRead.open("input.txt");
	if (fileToRead.is_open())
	{
		std::getline(fileToRead, prod_inpt);
		while (1)
		{
			std::getline(fileToRead, buf);
			filter_inpt.push_back(buf);
			if (fileToRead.eof())
				break;
		}
		fileToRead.close();
	}
	else
	{
		if (argc == 1)
		{
			std::cin >> prod_inpt;
			for (int i = 0; i < 5; i++)
			{
				std::cin >> buf;
				filter_inpt.push_back(buf);
			}
		}
		else
		{
			std::fstream fileToRead;
			fileToRead.open(argv[1]);
			if (!fileToRead.is_open())
				exit (1);
			while (1)
			{
				std::getline(fileToRead, buf);
				filter_inpt.push_back(buf);
				if (fileToRead.eof())
					break;
			}
			fileToRead.close();
		}
	}

	fillData(prod_inpt, products);

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