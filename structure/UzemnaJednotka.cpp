#include "UzemnaJednotka.h"

UzemnaJednotka::UzemnaJednotka(std::string sortN, std::string code, std::string officialTitle, std::string mediumTitle, std::string shortTitle, std::string note, size_t type)
{
	this->sortN = sortN;
	this->code = code;
	this->officialTitle = officialTitle;
	this->mediumTitle = mediumTitle;
	this->shortTitle = shortTitle;
	this->note = note;
	this->type = type;
}

const std::string& UzemnaJednotka::getOfficialTitle()
{
	return this->officialTitle;
}

const std::string& UzemnaJednotka::getShortTitle()
{
	return this->shortTitle;
}

const std::string& UzemnaJednotka::getNote()
{
	return this->note;
}

const std::string& UzemnaJednotka::getCode()
{
	return this->code;
}

const size_t& UzemnaJednotka::getPopulation()
{
	return this->population;
}

void UzemnaJednotka::setPopulation(size_t p)
{
	this->population = p;
}

const size_t& UzemnaJednotka::getType()
{
	return this->type;
}

std::string UzemnaJednotka::print()
{
	std::string helperString{ "" };
	helperString.append(this->sortN).append(";").append(this->code).append(";").append(this->officialTitle).append(";").append(this->mediumTitle).append(";").append(this->shortTitle).append(";").append(this->note).append(";").append(std::to_string(this->population));
	return helperString;
}

UzemnaJednotka::~UzemnaJednotka()
{
}