/////////////////////////////////////////////////////////////
//
// Author: Антони Калоферов
// FN: 81394
// Date: 8.02.2018
//

#include <string>
#include <vector>

#include "html_iterator.h"

using namespace std;

// Да се напише функция
// std::vector<std::string> collect (HTMLIterator it, std::vector<std::string> tags);
// която връща списък от всички низове в HTML документа, обхождан от итератора it,
// които са непосредствено вложени в последователност от тагове, описана чрез tags.
// Функцията трябва също да проверява дали таговете в HTML документа, прочетен от потока,
// са правилно вложени, и ако това не е вярно, да връща списък от единствен низ "ERROR".

void collectRec(vector<string>& v, HTMLIterator& it, vector<string> tags, int i) {
	if (!it) {
		return;
	}

	if (i == tags.size()) {
		if ((*it).type == 't') {
			v.push_back((*it).data);
		}
	}

	if ((*it).type == 'c' && (*it).data == tags[i-1 < 0 ? 0 : i-1]) {
        return;
	}

	if ((*it).type == 'o' && (*it).data == tags[i]) {
		collectRec(v, it, tags, i + 1);
	}
	++it;
	collectRec(v, it, tags, i);
}

std::vector<std::string> collect(HTMLIterator it, std::vector<std::string> tags) {
	vector<string> v;
	collectRec(v, it, tags, 0);
	return v;
}

//-------------------------------------------------------------------------
//
// ВАЖНО: Преди предаване на решението, моля премахнете коментара от дадения по-долу ред,
//        за да активирате автоматичните тестове за решението си.
//
//-------------------------------------------------------------------------
#include "prob2-tests.h"

#include "UnitTestFramework.h"

int main() {

  //-------------------------------------------------------------------------
  //
  // ВАЖНО: При предаване на работата във тялото на функцията main не трябва да се
  //        изпълнява нищо друго освен функцията RunTests().
  //
  //-------------------------------------------------------------------------
  RunTests();

  system("pause");
  return 0;
}
