#include <iostream>

#include "QTView.h"

int main(int argc, char *argv[]) {
    std::cout << "Hello, World!" << std::endl;
    QApplication a(argc, argv);
    Collections collection;
    QTView w(&collection);



    return a.exec();
}
