/*dungeon.cpp*/
#include <cstdlib>
#include <ctime>
#include <JsonBox.h>
#include <iostream>
#include <string>

#include "Item.hpp"
#include "Weapon.hpp"
#include "Armor.hpp"
#include "EntityManager.hpp"


const std::string dataDir = "/home/dustin/Documents/Programming/C++/Dungeon/data/"; 
EntityManager entityManager; 

int main() {
	entityManager.loadJson<Item>(dataDir + "items.json"); 
	entityManager.loadJson<Weapon>(dataDir + "weapons.json");
	entityManager.loadJson<Armor>(dataDir + "armor.json"); 	
	std::cout << "Hello, world!" << std::endl;
	while(true) {
		std::string userInput; 
		std::cin >> userInput; 
		if (userInput == "Hello") {
			std::cout << "Hello back." << "\n"; 
		}
		else if (userInput == "Quit") {
			std::cout << "Ok" << "\n"; 
			break; 

		}
		else {
			std::cout << "What?" << "\n"; 
		}
	
	}	

	std::srand(std::time(nullptr)); 	
	return 0;  
}
