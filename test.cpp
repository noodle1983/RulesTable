#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <RulesTable.hpp>

using namespace std;

int main ()
{
	RulesTable3<int, int, int, string> table;
	string i;
	table.setRule(1, 1, 1, "abc");
	table.setDefaultRule(1, "def");
	cout << table;
	cout << "get rules:" << table.getRule(1, 2, 3) << endl;

	return 0;
}
