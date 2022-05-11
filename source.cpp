#include <iostream>
#include "Engine/Engine.h"
using namespace std;

// if ($?) { g++ (Get-ChildItem -Recurse *.cpp) -o source } ; if ($?) { .\source }

int main() {
    // doctest::Context c;
    // c.run();
    Engine engine;
    engine.run();
}