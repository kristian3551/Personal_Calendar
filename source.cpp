#include <iostream>
#include "String.h"
#include "Date.h"

using namespace std;

int main() {
    Date date(22, 4, 2022);
    cout << date.toString();
}