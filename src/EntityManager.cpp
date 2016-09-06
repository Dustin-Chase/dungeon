#include <iostream>
#include <string>
#include <map>
#include "Item.hpp"
#include "EntityManager.hpp"

template<class T>
void EntityManager::loadJson(std::string filename) {
	JsonBox::Value v; 
	v.loadFromFile(filename); 
	
	JsonBox::Object o = v.getObject();
	for(auto entity : o) {
		std::string key = entity.first;  		
		this->data[key] = dynamic_cast<Entity*>(new T(key, entity.second, this)); 
	}

}

template<class T>
T* EntityManager::getEntity(std::string id) {
	//The id prefix should match to the type T, so take the 
	//first characters of the id up to the length of the 
	//prefix and compare the two
	if (id.substr(0, entityToString<T>().size()) == entityToString<T>()) {
		return dynamic_cast<T*>(this->data.at(id)); 
	}
	else {
		return nullptr; 	
	}

}

EntityManager::EntityManager() {}

EntityManager::~EntityManager() {
		
	for (auto& entity : this->data) {
		std::cout << "Deleting " << entity.first << "\n";
		std::cout << "Printing " << entity.second->id << "\n"; 
		delete entity.second;		
	}
}

template void EntityManager::loadJson<Item>(std::string);
