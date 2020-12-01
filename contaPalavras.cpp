#include <iostream>
#include <string.h>
#include <stdio.h>
#include "MySet.h"
#include "MyVecNewIterator.h"

using namespace std;

int main(int argc, char *argv[])
{

    char str1[] = "myset";
    char str2[] = "myvec";

    int result1 = strcmp(argv[1], str1);
    int result2 = strcmp(argv[1], str2);

    if (result1 == 0)
    {
        MySet<string> s;
        int total = 0;

        string str;

        while (cin >> str)
        {
            total++;
            s.insert(str);
        }

        cout << total << " " << s.size() << endl;
    }

    else if (result2 == 0)
    {
        MyVec<string> s;

        int total = 0;

        string str;

        while (cin >> str)
        {
            int exist = 0;
            total++;
            for (int i = 0; i < s.size(); i++)
            {

                if (s[i] == str)
                {
                    exist++;
                }
            }
            if (exist == 0)
            {
                s.push_back(str);
            }
        }
        cout << total << " " << s.size() << endl;
    }
}
