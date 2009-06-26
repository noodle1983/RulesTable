#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <RulesTable.hpp>
using namespace std;

int main ()
{
	RulesTable2<int, int, int> table;
	table._rules[1]._rules[1] = 1;
	cout << table._rules[1]._rules[1] << endl;
	return 0;
}
