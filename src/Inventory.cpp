/*Inventory.cpp*/ 
#include <list>
#include <string>
#include <utility>
#include <iostream>
#include "JsonBox/JsonBox.h"

#include "Inventory.hpp"
#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "EntityManager.hpp"

template <typename T>
void Inventory::load(JsonBox::Value& v, EntityManager* mgr) {
	for(auto item : v.getArray()) {
		std::string itemId = item.getArray()[0].getString(); 
		int quantity = item.getArray()[1].getInteger(); 
		this->items.push_back(std::make_pair(mgr->getEntity<T>(itemId), quantity)); 
	}

}

template <typename T>
JsonBox::Array Inventory::jsonArray() {
	JsonBox::Array a; 
	for (auto item : this->items) {
		//skip if te id does not match to the Type T
		if(item.first->id.substr(0, entityToString<T>().size()) != entityToString<T>())
			continue; 
		//otherwise add the item to the array
		JsonBox::Array pair; 
		pair.push_back(JsonBox::Value(item.first->id)); 
		pair.push_back(JsonBox::Value(item.second)); 
		a.push_back(JsonBox::Value(pair)); 
	}
return a; 

}

JsonBox::Object Inventory::getJson()
{
    JsonBox::Object o;

    o["items"] = JsonBox::Value(jsonArray<Item>());
    o["weapons"] = JsonBox::Value(jsonArray<Weapon>());
    o["armor"] = JsonBox::Value(jsonArray<Armor>());

    return o;
}

void Inventory::add(Item* item, int count) {
	for (auto& it : this->items) {
		if (it.first->id == item->id) {
			it.second += count; 
			return; 
		}
	
	}
	this->items.push_back(std::make_pair(item, count)); 
}

void Inventory::remove(Item* item, int count) {
	for (auto it = this->items.begin(); it != this->items.end(); ++it) {
		if((*it).first->id == item->id) {
			(*it).second -= count; 
			if((*it).second < 1) this->items.erase(it); 
			return; 
		}

	}
}

template <typename T> 
T* Inventory::get(unsigned int n) {
	//using a list so we have to step through the list until 
	//we find the nth element
	unsigned int i = 0; 
	auto it = this->items.begin(); 
	for (; it != this->items.end(); ++it) {
		if ((*it).first->id.substr(0, entityToString<T>().size()) != entityToString<T>())
			continue; 
		if (i++ == n) break; 
	}	
	if(it != this->items.end()) 
		return dynamic_cast<T*>((*it).first); 
	else 
		return nullptr; 

}

int Inventory::count(Item * item) {
	for (auto it : this->items) {
		if(it.first->id == item->id) {
			return it.second; 
		}
		
	}
	return 0; 
}

template<typename T>
int Inventory::count(unsigned int n) {
	return count(get<T>(n)); 
}

template<typename T>
int Inventory::print(bool label) {
	unsigned int i = 1; 
	
	for (auto it : this->items) {

		//skip if the id does not match to the type T
		if(it.first->id.substr(0, entityToString<T>().size()) != entityToString<T>())
			continue; 
		if(label) std::cout << i++ << ": "; 
		//output the item name, quantity and description e.g.
		//gold piece (29) - glimmering disc of wealth
		std::cout << it.first->name << " (" << it.second << ") - "; 
		std::cout << it.first->description << std::endl;
	}
	
	return this->items.size();

}

//overload of print to print all items when the template argument is empty
int Inventory::print(bool label) {
	unsigned int i = 0; 
	
	if(items.empty()) {
		std::cout << "Nothing" << std::endl; 
	}
	else {
		i += print<Item>(label); 
		i += print<Weapon>(label); 
		i += print<Armor>(label); 
	}

	return i; 
}

void Inventory::clear() {
	this->items.clear();
}

void Inventory::merge(Inventory * inventory) {
	if(inventory == this) return; 
	
	for (auto it: inventory->items) this->add(it.first, it.second); 
		
	return; 

}

Inventory::Inventory(JsonBox::Value & v, EntityManager * mgr) {
	JsonBox::Object o = v.getObject(); 
	load<Item>(o["items"], mgr); 
	load<Weapon>(o["weapons"], mgr); 
	load<Armor>(o["armor"], mgr); 
}

// Template instantiations
template void Inventory::load<Item>(JsonBox::Value&, EntityManager*);
template void Inventory::load<Weapon>(JsonBox::Value&, EntityManager*);
template void Inventory::load<Armor>(JsonBox::Value&, EntityManager*);

template JsonBox::Array Inventory::jsonArray<Item>();
template JsonBox::Array Inventory::jsonArray<Weapon>();
template JsonBox::Array Inventory::jsonArray<Armor>();

template int Inventory::count<Item>(unsigned int);
template int Inventory::count<Weapon>(unsigned int);
template int Inventory::count<Armor>(unsigned int);

template Item* Inventory::get<Item>(unsigned int);
template Weapon* Inventory::get<Weapon>(unsigned int);
template Armor* Inventory::get<Armor>(unsigned int);

template int Inventory::print<Item>(bool);
template int Inventory::print<Weapon>(bool);
template int Inventory::print<Armor>(bool);

