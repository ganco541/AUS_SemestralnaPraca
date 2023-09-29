#pragma once
#include "UzemnaJednotka.h"
#include "../utils/Algorithm.h"
#include "../utils/OutputOperations.h"
#include <libds/adt/table.h>
#include <libds/adt/list.h>
#include <libds/heap_monitor.h>
#include <libds/amt/explicit_hierarchy.h>

class Tables
{
private:
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* krajeTable;
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* okresyTable;
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* obceTable;
	ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>** selectionTable;
	void deleteTable(ds::adt::HashTable<std::string, ds::adt::ImplicitList<UzemnaJednotka*>*>* table);
public:
	Tables(ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& hierarchy);
	void setTable(size_t table);
	void findAndPrint(std::string& key, ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& hierarchy);
	~Tables();
};