#include "Set.hpp"

Set::Set()
{
	this->size = 0;
}


Set::Set(char* _mass, char** _massPlus, char** _massMult, int _size)
{
	this->size = _size;

	if (this->size < 0) {
		std::cout << "Ошибка: отрицательное число элементов" << std::endl;
		exit(1);
	}
	if (this->size == 0) {
		return;
	}
	this->mass = new char[this->size];
	this->massMult = new char* [this->size];
	this->massPlus = new char*[this->size];

	for (int i = 0; i < this->size; ++i) {
		this->mass[i] = _mass[i];
		this->massPlus[i] = new char[this->size];
		this->massMult[i] = new char[this->size];
		for (int j = 0; j < this->size; ++j) {
			this->massPlus[i][j] = _massPlus[i][j];
			this->massMult[i][j] = _massMult[i][j];
		}		
	}
}

Set::Set(const Set& object) {
	this->size = object.size;
	if (this->size == 0) {
		return;
	}
	
	this->mass = new char[this->size];
	this->massPlus = new char* [this->size];
	this->massMult = new char* [this->size];

	for (int i = 0; i < this->size; ++i) {
		this->mass[i] = object.mass[i];
		this->massPlus[i] = new char[this->size];
		this->massMult[i] = new char[this->size];
		for (int j = 0; j < this->size; ++j) {
			this->massPlus[i][j] = object.massPlus[i][j];
			this->massMult[i][j] = object.massMult[i][j];
		}
	}
}

Set::Set(std::string fileName)
{
	std::ifstream setFile(fileName);

	if (!setFile.is_open()) {
		std::cout << "Ошибка открытия файла" << std::endl;
		exit(1);
	}

	char ch;
	this->size = 0;

	if (!setFile.get(ch)) {
		std::cout << "Ошибка чтения из файла" << std::endl;
		exit(1);
	}

	while (ch != '\n') {
		if (ch > '9' || ch < '0') {
			std::cout << "Ошибка чтения числа элементов" << std::endl;
			exit(1);
		}
		else {
			this->size = this->size * 10 + ch - '0';
		}
		if (!setFile.get(ch)) {
			std::cout << "Ошибка чтения из файла" << std::endl;
			exit(1);
		}
	}

	if (this->size == 0) {
		return;
	}

	this->mass = new char[this->size];

	for (int i = 0; i < this->size; i++) {
		if (!setFile.get(this->mass[i])) {
			std::cout << "Ошибка чтения из файла: элементы" << std::endl;
			exit(1);
		}
		setFile.get();
	}

	this->massPlus = new char* [this->size];

	for (int i = 0; i < this->size; ++i) {
		this->massPlus[i] = new char[size];
		for (int j = 0; j < this->size; ++j) {
			if (!setFile.get(this->massPlus[i][j])) {
				std::cout << "Ошибка чтения из файла: матрица сложения" << std::endl;
				exit(1);
			}
			if (!this->isElem(massPlus[i][j])) {
				std::cout << "Прочитан элемент не из множества" << std::endl;
				exit(1);
			}
			setFile.get();
		}
	}


	this->massMult = new char* [this->size];


	for (int i = 0; i < this->size; ++i) {
		this->massMult[i] = new char[this->size];
		for (int j = 0; j < this->size; ++j) {
			if (!setFile.get(this->massMult[i][j])) {
				std::cout << "Ошибка чтения из файла: матрица умножения" << std::endl;
				exit(1);
			}
			if (!this->isElem(massMult[i][j])) {
				std::cout << "Прочитан элемент не из множества" << std::endl;
				exit(1);
			}
			setFile.get();
		}
	}
	setFile.close();
}

void Set::showSet()
{
	if (this->size == 0) {
		std::cout << "showSet: Пустое множество"<< std::endl;
		return;
	}

	std::cout << "Size = " << this->size << std::endl;

	for (int i = 0; i < this->size; ++i) {
		std::cout << this->mass[i] << " ";
	}

	std::cout << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << this->massPlus[i][j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			std::cout << this->massMult[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int Set::getIndex(char sym)
{
	if (this->size == 0) {
		std::cout << "getIndex: Пустое множество" << std::endl;
		return -1;
	}
	int ind = 0;

	while (sym != this->mass[ind]) {
		ind += 1;
	}

	if (ind < this->size) {
		return ind;
	}
	else {
		return -1;
	}
}

bool Set::commut()
{
	if (this->size == 0) {
		std::cout << "commut: Пустое множество" << std::endl;
		return 0;
	}
	for (int i = 0; i < size - 1; ++i) {
		for (int j = i + 1; j < size; ++j) {
			if (plus(mass[i], mass[j]) != plus(mass[j], mass[i])) {
				std::cout << "Некоммутативно по сложению" << std::endl;
				return false;
			}
			if (mult(mass[i], mass[j]) != mult(mass[j], mass[i])) {
				std::cout << "Некоммутативно по умножению" << std::endl;
				return false;
			}
		}
	}
	return true;
}

bool Set::neutralAndReverse()
{
	if (this->size == 0) {
		std::cout << "neutralAndReverse: Пустое множество" << std::endl;
		return 0;
	}
	char eMult = 0;
	char ePlus = 0;

	for (int i = 0; i < size; ++i) {
		int countPlus = 0;
		int countMult = 0;

		for (int j = 0; j < size; ++j) {
			if (massPlus[i][j] == mass[j]) {
				countPlus++;
			}

			if (massMult[i][j] == mass[j]) {
				countMult++;
			}
		}
		if (countPlus == size) {
			ePlus = mass[i];
		}
		if (countMult == size) {
			eMult = mass[i];
		}

	}

	//std::cout << ePlus << eMult << std::endl;
	if (eMult == 0) {
		std::cout << "Нет нейтрального элемента по умножению" << std::endl;
		return false;
	}

	if (ePlus == 0) {
		std::cout << "Нет нейтрального элемента по сложению" << std::endl;
		return false;
	}

	for (int i = 0; i < size; ++i) {

		bool flagPlus = 0;
		bool flagMult = 0;
		for (int j = 0; j < size; ++j) {
			if (plus(mass[i], mass[j]) == ePlus) {
				flagPlus = 1;
			}
			if (mult(mass[i], mass[j]) == eMult || mass[i] == ePlus) {
				flagMult = 1;
			}
		}

		if (flagPlus == false) {
			std::cout << "Нет обратного элемента по сложению для " << mass[i] << std::endl;
			return false;
		}
		if (flagMult == false) {
			std::cout << "Нет обратного элемента по умножению для " << mass[i] << std::endl;
			return false;
		}
	}
	return true;
}

bool Set::assocAnsDistr()
{
	if (this->size == 0) {
		std::cout << "assocAndDistr: Пустое множество" << std::endl;
		return 0;
	}

	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			for (int k = 0; k < size; ++k) {
				if (plus(plus(mass[i], mass[j]), mass[k]) != plus(mass[i], plus(mass[j], mass[k]))) {
					std::cout << "Сложение неассоциативно" << std::endl;
					return false;
				}

				if (mult(mult(mass[i], mass[j]), mass[k]) != mult(mass[i], mult(mass[j], mass[k]))) {
					std::cout << "Умножение неассоциативно" << std::endl;
					return false;
				}

				if (plus(mult(mass[i], mass[j]), mult(mass[i],mass[k])) != mult(mass[i], plus(mass[j], mass[k]))) {
					std::cout << "Недистрибутивно" << std::endl;
					return false;
				}
			}
		}
	}
	return true;
}

bool Set::isElem(char sym)
{
	for (int i = 0; i < size; ++i) {
		if (sym == mass[i]) {
			return true;
		}
	}
	return false;
}

char Set::plus(char a, char b)
{
	if (this->size == 0) {
		std::cout << "plus: Пустое множество" << std::endl;
		return 0;
	}
	int aInd = this->getIndex(a);
	int bInd = this->getIndex(b);

	if (aInd < 0 || bInd < 0) {
		std::cout << "Error" << std::endl;
		return 0;
	}
	return this->massPlus[aInd][bInd];
}

char Set::mult(char a, char b)
{
	if (this->size == 0) {
		std::cout << "mult: Пустое множество" << std::endl;
		return 0;
	}
	int aInd = this->getIndex(a);
	int bInd = this->getIndex(b);

	if (aInd < 0 || bInd < 0) {
		std::cout << "Error" << std::endl;
		return 0;
	}
	return this->massMult[aInd][bInd];
}

bool Set::isField()
{
	if (this->size == 0) {
		return false;
	}
	if (!this->commut() || !this->neutralAndReverse() || !this->assocAnsDistr()) {
		return false;
	}

	return true;
}

Set::~Set()
{
	if (this->size == 0) {
		return;
	}
	for (int i = 0; i < this->size; ++i) {
		delete[] this->massMult[i];
		delete[] this->massPlus[i];
	}
	delete[] this->mass;
	delete[] this->massPlus;
	delete[] this->massMult;
}


