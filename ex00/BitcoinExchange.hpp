#ifndef BITCOIN_EXCHANGE_HPP
#define BITCOIN_EXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class Btc
{
private:
	enum Errors
	{
		NEGVAL,
		HUGEVAL,
		INVVAL,
		FORMAT,
		MD,
		YEAR,
		MONTH,
		DAY,
		INVLINE,
		RATE,
	};

	std::string line;
	std::string date;
	std::string value;
	std::string year;
	std::string month;
	std::string day;
	std::string errorMessage;
	size_t pipePos;
	int monthNum;
	int dayNum;
	int yearNum;
	float val;
	float rate;

	void splitData();
	void checkline();
	void parseDate();
	void parseValue();
	void throwError(Errors cause, std::string str);
	void checkMonthDay();
	void getRate();
	void storeData();
	std::map<std::string, float> data;
	
public:
	void parse(const std::string &filename);
	void displayBtc();
};

#endif
