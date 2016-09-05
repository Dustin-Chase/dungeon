#ifndef ARMOR_HPP
#define ARMOR_HPP

#include <string>
#include <JsonBox/JsonBox.h>

#include "Item.hpp"

class EntityManager; 

class Armor: public Item {
	
	public: 
	
	int defense; 

	Armor(std::string id, std::string name, std::string description, int defense); 
	Armor(std::string id, JsonBox::Value& v, EntityManager * mgr); 

	//load the armor from the JSON value
	void load(JsonBox::Value& v, EntityManager* mgr); 

};

#endif
