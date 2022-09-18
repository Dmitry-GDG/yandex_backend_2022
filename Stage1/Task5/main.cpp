#include <iostream>
#include <fstream>
#include <string>
#include <vector>

long checkPair(std::vector<std::pair<long, char> > inpt_pair)
{
	std::vector<std::pair<long, char> > outp_pair;

	for (std::vector<std::pair<long, char> >::iterator iter = inpt_pair.begin(); iter < inpt_pair.end(); iter++)
	{
		if ((*iter).second == 123)
			outp_pair.push_back(*iter);
		if ((*iter).second == 125)
		{
			if (outp_pair.empty())
				outp_pair.push_back(*iter);
			else if (!outp_pair.empty() && (*(outp_pair.end() - 1)).second == 123)
				outp_pair.pop_back();
			else
				return (-1);
		}
	}
	if (outp_pair.empty() || outp_pair.size() > 1)
		return (-1);
	return outp_pair[0].first;
}

int main (int argc, char **argv)
{
	std::string inpt;
	std::pair<long, char> tmp_pair;
	std::vector<std::pair<long, char> > inpt_pair;
	long i;

	std::ifstream fileToRead;
	fileToRead.open("input.txt");
	if (fileToRead.is_open())
	{
		std::getline(fileToRead, inpt);
		fileToRead.close();
	}
	else
		exit (1);
	// {
	// 	if (argc == 1)
	// 	{
	// 		// std::cout<<"input\t= ";
	// 		std::cin>>inpt;
	// 	}
	// 	else
	// 	{
	// 		std::ifstream fileToRead;
	// 		fileToRead.open(argv[1]);
	// 		if (!fileToRead.is_open())
	// 			exit (1);
	// 		std::getline(fileToRead, inpt);
	// 		fileToRead.close();
	// 	}
	// }

	for (std::string::iterator iter = inpt.begin(); iter < inpt.end(); iter++)
	{
		if (*iter != 32 && *iter != 42 && *iter != 43 && *iter != 45 && *iter != 47 && *iter != 61 && *iter != 125 && (*iter < 97 || *iter > 123))
			exit (1);
	}

	if (inpt.empty())
		exit (1);

	i = 1;
	for (std::string::iterator iter = inpt.begin(); iter < inpt.end(); iter++)
	{
		tmp_pair.first = i;
		tmp_pair.second = *iter;
		inpt_pair.push_back(tmp_pair);
		i++;
	}

	// for (std::vector<std::pair<int, char> >::iterator iter = inpt_pair.begin(); iter < inpt_pair.end(); iter++)
	// 	std::cout << (*iter).first << "\t" << (*iter).second << std::endl;

	std::cout << checkPair(inpt_pair) << "\n";
	return 0;
}

// c++ main.cpp && ./a.out
// OR
// c++ main.cpp && ./a.out < input.txt
// OR
// c++ main.cpp && ./a.out input.txt