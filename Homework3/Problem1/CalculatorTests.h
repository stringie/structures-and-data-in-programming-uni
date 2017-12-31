#pragma once

#include "UnitTestFramework.h"
#include "Calculator.h"

TEST_CASE("Calculator", Calculator_ClassOperatorsWorkCorrectly){
    Calculator c;
    ((((c+2)*10)-5)/3);
    Assert::AreEqual(c.getValue(), 5);
}

TEST_CASE("Calculator", Calculator_ListOperationsReturnsCorrectList){
    Calculator c;
    ((((c+2)*10)-5)/3);
    Assert::AreEqual(c.listOperations(), "+2*10-5/3");
}

TEST_CASE("Calculator", Calculator_UndoWorksCorrectly){
    Calculator c;
    ((((c+2)*10)-5)/3).undo().undo()+10;
    Assert::AreEqual(c.getValue(), 30);
}

TEST_CASE("Calculator", Calculator_ResetWorksCorrectly){
    Calculator c;
    ((((c+2)*10)-5)/3).reset();
    Assert::AreEqual(c.getValue(), 0);
}

TEST_CASE("Calculator", Calculator_SaveAndRestoreWorkCorrectly){
    Calculator c;
    ((((c+2)*10)-5)/3);
    c.save("test.txt");
    c.reset();
    c.restore("test.txt");
    Assert::AreEqual(c.getValue(), 5);
}