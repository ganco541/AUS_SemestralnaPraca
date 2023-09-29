#pragma once
#include <libds/amt/implicit_sequence.h>
#include <fstream>
#include "UzemnaJednotka.h"

class Sequences
{
private:
	ds::amt::ImplicitSequence<UzemnaJednotka*>* kraje;
	ds::amt::ImplicitSequence<UzemnaJednotka*>* okresy;
	ds::amt::ImplicitSequence<UzemnaJednotka*>* obce;
public:
	Sequences(std::string kraje, std::string okresy, std::string obce);
	const ds::amt::ImplicitSequence<UzemnaJednotka*>& getKraje();
	const ds::amt::ImplicitSequence<UzemnaJednotka*>& getOkresy();
	const ds::amt::ImplicitSequence<UzemnaJednotka*>& getObce();
	~Sequences();
};