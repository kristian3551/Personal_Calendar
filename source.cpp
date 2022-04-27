#include <iostream>
#include "Controller/Controller.h"
using namespace std;

// cd "f:\FMI resources\Summer semester\Object-oriented programming\Private-calendar\" ;
// if ($?) { g++ (Get-ChildItem -Recurse *.cpp) -o source } ; if ($?) { .\source }

int main() {
    Controller controller;
    controller.run();
}