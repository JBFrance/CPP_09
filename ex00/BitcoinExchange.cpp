#include "BitcoinExchange.hpp"
#include <vector>

void Btc::throwError(Errors cause, std::string str)
{
	switch (cause)
	{
		case NEGVAL:
			str = "Not a positive number => " + str;
			break ;
		case HUGEVAL: 
			str = "Value too big =>" + str;
			break ;
		case INVVAL:
			str = "Invalid value => " + str;
			break ;
		case FORMAT:
			str = "Invalid date format => " + str;
			break ;
		case MD:
			str = "Bad month or day => " + str;
			break ;
		case YEAR:
			str = "Invalid year => " + str;
			break ;
		case MONTH:
			str = "Invalid month => " + str;
			break ;
		case DAY:
			str = "Invalid day => " + str;
			break ;
		case INVLINE:
			str = "Invalid line => " + str;
			break ;
		case RATE:
			str = "Invalid Rate => " + str;
			break ;
	}
	throw std::invalid_argument(str);
}

void Btc::parseValue()
{
	if (value[value.size() - 1] == 'f')
		value.pop_back();
	std::istringstream conv(value);
	if (conv >> val)
	{
		if (val >= 0 && val <= 1000)
			return ;
		else if (val < 0)
			throwError(NEGVAL, value);
		else if (val > 1000)
			throwError(HUGEVAL, value);
	}
	throwError(INVVAL, value);
}

void Btc::splitData()
{
	size_t dashPos = 0;
	size_t dashOld = 0;
	size_t count = 0;

	if (date.find('-') == std::string::npos)
		throwError(FORMAT, date);
	while (true)
	{
		dashOld = dashPos;
		dashPos = date.find('-', dashPos + (dashPos != 0));
		switch (count)
		{
			case 0:
			year = date.substr(0, dashPos);
			break;
			case 1:
			month = date.substr(dashOld + 1, dashPos - (dashOld + 1));
			break;
			case 2:
			day = date.substr(dashOld + 1, date.size() - 1 - (dashOld + (date[date.size() - 1] == ' ')));
		}
		if (count == 2)
			break ;
		count++;
	}
	if (count != 2 || day.find('-') != std::string::npos)
		throwError(FORMAT, date); 
}

void Btc::checkMonthDay()
{
	int months[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (monthNum == 2)
	{
		if (dayNum <= months[monthNum - 1] + ((!(yearNum % 4) && (yearNum % 100)) || (!(yearNum%400))))
			return ;
	} 
	else if (dayNum <= months[monthNum - 1])
		return ;
	throwError(MD, date);
}

void Btc::parseDate()
{
	splitData();
	std::istringstream convY(year);
	std::istringstream convM(month);
	std::istringstream convD(day);

	if (year.size() != 4 || !(convY >> yearNum))
	{
		throwError(YEAR, year);
	}
	if (month.size() != 2 || !(convM >> monthNum))
	{
		throwError(MONTH, month);
	}
	if (day.size() != 2 || !(convD >> dayNum))
	{
		throwError(DAY, day);
	}
	checkMonthDay();
}

void Btc::checkline()
{
	pipePos = line.find('|');
	if (pipePos != std::string::npos)
	{
		date = line.substr(0, (pipePos - 1));
		value = line.substr(pipePos + 1, line.size() - pipePos);
		parseDate();
		parseValue();
		return ;
	}
	throwError(INVLINE, line);
}

void Btc::parse(const std::string &filename)
{
	std::ifstream inp;
	bool firstLine = true;

	inp.open(filename);
	if (inp.is_open())
	{
		while (getline(inp, line))
		{
			if (firstLine && line != "date | value")
			{
				std::cout << "Invalid Input File" << std::endl;
				return ;
			} 
			else if (firstLine)
			{
				firstLine = false;
				continue ;
			}
			try
			{
				checkline();
				displayBtc();
			} 
			catch (const std::invalid_argument &e)
			{
				std::cout << e.what() << std::endl;
				continue ;
			}
		}
		return ;
	}
	std::cout << "File Does Not Exist" << std::endl;
}

void Btc::getRate()
{
	std::istringstream conv(line.substr(line.find(',') + 1, line.size() - (line.find(',') + 1)));
	
	conv >> rate;
}

void Btc::storeData()
{
	std::ifstream db;
	std::vector<int> test;

	db.open("data.csv");
	if (!db.is_open())
		throw (std::invalid_argument("Could not open data file"));
	getline(db,line);
	while (getline(db, line))
	{
		getRate();
		data[line.substr(0, line.find(","))] = rate;
	}
}

void Btc::displayBtc()
{
	storeData();
	
	std::map<std::string, float>::iterator it = data.begin();
	if (data.find(date) != data.end()){
		std::cout << date << " => " << val << " = " << val * data[date] << std::endl;
	} 
	else 
	{
		it = data.lower_bound(date);
		if (it == data.begin())
		{
			it = data.end();
			--it;
		}
		else
			--it;
		std::cout << date << " => " << val << " = " << val * it->second << std::endl;
	}
}
