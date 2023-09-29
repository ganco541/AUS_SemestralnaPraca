#pragma once
#include <string>
#include <libds/heap_monitor.h>
class UzemnaJednotka
{
private:
	std::string sortN;
	std::string code;
	std::string officialTitle;
	std::string mediumTitle;
	std::string shortTitle;
	std::string note;
	size_t population{ 0 };
	size_t type;
	
public:
	UzemnaJednotka(std::string sortN, std::string code, std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string note, size_t type);
	const std::string& getOfficialTitle();
	const std::string& getShortTitle();
	const std::string& getNote();
	const std::string& getCode();
	const size_t& getPopulation();
	void setPopulation(size_t p);
	const size_t& getType();
	std::string print();
	~UzemnaJednotka();
};


