#include "Tables.h"

Tables::Tables(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& hierarchy)
{
	this->krajeTable = new ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>;
	this->okresyTable = new ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>;
	this->obceTable = new ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>;
	this->selectionTable = nullptr;

	algoritmus(hierarchy.beginPre(), hierarchy.endPre(),
		[&](UzemnaJednotka* uj) 
		{
			switch (uj->getType())
			{
			case 1:
				this->selectionTable = &this->krajeTable;
				break;
			case 2:
				this->selectionTable = &this->okresyTable;
				break;
			case 3:
				this->selectionTable = &this->obceTable;
				break;
			default:
				return false;
			}
			return true;
		},
		[&](UzemnaJednotka* uj) 
		{
			std::string key = uj->getShortTitle();
			std::transform(key.begin(), key.end(), key.begin(), ::toupper);
			ds::adt::ImplicitList<UzemnaJednotka*>** data{nullptr};
			if ((*this->selectionTable)->tryFind(key, data))
			{
				(*data)->insertLast(uj);
			}
			else
			{
				ds::adt::ImplicitList<UzemnaJednotka*>* tmp = new ds::adt::ImplicitList<UzemnaJednotka*>;
				tmp->insertLast(uj);
				(*this->selectionTable)->insert(key, tmp);
			}
		});
	this->selectionTable = nullptr;
}

void Tables::setTable(size_t table)
{
	switch (table)
	{
	case 1:
		this->selectionTable = &this->krajeTable;
		break;
	case 2:
		this->selectionTable = &this->okresyTable;
		break;
	case 3:
		this->selectionTable = &this->obceTable;
		break;
	}
}

void Tables::findAndPrint(std::string& key, ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& hierarchy)
{
	std::string hlavicka{ "SN;Code;Official Title;Medium Title;Short Title;Note;Population" };
	ds::adt::ImplicitList<UzemnaJednotka*>** data{ nullptr };
	std::cout << "#######################################################################################################################################################################\n";
	if ((*this->selectionTable)->tryFind(key, data))
	{
		size_t found{0};
		auto beginPre = hierarchy.beginPre();
		auto endPre = hierarchy.endPre();
		algoritmus((*data)->begin(), (*data)->end(),
			[](UzemnaJednotka* block)
			{
				return true;
			},
			[&found, &hlavicka, &hierarchy, &endPre, &beginPre](UzemnaJednotka* block)
			{
				if (found == 0)
				{
					vypis(hlavicka);
					std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
					std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
				}
				while (beginPre != endPre)
				{
					if ((block->getType() == 2 || block->getType() == 3) && (*beginPre)->getType() < block->getType() && (((*beginPre)->getType() == 1 && (*beginPre)->getNote().find(block->getCode().substr(0, 5)) != std::string::npos) || ((*beginPre)->getType() == 2 && (*beginPre)->getCode().find(block->getCode().substr(0, 6)) != std::string::npos)))
					{
						vypis((*beginPre)->print());
						if (((*beginPre)->getType() == 2 && block->getType() == 3) || ((*beginPre)->getType() == 1 && block->getType() == 2))
						{
							++beginPre;
							break;
						}
					}
					++beginPre;
				}
				vypis(block->print());
				std::cout << "-----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
				++found;
			});
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
		std::cout << "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||  KEY WAS NOT FOUND!  |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
		std::cout << "#######################################################################################################################################################################\n";
	}
}

void Tables::deleteTable(ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* table)
{
	algoritmus(table->begin(), table->end(), [](ds::adt::TableItem<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>& tableItem) {return true; },
		[](ds::adt::TableItem<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>& tableItem)
		{
			delete tableItem.data_;
		});
	delete table;
}

Tables::~Tables()
{
	this->deleteTable(this->krajeTable);
	this->deleteTable(this->okresyTable);
	this->deleteTable(this->obceTable);
}