/*Inventory.hpp*/ 
#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <list>
#include <utility>
#include <JsonBox/JsonBox.h>

#include "EntityManager.hpp"

class Item; 
class Weapon; 
class Armor; 

class Inventory {
	private:
	//using a list, but could use std::map instead. map would provide 
	//faster lookups (depending on the hash), but not O(1) insertions
	std::list<std::pair<Item*, int>> items; 
	
	template<typename T>
	void load(JsonBox::Value& v, EntityManager* mgr); 

	template <typename T>
	JsonBox::Array jsonArray(); 

	public: 
	void add(Item * item, int count); 
	
	void remove(Item* item, int count); 
	
	int count(Item* item); 
	template <typename T>
	int count(unsigned int n); 
	
	template <typename T>
	T* get(unsigned int n); 

	//output list of item to stdout
	template <typename T>
	int print(bool label = false); 

	//empty the inventory
	void clear(); 

	//merge this inventory with another
	//add counts if items already in inventory, 
	//insert new item if not already in the inventory
	void merge(Inventory* inventory); 
	
	//Load the inventory from a JSON value
	Inventory(JsonBox::Value& v, EntityManager* mgr); 
	Inventory() {}

	//print the entire inventory, or "nothing" if empty
	int print(bool label = false); 

	//get a Json object representation of the inventory
	JsonBox::Object getJson(); 


};

#endif /*Inventory.hpp*/ 
