#ifndef STRING_HEADER
#define STRING_HEADER
#include <fstream>
#include <cstring>

class String {
    char* str;
    int length;
    void copyFrom(const String&);
    void free();
public:
    String(); //
    String(const char*); //
    String(const String&);
    String(int);
    String& operator =(const String&); //
    char charAt(int) const; //
    int compareTo(const String&) const; //
    String concat(const String&); //
    String operator +(const String&); //
    void operator +=(const String&); //
    friend std::ostream& operator <<(std::ostream&, const String&); //
    bool contains(const String&) const; //
    bool equals(const String&) const; //
    int indexOf(const String&) const; //
    bool isEmpty() const; //
    int getLength() const; //
    bool startsWith(const String&) const; //
    String toUpperCase() const; //
    String toLowerCase() const; //
    String trim() const; //
    const char* toString() const; //
    ~String();
};

#endif