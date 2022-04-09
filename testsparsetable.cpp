#include <stdio.h>
#include <iostream>
#include <SparseTable.hpp>

using namespace std;

int main ()
{
	SparseTable3<int, int, int, string> table;
	string str;
    cout << "----------------------------------" << endl;
    cout << "table.set(1, 1, 1, \"abc\");" << endl;
	table.set(1, 1, 1, "abc");
	cout << table << endl;
    cout << "----------------------------------" << endl;

	cout << "table[1][1][1]:" << table[1][1][1] << endl;
	cout << "table[1][1][3]:" << table[1][1][3] << endl;
	cout << table << endl;
    cout << "----------------------------------" << endl;

	cout << "table[1][1][3]:\"sadf\"" << endl;
	table[1][1][3] = "sadf";
	cout << table << endl;
    cout << "----------------------------------" << endl;

	cout << "table[1][1]:\"11\"" << endl;
	table[1][1] = "11";
	cout << table << endl;
    cout << "----------------------------------" << endl;
	//table.set(1, "def");
	//cout << "table.get(1, 2, 3):" << table.get(1, 2, 3) << endl;
	//cout << "table.get(1, 1, 1):" << table.get(1, 1, 1) << endl;
	//str = table[1][1][3];
	//cout << "table[1][1][3]=" << str << endl;

	return 0;
}
