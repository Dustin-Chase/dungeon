#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <string>
#include <map>

#include "Entity.hpp"

class EntityManager {
	private:
	
	std::map<std::string, Entity*> data; 
	
	public: 
	
	//load the JSON file and determine which map 
	//to save data to according to type T	
	template<typename T>
	void loadJson(std::string filename); 
	
	//return the entity given by id
	template<typename T>
	T* getEntity(std::string id); 

	//Constructor
	EntityManager(); 
	
	//Destructor
	~EntityManager(); 
	
};

template<typename T>
std::string entityToString(); 


#endif
