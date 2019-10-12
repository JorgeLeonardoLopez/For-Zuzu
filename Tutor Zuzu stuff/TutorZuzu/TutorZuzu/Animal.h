#pragma once
#include <string>;
using namespace std;

class Animal
{
	private:
		double height, weight;
		char gender;
		string name;
		int birthMonth, birthDay, birthYear;
		string birthDate;
		

	public:
		Animal() {};
		Animal(double _height, double _weight, char _gender);
		void setHeight(double _height);
		void setWeight(double _weight);
		void setGender(char _gender);
		void setName(string _name);
		void setBirthDate(string birthDate);

		double getHeight();
		double getWeight();
		char getGender();
		string getName();
		string getBirthDate();
		int getAge();
};