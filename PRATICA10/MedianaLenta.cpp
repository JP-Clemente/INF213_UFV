#include <iostream>
#include "MedianaLenta.h"
#include <algorithm>
using namespace std;

void Mediana::insere(int el)
{
	elems.push_back(el);
	sort(elems.begin(), elems.end());
}

int Mediana::getMediana()
{
	if (elems.size() % 2)
	{
		return elems[elems.size() / 2];
	}
	else
	{
		return (elems[elems.size() / 2] + elems[(elems.size() / 2) - 1]) / 2;
	}
}
