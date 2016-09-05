#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <JsonBox/JsonBox.h>
#include <string>

class EntityManager; 

class Entity {
	public:
	
	std::string id; 

	Entity(std::string id) {
		this->id = id; 
	}

	virtual ~Entity() {}
	virtual void loadJson(JsonBox::Value& v, EntityManager* mgr) = 0; 

};

#endif 
