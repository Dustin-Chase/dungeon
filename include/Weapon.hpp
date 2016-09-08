//weapon.hpp
#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>
#include <JsonBox.h>

#include "Item.hpp"

class EntityManager; 

class Weapon : public Item {
	public:
	int damage; 

	Weapon(std::string id, std::string name, std::string description, int damage); 
	Weapon(std::string id, JsonBox::Value& v, EntityManager* mgr); 
	
	void load(JsonBox::Value& v, EntityManager * mgr); 

};

#endif
