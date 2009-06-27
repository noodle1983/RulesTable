#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <RulesTable.hpp>

using namespace std;

int main ()
{
	RulesTable2<int, int, string> table;
	string i;
	table.setRule(1, 1, "abc");
	cout << table.getRule(1,1,i) << i << endl;
	cout << (table[1][1]) << endl;
	cout << table;
	return 0;
}
