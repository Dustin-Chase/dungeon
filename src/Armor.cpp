//Armor.cpp

#include <string>
#include <JsonBox.h>

#include "Armor.hpp"
#include "Item.hpp"
#include "EntityManager.hpp"

Armor::Armor(std::string id, std::string name, std::string description, int defense) :
	Item(id, name, description) {

	this->defense = defense; 
}

Armor::Armor(std::string id, JsonBox::Value & v, EntityManager* mgr) : Item(id, v, mgr) {
	
	this->load(v, mgr); 
}

void Armor::load(JsonBox::Value & v, EntityManager * mgr) {
	JsonBox::Object o = v.getObject(); 
	this->defense = o["defense"].getInteger(); 

	return; 

}
