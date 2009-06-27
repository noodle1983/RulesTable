#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <RulesTable.hpp>

using namespace std;

int main ()
{
	RulesTable3<int, int, int, string> table;
	string str;
	table.setRule(1, 1, 1, "abc");
	table[1][1][3] = "sadf";
	table.setDefaultRule(1, "def");
	cout << table << endl;
	cout << "table.getRule(1, 2, 3):" << table.getRule(1, 2, 3) << endl;
	cout << "table.getRule(1, 1, 1):" << table.getRule(1, 1, 1) << endl;
	str = table[1][1][3];
	cout << "table[1][1][3]=" << str << endl;

	return 0;
}
