#include "stdafx.h"

#include "player.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#ifndef _TYPES_H
	#include "types.h"
#endif

CPlayer::CPlayer()
{
	//Each player begins the game with 30 health points. 
	mHealth = 30;
}
CPlayer::~CPlayer()
{
	/*
	//delete pointer to card on player class temination
	for (int i = 0; i < deck.size(); ++i)	{ delete deck[i]; }
	for (int i = 0; i < hand.size(); ++i)	{ delete hand[i]; }
	for (int i = 0; i < table.size(); ++i)	{ delete table[i]; }
	*/
}
//assign values from file
void CPlayer::assignFromFile(std::string filename)
{
	std::ifstream file(filename); 
	std::string line;
	std::string type, name, attack, health;
	if (!file)
	{
		std::cout << "Unable to open file " << filename << std::endl;
		return;
	}

#if _DEBUG
	std::cout << std::endl << "Loaded cards from: " << filename << std::endl;
#endif

	int count = 0;
	while (file.good())
	{
		//load the fline from the file and place into stringstream
		std::getline(file, line);
		std::stringstream ss(line);

		//parse the file by spaces and assign varibles accrodingly
		std::getline(ss, type, ' ');
		std::getline(ss, name, ' ');
		std::getline(ss, attack, ' ');
		if (std::stoi(type) != 3)
		{
			//lightning does't have a specified health
			std::getline(ss, health, '\n');
		}
		else
		{
			std::cout << "light" << std::endl;
			//read to end of line and ignore the values
			std::string ignore;
			std::getline(ss, ignore, '\n');
			health = "0";
		}
		//shouldn't be reached, possible bug if health is null
		if (type == "") { return; }

		//add new element to the array for each card (dependant of card type)
		switch (std::stoi(type))
		{
		case 1:
			deck.emplace_back(new CMinion);
			break;
		case 2:
			deck.emplace_back(new CFireball);
			break;
		case 3:
			deck.emplace_back(new CLightning);
			break;
		case 4:
			deck.emplace_back(new CBless);
			break;
		case 5:
			deck.emplace_back(new CVampire);
			break;
		case 6: //Wall type is not a special class, just uses generic type
			deck.emplace_back(new CCard);
			break;
		case 7:
			deck.emplace_back(new CHorde);
			break;
		case 8:
			deck.emplace_back(new CTrample);
			break;
		case 9:
			deck.emplace_back(new CLeech);
			break;
		case 10:
			deck.emplace_back(new CSword);
			break;
		case 11:
			deck.emplace_back(new CArmour);
			break;
		default: //generic card -- should not be used, just in case.
			deck.emplace_back(new CCard);
			break;
		}

		//assign varibles to class
		deck[count]->setType(std::stoi(type));
		deck[count]->setName(name);
		deck[count]->setAttack(std::stoi(attack));
		if (health != "") { deck[count]->setHealth(std::stoi(health)); }	//catch cards with no defined health value (i.e. lightning)
		else { deck[count]->setHealth(0); }									//assign the card 0 health
		deck[count]->setArmour(false);										//by default no minion should have armour
		deck[count]->setRemove(false);

#if _DEBUG
		std::cout
			<< "I: " << count << " "
			<< "T: " << deck[count]->getType() << "	"
			<< "N: " << deck[count]->getName() << "	"
			<< "A: " << deck[count]->getAttack() << "	"
			<< "H: " << deck[count]->getHealth() << "	"
			<< std::endl;
#endif

		//iterate for next card
		count++;
	}
	mSize = count;
}

void CPlayer::removeTableCard(int v)
{
	std::swap(table[v], table.back());
	table.pop_back();
}

//GETTERS
CCard& CPlayer::getDeckCard(int v)
{
	return *deck[v];
}
CCard& CPlayer::getHandCard(int v)
{
	return *hand[v];
}
CCard& CPlayer::getTableCard(int v)
{
	return *table[v];
}
int CPlayer::getSizeOfDeck()
{
	return deck.size();
}
int CPlayer::getSizeOfHand()
{
	return hand.size();
}
int CPlayer::getSizeOfTable()
{
	return table.size();
}
int CPlayer::getHealth()
{
	return mHealth;
}

//SETTERS
void CPlayer::setHealth(int v)
{
	mHealth = v;
}
void CPlayer::setHandCard(int v)
{
	hand.push_back(std::move(deck[v]));
	//remove card from hand
	std::swap(deck[v], deck.back());
	deck.pop_back();
	mSize--;	//delete?
}
void CPlayer::setTableCard(int v)
{
	table.push_back(std::move(hand[v]));
	//remove card from hand
	std::swap(hand[v], hand.back());
	hand.pop_back();
}

