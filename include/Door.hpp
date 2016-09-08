/*Door.hpp*/
#ifndef DOOR_HPP
#define DOOR_HPP

#include <string>
#include <utility>

#include "Entity.hpp"

class Item; 
class EntityManager; 

class Door : public Entity {
	public:
	std::string description; 
	
	//<0 is open
	// 0 is unlocked but closed
	// >0 is locked and needs key to open
	int locked; 
	Item * key; 

	std::pair<std::string, std::string> areas; 
	
	Door(std::string id, std::string description, std::pair<std::string, std::string> areas, 
		int locked, Item* key = nullptr); 
	Door(std::string id, JsonBox::Value & v, EntityManager * mgr); 
	void load(JsonBox::Value & v, EntityManager* mgr); 


};

#endif //door.hpp
