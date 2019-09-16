#include "Student.h"

void Student::show()
{
	Person::show();
	cout << setw(10) << grade << endl;
}

string Student::save()
{
	string g = to_string(grade);
	return Person::save() + "," + g;
}