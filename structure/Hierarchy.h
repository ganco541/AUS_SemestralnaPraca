#pragma once
#include <libds/amt/explicit_hierarchy.h>
#include <libds/adt/sorts.h>
#include <libds/adt/list.h>
#include <libds/heap_monitor.h>
#include <string>
#include <fstream>
#include "UzemnaJednotka.h"
#include "../utils/OutputOperations.h"
#include "../utils/Predicators.h"
#include "../utils/Comperators.h"


class Hierarchy
{
private:
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>* hierarchy;
	ds::amt::MultiWayExplicitHierarchyBlock<UzemnaJednotka*>* currentBlock;
	void printSonsWithId();
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>::PreOrderHierarchyIterator beginFromCurrent();

public:
	Hierarchy(const ds::amt::ImplicitSequence<UzemnaJednotka*>& kraje, const ds::amt::ImplicitSequence<UzemnaJednotka*>& okresy, const ds::amt::ImplicitSequence<UzemnaJednotka*>& obce);
	void setPopulation(std::string population);
	const std::string& getCurrentOfficialTitle();
	ds::amt::MultiWayExplicitHierarchy<UzemnaJednotka*>& getHierarchy();
	void doPredicate(std::string find, size_t predicate);
	bool moveUp();
	bool canMoveDown(size_t& numberOfSons);
	void moveDown(size_t son);
	void printSons();
	~Hierarchy();
};