#include <iostream>
#include "Animal.h"
#include "Bear.h"
using namespace std;

int main()
{
	Animal ani;
	ani.setBirthDate("10-20-1997");
	int age = ani.getAge();
	Bear Ny;
	Ny.setDiet("Apples, Bamboo, Vodka");
	return 0;
}