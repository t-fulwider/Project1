#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "AVL.h"

using namespace std;

int main(){
	system("clear");
	AVL tree;
	string numCommands;
	getline(cin, numCommands);

	for (int i = 0; i < stoi(numCommands); i++)
	{
		string line;
		getline(cin, line);

		istringstream inStream(line);
		string function;
		getline(inStream, function, ' ');

		string next;
		getline(inStream, next, '"');

		string name;
		getline(inStream, name, '"');

		getline(inStream, next, ' ');

		string ufid;
		getline(inStream, ufid);

		if (function == "insert")
			tree.Insert(name, ufid);
		else if (function == "search")
		{
			if (name.empty())
			{
				// cannot just call searchID because Insert used SearchID
				// (Do not want to print unsuccessful/successful twice)
				string nameStr = tree.SearchID(next);
				if (!nameStr.empty())
					cout << nameStr;
				else
					cout << "unsuccessful";
			}
			else
				tree.SearchName(name);
		}
		else if (function == "printInorder")
			tree.PrintInorder();
		else if (function == "printPostorder")
			tree.PrintPostorder();
		else if (function == "printPreorder")
			tree.PrintPreorder();
		else if (function == "printLevelCount")
			tree.PrintLevelCount();
		else if (function == "remove")
			tree.RemoveID(next);
		else if (function == "removeInorder")
			tree.RemoveInorder(stoi(next));
		else
			cout << "unsuccessful";

		cout << endl;
	}

	return 0;
}