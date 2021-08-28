#include <iostream>

#include "QTView.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Collections collection;
    QTView w(&collection);
    return a.exec();
}
