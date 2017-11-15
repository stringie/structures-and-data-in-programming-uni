//
// Created by string on 11/13/17.
//

#ifndef PROBLEM6_EDITOR_H
#define PROBLEM6_EDITOR_H

#include <iostream>
#include <stack>

using namespace std;

class Editor {
private:
    stack<string> history;
    stack<string> future;
public:
    Editor(string str);
    string getCurrent() const ;
    Editor* remove(int start, int positions);
    Editor* insert(int pos, string s);
    Editor* undo();
    Editor* redo();
};


#endif //PROBLEM6_EDITOR_H
