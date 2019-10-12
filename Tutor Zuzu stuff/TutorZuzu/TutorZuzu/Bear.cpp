#include "Bear.h";
Bear::Bear(string _diet, int _ID, string _type, bool _madeBabies)
{
	ID = _ID;
	type = _type;
	madeBabies = _madeBabies;
}

void Bear::setDiet(string _diet)
{
	//We want to break up the _diet string based of where the commas are
	//We want to do this with out having to mannually figure out the locations all the time
	//In other words we want to loop through the string and use temporary variables to do the process

	int _dietStringSize = _diet.size(); // This will be used as the condition for our while loop
	string beforeComma, afterComma; // These will be the strings created once we find a comma
	int commaLocation, counter = 0;  // This will be used to add elements into the array

	//While loop, while the condition of _dietStringSize > 0 is true continue the pocess
	while (_dietStringSize > 0) 
	{
		commaLocation = _diet.find(","); // Find the first comma

		beforeComma = _diet.substr(0, commaLocation); // Create a string that is from the begining of the original string all the way to the where we found the comma

		afterComma = _diet.substr(commaLocation + 1); // Create a second string that starts one over where we found the first comma and ends at the end of the string (i.e. getting all other commas as well)

		diet[counter] = beforeComma; // Add the item to the array

		counter++; // Increase our position in the array

		_diet = afterComma; // Change the parameter string to be all of it minus the section that we have added to the array

		if (commaLocation == -1) // If at the start in the _diet.find(",") we get -1 it means there are no more commas
		{
			_dietStringSize = 0; // Therefore we set the exit condition to 0 so that the while loop ends
		}
		else // else we want to update the exit condition with the new string size
		{
			_dietStringSize = _diet.size();
		}
	}
}
void Bear::setID(int _ID)
{
	ID = _ID;
}
void Bear::setType(string _type)
{
	type = _type;
}
void Bear::setMadeBabies(bool _madeBabies)
{
	madeBabies = _madeBabies;
}

int Bear::getID()
{
	return ID;
}
string Bear::getType()
{
	return type;
}
bool Bear::getMadeBabies()
{
	return madeBabies;
}