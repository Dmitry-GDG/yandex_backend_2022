#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <sstream>

struct Product
{
	long	id;
	std::string	name;
	long	price;
	tm			productDate;
};

long	ft_atou(std::string str)
{
	long	i;
	long	outp;

	i = 0;
	outp = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32) || str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		outp = outp * 10 + str[i] - '0';
		i++;
	}
	return (outp);
}

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

std::string longToString99(long x)
{
    std::string s;
	if (x > 99)
	{
		while (x > 99)
			x %= 100;
	}
	s += x / 10 + '0';
	s += x % 10 + '0';
    return s;
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

// Компаратор
bool comp(Product a, Product b)
{
	return a.id < b.id;
}

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
				product.id = ft_atou(value);
			if (key == "name")
				product.name = value;
			if (key == "price")
				product.price = ft_atou(value);
			if (key == "date")
				fillTm(value, product.productDate);
		}
		products.push_back(product);
	}
}

bool isNameContains(std::string name, std::string NAME_CONTAINS)
{
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	std::transform(NAME_CONTAINS.begin(), NAME_CONTAINS.end(), NAME_CONTAINS.begin(), ::toupper);
	// std::cout << "name: " << name << std::endl;
	// std::cout << "NAME_CONTAINS: " << NAME_CONTAINS << std::endl;
	return (name.find(NAME_CONTAINS) != std::string::npos);
}

bool ifTimeValid(tm time, tm DATE_AFTER, tm DATE_BEFORE)
{
	int real, after, before;
	real = time.tm_year * 10000 + time.tm_mon * 100 + time.tm_mday;
	after = DATE_AFTER.tm_year * 10000 + DATE_AFTER.tm_mon * 100 + DATE_AFTER.tm_mday;
	before = DATE_BEFORE.tm_year * 10000 + DATE_BEFORE.tm_mon * 100 + DATE_BEFORE.tm_mday;
	return (real >= after && real <= before);
}

void fillFilter(std::vector<std::string> filter_inpt, long & PRICE_LESS_THAN, tm & DATE_AFTER, std::string & NAME_CONTAINS, long & PRICE_GREATER_THAN, tm & DATE_BEFORE)
{
	for (std::vector<std::string>::iterator iter = filter_inpt.begin(); iter < filter_inpt.end(); iter++)
	{
		std::stringstream ss(*iter);
		std::string item;
		std::getline(ss, item, ' ');
		std::string value;
		std::getline(ss, value);
		if (item == "PRICE_LESS_THAN")
			PRICE_LESS_THAN = ft_atou(value);
		if (item == "DATE_AFTER")
			fillTm (value, DATE_AFTER);
		if (item == "NAME_CONTAINS")
			NAME_CONTAINS = value;
		if (item == "PRICE_GREATER_THAN")
			PRICE_GREATER_THAN = ft_atou(value);
		if (item == "DATE_BEFORE")
			fillTm (value, DATE_BEFORE);
	}
}

int main (int argc, char **argv)
{
	std::vector<Product> products, outp;
	long	PRICE_LESS_THAN;
	tm			DATE_AFTER;
	std::string	NAME_CONTAINS;
	long	PRICE_GREATER_THAN;
	tm			DATE_BEFORE;
	std::string	prod_inpt, buf, outp_json;
	std::vector<std::string> filter_inpt;

	std::ifstream fileToRead;
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
			std::ifstream fileToRead;
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

	for (std::vector<Product>::iterator iter = products.begin(); iter < products.end(); iter++)
	{
		if (isNameContains((*iter).name, NAME_CONTAINS) && ifTimeValid((*iter).productDate, DATE_AFTER, DATE_BEFORE) && (*iter).price <= PRICE_LESS_THAN && (*iter).price >= PRICE_GREATER_THAN)
			outp.push_back(*iter);
	}

	// std::cout << std::endl;
	// for (std::vector<Product>::iterator iter = outp.begin(); iter < outp.end(); iter++)
	// 	std::cout << "id: " << (*iter).id << ", name: " << (*iter).name << ", price: " << (*iter).price << ", date: " << (*iter).productDate.tm_mday << "." << (*iter).productDate.tm_mon << "." << (*iter).productDate.tm_year << std::endl;

	sort (outp.begin(), outp.end(), comp);

	// for (std::vector<Product>::iterator iter = outp.begin(); iter < outp.end(); iter++)
	// 	std::cout << "id: " << (*iter).id << ", name: " << (*iter).name << ", price: " << (*iter).price << ", date: " << (*iter).productDate.tm_mday << "." << (*iter).productDate.tm_mon << "." << (*iter).productDate.tm_year << std::endl;

	// makeJson(outp, outp_json);

	// std::cout << outp_json << std::endl;

	std::cout <<  "[";
	for (std::vector<Product>::iterator iter = outp.begin(); iter < outp.end(); iter++)
	{
		std::cout <<  "{\"id\": " << int((*iter).id) << ", \"name\": \"" << (*iter).name << "\", \"price\": " << (*iter).price << ", \"date\": \"" << longToString99((*iter).productDate.tm_mday) << "." << longToString99((*iter).productDate.tm_mon) << "." << (*iter).productDate.tm_year << "\"}";
		if (iter + 1 != outp.end())
			std::cout << ", ";
	}
	std::cout << "]\n";

	return 0;
}

// c++ main.cpp && ./a.out
// OR
// c++ main.cpp && ./a.out < input.txt
// OR
// c++ main.cpp && ./a.out input.txt