//
// Created by string on 11/13/17.
//

#include "Editor.h"

Editor::Editor(string str) { history.push(str);}

Editor* Editor::insert(int pos, string s) {
    string oldS = getCurrent();
    string newS = oldS.insert(pos, s);
    history.push(newS);
    future = stack<string>();
    return this;
}

Editor* Editor::remove(int start, int positions) {
    string oldS = getCurrent();
    string newS = oldS.erase(start, positions);
    history.push(newS);
    future = stack<string>();
    return this;
}

Editor* Editor::redo() {
    string nextS = future.top();
    history.push(nextS);
    future.pop();
    return this;
}

Editor* Editor::undo() {
    string current = getCurrent();
    history.pop();
    future.push(current);
    return this;
}

string Editor::getCurrent() const {
    return history.top();
}
