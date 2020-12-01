#include <iostream>
#include <string.h>
#include "MyMap.h"

using namespace std;

int main()
{
        MyMap<string, int> m;

        string s;
        int cod = 0;

        while (cin >> s)
        {
                m.insert(pair<string, int>(s, cod));
                cout << s << " " << m[s] << endl;
                cod = m.size();
        }
}
