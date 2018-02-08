#ifndef _HTML_ITERATOR_H
#define _HTML_ITERATOR_H

#include <string>
#include <iostream>
#include <cassert>
#include <algorithm>

bool _isspace(char c) {
  return c == ' ' || c == '\t' || c == '\n' || c == '\r';
}

struct Token {

  // типът на токена, и може да е един от следните символи:
  // 'o' за отварящ таг
  // 'c' за затварящ таг
  // 't' за низ
  char type;

  // съдържанието на токена, което може да е:
  // името на отварящия или затварящия таг (без знаците ‘<’, ‘>’ и ‘/’)
  // съдържанието на текста
  std::string data;
};

const char TOKEN_OPEN   = 'o';
const char TOKEN_CLOSE  = 'c';
const char TOKEN_STRING = 't';
const char TOKEN_NONE   = '*';

const char TAG_START = '<';
const char TAG_END   = '>';
const char TAG_CLOSE = '/';

class HTMLIterator
{
public:

  // инициализира итератор с входен поток, съдържащ HTML документ
  HTMLIterator (std::istream &_in) : in (_in) {

    // инициализиране на итератора чрез прочитане на първия токен (ако такъв има)
    ++(*this);

  }

  // премества оператора на следващия токен
  HTMLIterator& operator ++ () {

    // игнориране на интервали, табулации, нови редове
    eatwhite ();

    // при край на потока маркираме токена като невалиден
    if (!in) {
      lastToken.type = TOKEN_NONE;
      return *this;
    }

    // допускаме, че четем низ
    // четем до началото на следващия таг
    char delimiter = TAG_START;
    lastToken.type = TOKEN_STRING;

    // ако следващият символ е начало на таг
    if (in.peek() == TAG_START) {
      in.get ();

      // ще четем до края на тага
      delimiter = TAG_END;
      // допускаме, че е отварящ таг
      lastToken.type = TOKEN_OPEN;

      if (in.peek () == TAG_CLOSE) {
        // оказва се, че тагът е затварящ
        in.get ();
        lastToken.type = TOKEN_CLOSE;
      }
    }

    // прочитане на съдържанието на токена до съответния разделител
    std::getline (in, lastToken.data, delimiter);

    // изрязване на интервалите отляво и отдясно
    ltrim(rtrim(lastToken.data));

    // std::getline премахва разделителя от потока,
    // което не е желано, ако разделителят е начало на следващ таг
    if (delimiter == TAG_START) {
      // връщаме обратно символа за отваряне на таг в потока
      in.putback (delimiter);
    }

    return *this;
  }

  // проверява дали итераторът сочи към валиден токен
  // и дали всичко е наред с входния поток
  operator bool () {
    return in.good() && lastToken.type != TOKEN_NONE;
  }

  // връща текущия токен, към който сочи итераторът
  Token operator * () {
    assert (lastToken.type != TOKEN_NONE); // проверка, че токенът е валиден
    return lastToken;
  }

private:

  std::istream &in; // входният поток
  Token lastToken;  // текущият токен

  // консумиране на интервали, табулации, символи за нов ред
  void eatwhite () {
    while (in && _isspace (in.peek())) {
      in.get();
    }
  }

  // премахване на интервалите отляво и отдясно на низ
  // https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
  
  // trim from start (in place)
  std::string& ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
          return !_isspace(ch);
        }));
    return s;
  }

  // trim from end (in place)
  std::string& rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
          return !_isspace(ch);
        }).base(), s.end());
    return s;
  }
};

#endif
