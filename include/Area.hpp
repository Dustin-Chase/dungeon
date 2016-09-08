/*Area.hpp*/ 
#ifndef AREA_HPP
#define AREA_HPP

#include <vector>
#include <string>
#include <JsonBox/JsonBox.h>

#include "Entity.hpp"
#include "Inventory.hpp"
#include "Dialogue.hpp"

class EntityManager; 
class Door; 

class Area: public Entity {
	public: 
	Dialogue dialogue; 
	
	Inventory items; 
	
	std::vector<Door *> doors; 

	std::vector<Creature> creatures;

	Area(std::string id, Dialogue dialogue, Inventory items, 
		std::vector<Creature*> creatures);
	Area(std::string id, JsonBox::Value& v, EntityManager* mgr); 
	
	void load(JsonBox::Value& v, EntityManager* mgr); 
	
	JsonBox::Object getJson(); 

};

#endif
