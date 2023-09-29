#include "Hierarchy.h"


Hierarchy::Hierarchy(const ds::amt::ImplicitSequence<UzemnaJednotka*>& kraje, const ds::amt::ImplicitSequence<UzemnaJednotka*>& okresy, const ds::amt::ImplicitSequence<UzemnaJednotka*>& obce)
{
	this->hierarchy = new ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>;
	this->hierarchy->emplaceRoot().data_ = new UzemnaJednotka("", "", "Slovenská Republika", "Slovenská-Republika", "Slovensko", "", 0);
	size_t krajNumber{0};
	size_t okresNumber{0};
	
	for (size_t i = 0; i < kraje.size()-1; ++i)
	{
		this->hierarchy->emplaceSon(*this->hierarchy->accessRoot(), this->hierarchy->degree(*this->hierarchy->accessRoot())).data_ = kraje.access(i)->data_;
	}
	
	for (size_t i = 0; i < okresy.size(); ++i)
	{
		std::string codeSub = okresy.access(i)->data_->getCode().substr(0, 5);
		bool found{ false };
		auto root = this->hierarchy->accessRoot();
		for (size_t x = krajNumber; x < this->hierarchy->degree(*root); ++x)
		{
			auto kraj = this->hierarchy->accessSon(*root, x);
			std::string noteSub = kraj->data_->getNote().substr(5, 5);
			if (codeSub == noteSub)
			{
				this->hierarchy->emplaceSon(*kraj, this->hierarchy->degree(*kraj)).data_ = okresy.access(i)->data_;
				found = true;
				break;
			}
			else
			{
				++krajNumber;
			}
		}
	}
	krajNumber = 0;

	for (size_t i = 0; i < obce.size(); ++i)
	{
		std::string codeSub = obce.access(i)->data_->getCode().substr(3, 3);
		bool found{ false };
		auto root = this->hierarchy->accessRoot();
		for (int x = krajNumber; x < this->hierarchy->degree(*root); ++x)
		{
			auto kraj = this->hierarchy->accessSon(*root, x);
			for (int y = okresNumber; y < this->hierarchy->degree(*kraj); ++y)
			{
				auto okres = this->hierarchy->accessSon(*kraj, y);
				std::string noteSub = okres->data_->getCode().substr(3, 3);
				if (codeSub == noteSub)
				{
					this->hierarchy->emplaceSon(*okres, this->hierarchy->degree(*okres)).data_ = obce.access(i)->data_;
					found = true;
					break;
				}
				else
				{
					++okresNumber;
				}
			}
			if (found)
			{
				break;
			}
			else
			{
				++krajNumber;
				okresNumber = 0;
			}
		}
	}

	this->currentBlock = this->hierarchy->accessRoot();
}

void Hierarchy::setPopulation(std::string population)
{
	std::ifstream suborPop;
	std::string line;
	bool first{ true };
	suborPop.open(population);
	while (std::getline(suborPop, line, '\n'))
	{
		if (!first)
		{
			std::stringstream ujStream{ line };
			std::string code, popString;
			size_t pop{ 0 };
			std::getline(ujStream, code, ';');
			std::getline(ujStream, popString, ';');
			std::stringstream popStream{ popString };
			popStream >> pop;
			auto begin = hierarchy->beginPost();
			auto end = hierarchy->endPost();
			while (begin != end)
			{
				if ((*begin)->getType() == 3 && (*begin)->getCode() == code)
				{
					(*begin)->setPopulation(pop);
					break;
				}
				++begin;
			}
		}
		else
		{
			first = false;
		}
	}
	suborPop.close();

	size_t popOkresu{ 0 };
	size_t popKraja{ 0 };
	size_t popKrajiny{ 0 };

	auto begin = hierarchy->beginPost();
	auto end = hierarchy->endPost();

	while (begin != end)
	{
		if ((*begin)->getType() == 3)
		{
			popOkresu += (*begin)->getPopulation();
		}
		else if ((*begin)->getType() == 2)
		{
			(*begin)->setPopulation(popOkresu);
			popKraja += popOkresu;
			popOkresu = 0;
		}
		else if ((*begin)->getType() == 1)
		{
			(*begin)->setPopulation(popKraja);
			popKrajiny += popKraja;
			popKraja = 0;
		}
		else
		{
			(*begin)->setPopulation(popKrajiny);
		}
		++begin;
	}
}

const std::string& Hierarchy::getCurrentOfficialTitle()
{
	return this->currentBlock->data_->getOfficialTitle();
}

ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& Hierarchy::getHierarchy()
{
	return *this->hierarchy;
}

bool Hierarchy::moveUp()
{
	if (this->hierarchy->level(*this->currentBlock) != 0)
	{
		this->currentBlock = this->hierarchy->accessParent(*this->currentBlock);
		return true;
	}
	else
	{
		return false;
	}
}

bool Hierarchy::canMoveDown(size_t& numberOfSons)
{
	if (this->hierarchy->degree(*this->currentBlock) != 0)
	{
		this->printSonsWithId();
		numberOfSons = this->hierarchy->degree(*this->currentBlock);
		return true;
	}
	else
	{
		std::cout << "------------------------------------\n";
		std::cout << "You don't have any sons!\n";
		return false;
	}
}

void Hierarchy::moveDown(size_t son)
{
	this->currentBlock = this->hierarchy->accessSon(*this->currentBlock, son - 1);
}

void Hierarchy::printSons()
{
	if (this->hierarchy->degree(*this->currentBlock) != 0)
	{
		std::cout << "-------------------  " << this->currentBlock->data_->getOfficialTitle() << "  -----------------\n";
		bool first{ true };
		size_t j{ 0 };
		for (size_t i = 0; i < this->hierarchy->degree(*this->currentBlock); ++i)
		{
			if (first)
			{
				std::cout << this->currentBlock->sons_->access(i)->data_->data_->getOfficialTitle();
				first = false;
			}
			else
			{
				std::cout << ", " << this->currentBlock->sons_->access(i)->data_->data_->getOfficialTitle();
			}
			++j;
			if (j % 5 == 0)
			{
				std::cout << ",";
				std::cout << std::endl;
				first = true;
			}
		}
		if (!first)
		{
			std::cout << "\n";
		}
	}
	else
	{
		std::cout << "------------------------\n";
		std::cout << "You don't have any sons!\n";
	}
}

void Hierarchy::doPredicate(std::string find, size_t type)
{
	if (this->hierarchy->level(*this->currentBlock) != 3)
	{
		size_t inputPop{ 0 };
		ds::amt::ImplicitSequence<UzemnaJednotka*> sortedIs;
		size_t typeHas{ 0 };
		if (type == 3)
		{
			if (find == "1")
			{
				typeHas = 1;
			}
			else if (find == "2")
			{
				typeHas = 2;
			}
			else
			{
				typeHas = 3;
			}
		}
		else if (type == 4)
		{
			std::stringstream stream(find);
			stream >> inputPop;
		}
		
		algoritmus(this->beginFromCurrent(), this->hierarchy->endPre(), [&](UzemnaJednotka* block) {
			std::string uppercase = block->getShortTitle();
			std::transform(uppercase.begin(), uppercase.end(), uppercase.begin(), [](unsigned char c) {return std::toupper(c); });
			switch (type)
			{
			case 1:
				return startsWithStr(uppercase, find);
			case 2:
				return containsStr(uppercase, find);
			case 3:
				return hasType(block->getType(), typeHas);
			case 4:
				return popMoreThan(block->getPopulation(), inputPop);
			}
		}, [&sortedIs](UzemnaJednotka* block) {
			sortedIs.insertLast().data_ = block;
		});

		bool sort{ false };
		bool error{ false };
		while (!sort)
		{
			std::cout << "------------------------------------\n(1) compareAlphabetical\n(2) compareVowelsCount\n(3) Back\n------------------------------------\nChoose comparator from above: ";
			std::cin >> type;
			std::cout << "------------------------------------\n";
			if (type > 0 && type < 3)
			{
				ds::adt::QuickSort<UzemnaJednotka*> quickSort;
				std::locale loc("sk-SK");
				quickSort.sort(sortedIs, [&type, &loc](UzemnaJednotka* uj1, UzemnaJednotka* uj2)
					{
						switch (type)
						{
						case 1:
							return compareAlphabetical(uj1->getShortTitle(), uj2->getShortTitle(), loc) < 0;
						case 2:
							return compareVowelsCount(uj1->getShortTitle(), uj2->getShortTitle()) < 0;
						}
					});
				sort = true;
			}
			else if (type == 3)
			{
				error = true;
				sort = true;
			}
			else
			{
				std::cout << "Please choose a comparator!\n";
			}
		}

		if (!error)
		{
			size_t found{ 0 };
			std::string hlavicka{"SN;Code;Official Title;Medium Title;Short Title;Note;Population"};
			std::cout << "\n#######################################################################################################################################################################\n";
			for (size_t i = 0; i < sortedIs.size(); ++i)
			{
				if (found == 0)
				{
					vypis(hlavicka);
					std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
				}
				vypis(sortedIs.access(i)->data_->print());
				++found;
			}
			if (found != 0)
			{
				std::cout << "############################################################################ RESULTS: " << found << " ###########################################################################";
				if (found < 1000)
				{
					int mod = found % 1000;
					if (mod < 10)
					{
						std::cout << "####";
					}
					else if (mod < 100)
					{
						std::cout << "###";
					}
					else if (mod < 1000)
					{
						std::cout << "##";
					}
					std::cout << "\n";
				}
				else
				{
					std::cout << "#\n";
				}
			}
			else
			{
				std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||  NOTHING WAS FOUND!  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
				std::cout << "#######################################################################################################################################################################\n";
			}
		}
	}
	else
	{
		std::cout << "------------------------------------\n";
		std::cout << "You don't have any sons!\n";
	}
}

Hierarchy::~Hierarchy()
{
	delete this->hierarchy->accessRoot()->data_;
	delete this->hierarchy;
}

// Private
void Hierarchy::printSonsWithId()
{
	size_t i{ 1 };
	bool newLine{ false };
	std::cout << "-------------------  " << this->currentBlock->data_->getOfficialTitle() << "  -----------------\n";

	for (size_t j = 0; j < this->hierarchy->degree(*this->currentBlock); ++j)
	{
		std::cout << "(" << i << ") " << this->currentBlock->sons_->access(j)->data_->data_->getOfficialTitle() << " | ";
		++i;
		if (newLine)
		{
			newLine = false;
		}
		if (i % 5 == 0)
		{
			newLine = true;
			std::cout << "\n";
		}
	}
	if (!newLine)
	{
		std::cout << "\n";
	}
}

ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator Hierarchy::beginFromCurrent()
{
	return ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator{ this->hierarchy, this->currentBlock };
}

