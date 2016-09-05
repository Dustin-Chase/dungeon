#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>
#include <JsonBox/JsonBox.h>

#include "Entity.hpp"

class EntityManager; 

class Item : public Entity {
	public: 
	
	std::string name; 
	std::string description; 
	
	Item(std::string id, std::string name, std::string description); 
	Item(std::string id, JsonBox::Value & v, EntityManager* mgr); 
	
	//load the item information from the JSON vale
	virtual void load(JsonBox::Value& v, EntityManager *mgr); 
	
};
#endif
