
#include "Set.hpp"

int main() {
    setlocale(LC_ALL, "");

    

    Set set("set2.txt");

    set.showSet();
    
    if (set.isField()) {
        std::cout << "����" << std::endl;
    }
    else {
        std::cout << "�� ����" << std::endl;
    }

	return 0;
}