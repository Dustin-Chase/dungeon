/*Dialogue.hpp*/ 

#ifndef DIALOGUE_HPP
#define DIALOGUE_HPP

#include <string>
#include <map>
#include <iostream>
#include <JsonBox/JsonBox.h>

#include "Area.hpp"
#include "Player.hpp"

//gameplay is expressed in a dialogue which has a <map> of 
//known action words. The user enters one and if they do not enter
//a valid one the dialogue loops until they do

typedef void (*ActionFunction)(Player * player, Area * area);

class Dialogue {
	private:
	//intial piece of information the dialogue displays	
	std::string description; 
	
	std::map<std::string, ActionFunction> choices;
	
	public:
	std::string activate() {
		std::cout << description << std::endl; 
		
		//std::cout << choices.keys() << std::endl; 

		std::string userInput; 

		while (true) {
			std::cin >> userInput; 

			//valid means the action is in the choices <map>
			if (choices.find(userInput) != choices.end()) {
				return userInput; 
			}

		}

	}


	Dialogue(std::string description, std::map<std::string, ActionFunction>& choices)
	{
		this->description = description;
		this->choices = choices;
	}

	// Create a dialogue from a JSON value
	Dialogue(JsonBox::Value& v)
	{
		JsonBox::Object o = v.getObject();
		//description = o["description"].getString();
		//for(auto choice : o["choices"].getArray())
		//	choices.push_back(choice.getString());
	}

	Dialogue() {}

	void addChoice(std::string choice, ActionFunction func)
	{
		this->choices.insert({choice, func}); 
	}

	unsigned int size()
	{
		return this->choices.size();
	} 

};

#endif
