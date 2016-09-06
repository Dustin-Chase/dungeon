/*dungeon.cpp*/
#include <cstdlib>
#include <ctime>
#include <JsonBox.h>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "EntityManager.hpp"
#include <iostream>

const std::string dataDir = "/home/dustin/Documents/Programming/C++/Dungeon/data/"; 
EntityManager entityManager; 

int main() {
	entityManager.loadJson<Item>(dataDir + "items.json"); 
	//entityManager.loadJson<Weapon>("weapons.json");
	//entityManager.loadJson<Armor>("armor.json"); 	
	std::cout << "Hello, world!" << std::endl;
	return 0;  
}
