#include "String.h"
#include <iostream>
using namespace std;

void String::copyFrom(const String& string) {
    this->str = new char[string.length + 1];
    strcpy(this->str, string.str);
    this->length = string.length;
}
void String::free() {
    delete[] this->str;
}

String::String() {
    str = new char[1];
    str[0] = '\0';
    length = 0;
}
String::String(const char* str) {
    int length = strlen(str);
    this->str = new char[length + 1];
    strcpy(this->str, str);
    this->length = length;
}
String::String(int n) {
    char buffer[12];
    itoa(n, buffer, 10);
    this->length = strlen(buffer);
    this->str = new char[this->length + 1];
    strcpy(this->str, buffer);
}
String::String(const String& string) {
    copyFrom(string);
}

String& String::operator =(const String& string) {
    if(this != &string) {
        free();
        copyFrom(string);
    }
    return *this;
}

char String::charAt(int index) const {
    if(index >= length || index < 0)
        return 0;
    return this->str[index]; 
}

int String::compareTo(const String& string) const {
    for(int i = 0; i < length && i < string.length; i++) {
        if(str[i] < string.str[i]) return 1;
        else if(str[i] > string.str[i]) return -1;
    }
    if(length > string.length) return -1;
    if(length < string.length) return 1;
    return 0;
}

String String::concat(const String& string) {
    char* ptr = new char[length + string.length + 1];
    strcpy(ptr, this->str);
    strcpy(ptr + length, string.str);
    String concatenatedString(ptr);
    delete[] ptr;
    return concatenatedString;
}

String String::operator +(const String& string) {
    char* ptr = new char[length + string.length + 1];
    strcpy(ptr, this->str);
    strcpy(ptr + length, string.str);
    String concatenatedString(ptr);
    delete[] ptr;
    return concatenatedString;
}

void String::operator +=(const String& string) {
    char* ptr = new char[length + string.length + 1];
    strcpy(ptr, this->str);
    strcpy(ptr + length, string.str);
    free();
    this->str = ptr;
    this->length = length + string.length;
}

ostream& operator <<(ostream& file, const String& string) {
    file << string.str;
    return file;
}

bool String::startsWith(const String& string) const {
    for(int i = 0; i < string.length; i++) {
        if(str[i] != string.str[i]) return false;
    }
    return true;
}

bool isPrefix(const char* where, const char* what) {
    int whereLength = strlen(where);
    int whatLength = strlen(what);
    for(int i = 0; i < whatLength; i++) {
        if(where[i] != what[i]) return false;
    }
    return true;
}

bool String::contains(const String& string) const {
    for(int i = 0; i < length - string.length + 1; i++) {
        if(isPrefix(str + i, string.str)) return true;
    }
    return false;
}

bool String::equals(const String& string) const {
    return this->compareTo(string) == 0;
}

int String::indexOf(const String& string) const {
    for(int i = 0; i < length - string.length + 1; i++) {
        if(isPrefix(str + i, string.str)) return i;
    }
    return -1;
}

bool String::isEmpty() const {
    return length == 0;
}

bool isLowerCase(char c) {
    return c >= 'a' && c <= 'z';
}

bool isUpperCase(char c) {
    return c >= 'A' && c <= 'Z';
}

String String::toUpperCase() const {
    String string = *this;
    for(int i = 0; i < string.length; i++) {
        if(isLowerCase(string.str[i])) {
            string.str[i] = 'A' + string.str[i] - 'a';
        }
    }
    return string;
}

String String::toLowerCase() const {
    String string = *this;
    for(int i = 0; i < string.length; i++) {
        if(isUpperCase(string.str[i])) {
            string.str[i] = 'a' + string.str[i] - 'A';
        }
    }
    return string;
}

const char* String::toString() const {
    return str;
}

String String::trim() const {
    int index = 0;
    for(int i = length - 1; i >= 0; i--) {
        if(str[i] != ' ') {
            index = i + 1;
            break;
        }
    }
    char* ptr = new char[index + 1];
    strncpy(ptr, str, index);
    ptr[index] = '\0';
    String res(ptr);
    delete[] ptr;
    return res;
}

int String::getLength() const {
    return length;
}

String::~String() {
    free();
}