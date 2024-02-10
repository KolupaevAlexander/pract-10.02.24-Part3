// Practic(10.02.24)part3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string.h>
// Дана анкета, каждая строка которой содержит информацию:
// 1) фамилия; 2) пол; 3) если пол женский, то год рождения; если пол
// мужской, то указать семейное положение(холост, женат) и количество детей.Составить упорядоченный по фамилиям список всех холостых мужчин, не имеющих детей.

struct Person
{
	char LastName[100];
	bool IsMan;

	union
	{
		int YearOfBirth;

		struct
		{
			bool isMaried;
			int childrenCount;
		}Man;
	}extraInfo;
};

Person setMenInfo(const char* lastName, bool isMaried, int childrenCount)
{
	Person person;
	strcpy_s(person.LastName, lastName);
	person.IsMan = true;
	person.extraInfo.Man.childrenCount = childrenCount;
	person.extraInfo.Man.isMaried = isMaried;
	return person;
}

Person setWomenInfo(const char* lastName, int YearOfBirth)
{
	Person person;
	strcpy_s(person.LastName, lastName);
	person.IsMan = false;
	person.extraInfo.YearOfBirth = YearOfBirth;
	return person;
}

int main()
{
	setlocale(LC_ALL, "rus");
	Person woman1 = setWomenInfo("Kozlov", 1998);
	Person woman2 = setWomenInfo("Leonova", 1950);
	Person woman3 = setWomenInfo("Smirnova", 1923);
	Person woman4 = setWomenInfo("Kozlova",1231);

	Person man1 = setMenInfo("Kozlov", true, 2);
	Person man2 = setMenInfo("Klimov", true, 0);
	Person man3 = setMenInfo("Titov", false,2);
	Person man4 = setMenInfo("Smirnov", false, 0);
	Person man5 = setMenInfo("Popov",false, 0);
	Person man6 = setMenInfo("Anosov",false, 0);

	Person persons[10] = { woman1, woman2, woman3, woman4, man1, man2, man3, man4, man5, man6 };

	Person neededPerson[10];
	int counter=0;

	for (const auto& person : persons)
	{
		if (person.IsMan && 
			!person.extraInfo.Man.isMaried && 
			person.extraInfo.Man.childrenCount == 0)
		{
			neededPerson[counter] = person;
			counter++;
		}
	}

	int neededPersonCount = counter;

	for (int i = 1; i < neededPersonCount; i++) {
		for (int j = 0; j < neededPersonCount-1; j++) {
			if (neededPerson[j].LastName < neededPerson[j+1].LastName) {
				Person a = neededPerson[j];
				neededPerson[j] = neededPerson[j + 1];
				neededPerson[j + 1] = a;
			}
		}
	}

	for (int i = 0; i <counter; i++)
	{
		std::cout << neededPerson[i].LastName<< std::endl;
	}
	return 0;
}
