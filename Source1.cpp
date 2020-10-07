#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

class String
{
    void resize(size_t);

public:
    String();
    String(const char);
    String(const char*);
    String(const String&);
    ~String();

    friend istream& operator>>(istream&, String&);
    friend ostream& operator<<(ostream&, const String&);

    size_t length() const;
    size_t capacity() const;

    void clear();
    void to_upper();
    int find_first_of(char) const;

    friend const String operator+(const String&, const String&);
    const String& operator+=(const String&);

    const String& operator=(const String&);

    friend bool operator==(const String&, const String&);
    friend bool operator!=(const String&, const String&);

    const char& operator[](size_t) const;
    char& operator[](size_t);

private:
    char* _string;
    size_t _length;
    size_t _capacity;
};

String::String() :
    _string(0),
    _length(0),
    _capacity(0)
{
}

String::String(const char symbol) :
    _length(2),
    _capacity(2)
{
    _string = new char[_capacity];

    _string[0] = symbol;
    _string[1] = '\0';
}

String::String(const char* string) :
    _length(strlen(string)),
    _capacity(1)
{
    while (_capacity < _length)
        _capacity *= 2;

    _string = new char[++_capacity];

    strcpy(_string, string);
}

String::String(const String& original) :
    _length(original._length),
    _capacity(original._capacity)
{
    _string = new char[_capacity];

    strcpy(_string, original._string);
}

String::~String()
{
    delete[] _string;
}

void String::resize(size_t new_length)
{
    _capacity = 1;

    while (_capacity < new_length)
        _capacity *= 2;

    char* new_string = new char[++_capacity];

    if (_string != 0)
    {
        size_t count = new_length < _length ? new_length : _length;

        for (size_t i = 0; i < count; ++i)
            new_string[i] = _string[i];

        new_string[count] = '\0';

        delete[] _string;
    }

    _string = new_string;
    _length = new_length;
}

istream& operator>>(istream& input, String& rhs)
{
    size_t max_len = 1;
    size_t current_len = 0;
    char* buf = new char[max_len];

    do
    {
        if (current_len > max_len - 1)
        {
            char* temp = new char[max_len];

            for (size_t i = 0; i < max_len; ++i)
                temp[i] = buf[i];

            max_len *= 2;

            delete[] buf;

            buf = new char[max_len + 1];

            for (size_t i = 0; i < max_len / 2; ++i)
                buf[i] = temp[i];

            delete[] temp;
        }

        buf[current_len] = input.get();
    } while (buf[current_len++] != '\n');

    buf[current_len - 1] = '\0';
    rhs = String(buf);

    delete[] buf;

    return input;
}

ostream& operator<<(ostream& output, const String& rhs)
{
    if (rhs._string != 0)
        output << rhs._string;

    return output;
}

size_t String::length() const
{
    return _length;
}

size_t String::capacity() const
{
    return _capacity;
}

void String::clear()
{
    delete[] _string;

    _string = 0;
    _length = 0;
    _capacity = 0;
}

void String::to_upper()
{
    for (size_t i = 0; i < _length; ++i)
        _string[i] = toupper(_string[i]);
}

int String::find_first_of(char symbol) const
{
    for (size_t i = 0; i < _length; ++i)
        if (_string[i] == symbol)
            return static_cast<int>(i);

    return -1;
}

const String operator+(const String& lhs, const String& rhs)
{
    String result(lhs);

    result.resize(lhs._length + rhs._length);
    strcat(result._string, rhs._string);

    return result;
}

const String& String::operator+=(const String& rhs)
{
    *this = *this + rhs;

    return *this;
}

const String& String::operator=(const String& rhs)
{
    if (&rhs != this)
    {
        _length = rhs._length;
        _capacity = rhs._capacity;

        delete[] _string;

        _string = new char[_capacity];

        strcpy(_string, rhs._string);
    }

    return *this;
}

bool operator==(const String& lhs, const String& rhs)
{
    if (lhs._length != rhs._length)
        return false;

    for (size_t i = 0; i < lhs._length; ++i)
        if (lhs._string[i] != rhs._string[i])
            return false;

    return true;
}

bool operator!=(const String& lhs, const String& rhs)
{
    return !(lhs == rhs);
}

const char& String::operator[](size_t index) const
{
    return _string[index];
}

char& String::operator[](size_t index)
{
    return _string[index];
}



int main()
{
    String s1, s2("abc"), s3(s2);

    cout << s1 << s2 << s3 << endl;
    cin >> s1;
    cout << s1 << endl;
    cout << s1.length() << "   " << s1.capacity() << endl;

    s1.to_upper();

    cout << s1 << endl;
    cout << s1.find_first_of('A') << endl;

    s1.clear();

    cout << s1 << endl;

    s1 = s2 + s3;
    s1 += 'a';
    s1 += "bc";
    s1 += s1;

    cout << s1 << endl;

    s1 = "abc" + s2;
    s1 = s1 + "def";
    s1 = s1 + 'c';
    s1 = 'd' + s1;

    cout << s1 << endl;

    cout << (s2 == s3) << endl;
    cout << (s2 == "abc") << endl;
    cout << ("def" == s3) << endl;
    cout << (s2 == 'a') << endl;
    cout << ('a' == s3) << endl;

    cout << s2[1] << endl;

    return 0;
}