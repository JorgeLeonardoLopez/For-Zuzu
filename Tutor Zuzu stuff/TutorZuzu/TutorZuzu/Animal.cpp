#include "Animal.h";
Animal::Animal(double _height, double _weight, char _gender)
{
	height = _height;
	weight = _weight;
	gender = _gender;
}
void Animal::setHeight(double _height)
{
	height = _height;
}
void Animal::setWeight(double _weight)
{
	weight = _weight;
}
void Animal::setGender(char _gender)
{
	gender = _gender;
}
void Animal::setName(string _name)
{
	name = _name;
}
void Animal::setBirthDate(string _birthDate)
{
	birthDate = _birthDate;
	string monthRange = birthDate.substr(0, 2);
	string dayRange = birthDate.substr(3, 2);
	string yearRange = birthDate.substr(6, 4);
	birthMonth = stoi(monthRange);
	birthDay = stoi(dayRange);
	birthYear = stoi(yearRange);

}
double Animal::getHeight()
{
	return height;
}
double Animal::getWeight()
{
	return weight;
}
char Animal::getGender()
{
	return gender;
}
string Animal::getName()
{
	return name;
}
string Animal::getBirthDate()
{
	return birthDate;
}
int Animal::getAge()
{
	int currentYear = 2019;
	int currentDay = 12;
	int currentMonth = 10;

	int age = (currentYear - birthYear);
	if (currentMonth > birthMonth)
	{
		return age;
	}
	else if(currentMonth = birthMonth)
	{
		if (currentDay >= birthDay)
		{
			return age;
		}
		else
			return (age - 1);
	}
	else
	{
		return (age - 1);
	}

}