#pragma once
#include "Animal.h";
#include <ctime>

class Bear:Animal
{
	private:
	string diet[5];
	int ID;
	string type;
	bool madeBabies;

	public:
		Bear() {};
		Bear(string _diet, int _ID, string _type, bool _madeBabies);
		void setDiet(string _diet);
		void setID(int _ID);
		void setType(string _type);
		void setMadeBabies(bool _madeBabies);

		string getDiet();
		int getID();
		string getType();
		bool getMadeBabies();
};