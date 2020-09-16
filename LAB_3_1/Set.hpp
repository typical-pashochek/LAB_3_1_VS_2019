#pragma once

#include <iostream>
#include <fstream>

class Set
{
private:
	int size;
	char* mass;
	char** massPlus;
	char** massMult;

	int getIndex(char sym);
	bool commut();
	bool neutralAndReverse();
	bool assocAnsDistr();
	bool isElem(char sym);

public:
	Set();
	Set(char* _mass, char** _massPlus, char** _massMult, int _size);
	Set(const Set& object);
	Set(std::string fileName);

	void showSet();

	char plus(char a, char b);
	char mult(char a, char b);

	bool isField();
	~Set();
};

