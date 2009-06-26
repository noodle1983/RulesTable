#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <RulesTable.hpp>
using namespace std;

int main ()
{
	RulesTable2<int, int, int> table;
	int i = 0;
	table.setRule(1, 1, 1);
	cout << table.getRule(1,1,i) << i << endl;
	cout << (table[1][1]) << endl;
	return 0;
}
