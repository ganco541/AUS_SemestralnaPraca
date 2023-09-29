#include "Sequences.h"

Sequences::Sequences(std::string kraje, std::string okresy, std::string obce)
{
	this->kraje = new ds::amt::ImplicitSequence<UzemnaJednotka*>;
	this->okresy = new ds::amt::ImplicitSequence<UzemnaJednotka*>;
	this->obce = new ds::amt::ImplicitSequence<UzemnaJednotka*>;
	std::ifstream suborKraje;
	std::ifstream suborOkresy;
	std::ifstream suborObce;
	std::string line;
	bool first;
	suborKraje.open(kraje);
	suborOkresy.open(okresy);
	suborObce.open(obce);
	if (suborKraje.good() && suborOkresy.good() && suborObce.good())
	{
		first = true;
		while (std::getline(suborKraje, line, '\n'))
		{
			std::stringstream ujStream{ line };
			std::string sortN, code, officialTitle, mediumTitle, shortTitle, note;
			std::getline(ujStream, sortN, ';');
			std::getline(ujStream, code, ';');
			std::getline(ujStream, officialTitle, ';');
			std::getline(ujStream, mediumTitle, ';');
			std::getline(ujStream, shortTitle, ';');
			std::getline(ujStream, note);
			if (!first)
			{
				UzemnaJednotka* uj = new UzemnaJednotka(sortN, code, officialTitle, mediumTitle, shortTitle, note, 1);
				this->kraje->insertLast().data_ = uj;
			}
			else
			{
				first = false;
			}
			line = "";
		}
		first = true;
		while (std::getline(suborOkresy, line, '\n'))
		{
			std::stringstream ujStream{ line };
			std::string sortN, code, officialTitle, mediumTitle, shortTitle, note;
			std::getline(ujStream, sortN, ';');
			std::getline(ujStream, code, ';');
			std::getline(ujStream, officialTitle, ';');
			std::getline(ujStream, mediumTitle, ';');
			std::getline(ujStream, shortTitle, ';');
			std::getline(ujStream, note);
			if (!first)
			{
				UzemnaJednotka* uj = new UzemnaJednotka(sortN, code, officialTitle, mediumTitle, shortTitle, note, 2);
				this->okresy->insertLast().data_ = uj;
			}
			else
			{
				first = false;
			}
			line = "";
		}
		first = true;
		while (std::getline(suborObce, line, '\n'))
		{
			std::stringstream ujStream{ line };
			std::string sortN, code, officialTitle, mediumTitle, shortTitle, note;
			std::getline(ujStream, sortN, ';');
			std::getline(ujStream, code, ';');
			std::getline(ujStream, officialTitle, ';');
			std::getline(ujStream, mediumTitle, ';');
			std::getline(ujStream, shortTitle, ';');
			std::getline(ujStream, note);
			if (!first)
			{
				UzemnaJednotka* uj = new UzemnaJednotka(sortN, code, officialTitle, mediumTitle, shortTitle, note, 3);
				this->obce->insertLast().data_ = uj;
			}
			else
			{
				first = false;
			}
			line = "";
		}
	}
	suborKraje.close();
	suborOkresy.close();
	suborObce.close();
}

const ds::amt::ImplicitSequence<UzemnaJednotka*>& Sequences::getKraje()
{
	return *this->kraje;
}

const ds::amt::ImplicitSequence<UzemnaJednotka*>& Sequences::getOkresy()
{
	return *this->okresy;
}

const ds::amt::ImplicitSequence<UzemnaJednotka*>& Sequences::getObce()
{
	return *this->obce;
}

Sequences::~Sequences()
{
	for (size_t i = 0; i < this->kraje->size(); ++i)
	{
		delete this->kraje->access(i)->data_;
	}
	for (size_t i = 0; i < this->okresy->size(); ++i)
	{
		delete this->okresy->access(i)->data_;
	}
	for (size_t i = 0; i < this->obce->size(); ++i)
	{
		delete this->obce->access(i)->data_;
	}
	delete this->kraje;
	delete this->okresy;
	delete this->obce;
}