
#include "Set.hpp"

int main() {
    setlocale(LC_ALL, "");

    

    Set set("set2.txt");

    set.showSet();
    
    if (set.isField()) {
        std::cout << "Поле" << std::endl;
    }
    else {
        std::cout << "Не поле" << std::endl;
    }

	return 0;
}