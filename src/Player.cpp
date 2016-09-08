#include <unordered_set>
#include <cmath>
#include "JsonBox.h"

#include "Area.hpp"
#include "Player.hpp"
#include "Creature.hpp"
#include "EntityManager.hpp"

Player::Player(std::string name, int hp, int strength, int agility, double evasion,
	unsigned int xp, unsigned int level, std::string className) :
	Creature("player", name, hp, strength, agility, evasion, xp)
{
	this->level = level;
	this->className = className;
}

Player::Player() : Player::Player("", 0, 0, 0, 0.0, 0, 1, "nullid")
{
}

Player::Player(JsonBox::Value& saveData, JsonBox::Value& areaData, EntityManager* mgr) : Player::Player()
{
	this->load(saveData, mgr);
	this->loadArea(areaData, mgr);
}

JsonBox::Object Player::toJson()
{
	JsonBox::Object o = Creature::toJson();

	o["className"] = JsonBox::Value(this->className);
	o["level"] = JsonBox::Value(int(this->level));

	return o;
}

void Player::save(EntityManager* mgr)
{
	// Construct JSON representation of the player
	// and save it to a file
	JsonBox::Value v(this->toJson());
	v.writeToFile(this->name + ".json");

	// Construct a JSON object containing the areas
	// the player has visited 
	JsonBox::Object o;
	for(auto area : this->visitedAreas)
	{
		o[area] = mgr->getEntity<Area>(area)->getJson();
	}
	JsonBox::Value v2(o);
	// Write the object to a file similar to the player data
	v2.writeToFile(this->name + "_areas.json");

	return;
}

// Attempt to load all data from the JSON value
void Player::load(JsonBox::Value& saveData, EntityManager* mgr)
{
	// Load data shared with Creature
	Creature::load(saveData, mgr);

	// Load optional variables
	JsonBox::Object o = saveData.getObject();

	this->className = o["className"].getString();
	this->level = o["level"].getInteger();

	return;
}

void Player::loadArea(JsonBox::Value& areaData, EntityManager* mgr)
{
	// Load the area
	JsonBox::Object o = areaData.getObject();
	for(auto area : o)
	{
		std::string key = area.first;
		mgr->getEntity<Area>(key)->load(area.second, mgr);
		this->visitedAreas.insert(key);
	}

	return;
}
