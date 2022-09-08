#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>
// #include <nlohmann/json.hpp>

struct Product
{
	unsigned	id;
	std::string	name;
	unsigned	price;
	tm			productDate;
};

void fillTm(std::string value, tm & data)
{
	std::stringstream ss(value);
	std::string item;
	std::getline(ss, item, '.');
	data.tm_mday = stoi(item);
	std::getline(ss, item, '.');
	data.tm_mon = stoi(item);
	std::getline(ss, item);
	data.tm_year = stoi(item);
}

void tokenize(std::string prod_inpt, std::vector<std::string> & tmp)
{
	std::string::iterator beginP;
	std::string::iterator endP;
	std::string	str;
	for (std::string::iterator iter = prod_inpt.begin(); iter < prod_inpt.end(); iter++)
	{
		str = "";
		while (((*iter) == 123 || (*iter) == 32 || (*iter) == 91 || (*iter) == 44 || (*iter) == 93) && iter < prod_inpt.end())
			iter++;
		beginP = iter;
		while ((*iter) != 125 && iter < prod_inpt.end())
			iter++;
		endP = iter;
		copy(beginP, endP, inserter(str, str.begin()));
		// std::cout << str << std::endl;
		if (str != "")
			tmp.push_back(str);
	}
}

void splitTokens(std::string tmp0, std::vector<std::string> & tmp1)
{
	std::string::iterator beginP;
	std::string::iterator endP;
	std::string	str;
	for (std::string::iterator iter = tmp0.begin(); iter < tmp0.end(); iter++)
	{
		str = "";
		while (((*iter) == 32 || (*iter) == 44) && iter < tmp0.end())
			iter++;
		beginP = iter;
		while ((*iter) != 44 && iter < tmp0.end())
			iter++;
		endP = iter;
		copy(beginP, endP, inserter(str, str.begin()));
		// std::cout << str << std::endl;
		tmp1.push_back(str);
	}
}

void splitPairs(std::string tokenStr, std::string & key, std::string & value)
{
	std::string::iterator beginP;
	std::string::iterator endP;
	std::string	str;
	for (std::string::iterator iter = tokenStr.begin(); iter < tokenStr.end(); iter++)
	{
		str = "";
		while (((*iter) == 32 || (*iter) == 34) && iter < tokenStr.end())
			iter++;
		beginP = iter;
		while ((*iter) != 34 && (*iter) != 58 && (*iter) != 44 && iter < tokenStr.end())
			iter++;
		endP = iter;
		copy(beginP, endP, inserter(str, str.begin()));
		// std::cout << str << std::endl;
		key = str;
		str = "";
		while (((*iter) == 32 || (*iter) == 34 || (*iter) == 58) && iter < tokenStr.end())
			iter++;
		beginP = iter;
		while ((*iter) != 34  && (*iter) != 44 && iter < tokenStr.end())
			iter++;
		endP = iter;
		copy(beginP, endP, inserter(str, str.begin()));
		// std::cout << str << std::endl;
		value = str;
	}
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
	std::vector<std::string> tmp, tmp1;
	std::string key, value;
	Product	product;
	
	tokenize(prod_inpt, tmp);

	// for (std::vector<std::string>::iterator iter = tmp.begin(); iter < tmp.end(); iter++)
	// 	std::cout << *iter << std::endl;

	for (std::vector<std::string>::iterator iter = tmp.begin(); iter < tmp.end(); iter++)
	{
		splitTokens(*iter, tmp1);
		// for (std::vector<std::string>::iterator iter = tmp1.begin(); iter < tmp1.end(); iter++)
		// 	std::cout << *iter << std::endl;
		for (std::vector<std::string>::iterator iter1 = tmp1.begin(); iter1 < tmp1.end(); iter1++)
		{
			splitPairs(*iter1, key, value);
			// std::cout << "key: " << key << " value: " << value << std::endl;
			if (key == "id")
				product.id = stoi(value);
			if (key == "name")
				product.name = value;
			if (key == "price")
				product.price = stoi(value);
			if (key == "date")
				fillTm(value, product.productDate);
		}
		products.push_back(product);
	}

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

void fillFilter(std::vector<std::string> filter_inpt, unsigned & PRICE_LESS_THAN, tm & DATE_AFTER, std::string & NAME_CONTAINS, unsigned & PRICE_GREATER_THAN, tm & DATE_BEFORE)
{
	for (std::vector<std::string>::iterator iter = filter_inpt.begin(); iter < filter_inpt.end(); iter++)
	{
		std::stringstream ss(*iter);
		std::string item;
		std::getline(ss, item, ' ');
		std::string value;
		std::getline(ss, value);
		if (item == "PRICE_LESS_THAN")
			PRICE_LESS_THAN = stoi(value);
		if (item == "DATE_AFTER")
			fillTm (value, DATE_AFTER);
		if (item == "NAME_CONTAINS")
			NAME_CONTAINS = value;
		if (item == "PRICE_GREATER_THAN")
			PRICE_GREATER_THAN = stoi(value);
		if (item == "DATE_BEFORE")
			fillTm (value, DATE_BEFORE);
	}
}

int main (int argc, char **argv)
{
	int n, k;
	std::vector<Product> products;
	unsigned	PRICE_LESS_THAN;
	tm			DATE_AFTER;
	std::string	NAME_CONTAINS;
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

	fillFilter(filter_inpt, PRICE_LESS_THAN, DATE_AFTER, NAME_CONTAINS, PRICE_GREATER_THAN, DATE_BEFORE);

	// std::cout << "PRICE_LESS_THAN: " << PRICE_LESS_THAN << std::endl;
	// std::cout << "DATE_AFTER: " << DATE_AFTER.tm_mday << "." << DATE_AFTER.tm_mon << "." << DATE_AFTER.tm_year << std::endl;
	// std::cout << "NAME_CONTAINS: " << NAME_CONTAINS << std::endl;
	// std::cout << "PRICE_GREATER_THAN: " << PRICE_GREATER_THAN << std::endl;
	// std::cout << "DATE_BEFORE: " << DATE_BEFORE.tm_mday << "." << DATE_BEFORE.tm_mon << "." << DATE_BEFORE.tm_year << std::endl;

	fillData(prod_inpt, products);

	// for (std::vector<Product>::iterator iter = products.begin(); iter < products.end(); iter++)
	// 	std::cout << "id: " << (*iter).id << ", name: " << (*iter).name << ", price: " << (*iter).price << ", date: " << (*iter).productDate.tm_mday << "." << (*iter).productDate.tm_mon << "." << (*iter).productDate.tm_year << std::endl;


	// for (std::vector<Disciplines>::iterator iter = disciplines.begin(); iter < disciplines.end(); iter++)
	// 	std::cout << (*iter).disciplineName << "  " << (*iter).maxQtyParticipants << std::endl;
	// for (std::vector<Participants>::iterator iter = participants.begin(); iter < participants.end(); iter++)
	// 	std::cout << (*iter).identifier << "  " << (*iter).disciplineName << "  " << (*iter).numberOfTicks << "  " << (*iter).penalty << std::endl;

	// for (iterD = disciplines.begin(); iterD < disciplines.end(); iterD++)
	// {
	// 	participants_tmp.clear();
	// 	for (iterP = participants.begin(); iterP < participants.end(); iterP++)
	// 	{
	// 		if ((*iterD).disciplineName == (*iterP).disciplineName)
	// 			participants_tmp.push_back(*iterP);
	// 	}
	// 	sort (participants_tmp.begin(), participants_tmp.end(), comp);
	// 	int j = 0;
	// 	std::vector<Participants>::iterator iter = participants_tmp.begin();
	// 	while (j < (*iterD).maxQtyParticipants)
	// 	{
	// 		j++;
	// 		outp.push_back(*iter);
	// 		iter++;
	// 	}
	// }

	// sort (outp.begin(), outp.end(), comp2);

	// // std::cout << "Output:" << std::endl;
	// for (std::vector<Participants>::iterator iter = outp.begin(); iter < outp.end(); iter++)
	// 	std::cout << (*iter).identifier << std::endl;

	return 0;
}

// c++ main.cpp && ./a.out
// OR
// c++ main.cpp && ./a.out < input.txt
// OR
// c++ main.cpp && ./a.out input.txt