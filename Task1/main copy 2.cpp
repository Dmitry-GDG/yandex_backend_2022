#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main (int argc, char **argv)
{
	std::string inpt, attempt, outp;
	std::vector<int> safe(26);
	if (argc == 1)
	{
		std::fstream fileToRead;
		fileToRead.open("input.txt");
		if (!fileToRead.is_open())
		{
			// std::cout<<"input\t= ";
			std::cin>>inpt;
			// std::cout<<"attempt\t= ";
			std::cin>>attempt;
		}
		else
		{
			std::getline(fileToRead, inpt);
			std::getline(fileToRead, attempt);
			fileToRead.close();
		}
	}
	else
	{
		std::fstream fileToRead;
		fileToRead.open(argv[1]);
		std::getline(fileToRead, inpt);
		std::getline(fileToRead, attempt);
		fileToRead.close();
	}
	outp.resize(inpt.size(), 73);
	std::string::iterator iterI, iterA, iterO;
	for (iterI = inpt.begin(), iterA = attempt.begin(), iterO = outp.begin(); iterI < inpt.end(); iterI++, iterA++, iterO++)
	{
		if (*iterI == *iterA)
			*iterO = 80;
	}

	for (iterI = inpt.begin(), iterO = outp.begin(); iterI < inpt.end(); iterI++, iterO++)
	{
		if (*iterO != 80)
			safe[*iterI - 65]++;
	}

	// std::cout << "safe\t= ";
	// for (int i = 0; i < safe.size(); i++)
	// {
	// 	std::cout << safe[i];
	// 	if (i + 1 < safe.size())
	// 		std::cout << ", ";
	// }
	// std::cout << std::endl;

	for (iterI = inpt.begin(), iterA = attempt.begin(), iterO = outp.begin(); iterA < attempt.end(); iterI++, iterA++, iterO++)
	{
		if (*iterI != *iterA && safe[*iterA - 65] > 0)
		{
			safe[*iterA - 65]--;
			*iterO = 83;
		}
	}

	// std::cout << "safe\t= ";
	// for (int i = 0; i < safe.size(); i++)
	// {
	// 	std::cout << safe[i];
	// 	if (i + 1 < safe.size())
	// 		std::cout << ", ";
	// }
	// std::cout << std::endl;

	// std::cout << "output\t= ";
	std::cout << outp << std::endl;

	return 0;
}

// c++ main.cpp && ./a.out
// OR
// c++ main.cpp && ./a.out < input.txt
// OR
// c++ main.cpp && ./a.out input.txt