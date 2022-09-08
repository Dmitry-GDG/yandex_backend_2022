#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int checkPair(std::vector<std::pair<int, char> > inpt_pair)
{
	std::vector<std::pair<int, char> > outp_pair;

	for (std::vector<std::pair<int, char> >::iterator iter = inpt_pair.begin(); iter < inpt_pair.end(); iter++)
	{
		if ((*iter).second == 123)
			outp_pair.push_back(*iter);
		if ((*iter).second == 125)
		{
			if (outp_pair.empty())
				return (-1);
			outp_pair.pop_back();
		}
	}
	if (outp_pair.empty() || outp_pair.size() > 1)
		return (-1);
	return outp_pair[0].first;
}

int main ()
{
	std::string inpt;
	std::pair<int, char> tmp_pair;
	std::vector<std::pair<int, char> > inpt_pair;
	int i;

	std::fstream fileToRead;
	fileToRead.open("input.txt");
	if (fileToRead.is_open())
	{
		std::getline(fileToRead, inpt);
		fileToRead.close();
	}
	else
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

	std::cout << checkPair(inpt_pair) << std::endl;
	return 0;
}

// c++ main.cpp && ./a.out
// OR
// c++ main.cpp && ./a.out < input.txt
// OR
// c++ main.cpp && ./a.out input.txt