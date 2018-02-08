#include "UnitTestFramework.h"

#include <string>
#include <sstream>

std::string html0 = "";
std::string html1 = "   <x>\ny\n</x>  ";
std::string html2 = "\t  \n<a>\tA<b>B\tB</b>C</a>\t\n\t";
std::string html3 = R"(<html>
  <head>
    <title>SDP EXAM</title>
  </head>
  <body>
    <h1>Variant 1</h1>
    <h2>zada4a 1</h2>
    text ofzada4a 1.
    <h1>Variant 2</h1>
    TODO
  </body>
</html>)";
std::string html4 = "<x><y></y><z></x>";
std::string html5 = "<x>y</x></y>";
std::string html6 = "<x><y>z</y>";

TEST_CASE("HTMLIterator", HTMLIteratorEmptyDoc) {
  std::stringstream str(html0);
  HTMLIterator it(str);
  Assert::IsFalse(it);
}

bool operator==(Token const& t1, Token const& t2) {
  return t1.type == t2.type && t1.data == t2.data;
}

std::ostream& operator<<(std::ostream& os, Token const& t) {
  return os << '{' << t.type << ',' << t.data << '}';
}

TEST_CASE("HTMLIterator", HTMLIteratorSingleTag) {
  std::stringstream str(html1);
  HTMLIterator it(str);
  Assert::IsTrue(it);
  Assert::AreEqual(*it,   Token{'o', "x"});
  Assert::AreEqual(*++it, Token{'t', "y"});
  Assert::AreEqual(*++it, Token{'c', "x"});
  Assert::IsFalse(++it);
  return;
}

TEST_CASE("HTMLIterator", HTMLIteratorSimpleHTML) {
  std::stringstream str(html2);
  HTMLIterator it(str);
  Assert::IsTrue(it);
  Assert::AreEqual(*it,   Token{'o',"a"});
  Assert::AreEqual(*++it, Token{'t',"A"});
  Assert::AreEqual(*++it, Token{'o',"b"});
  Assert::AreEqual(*++it, Token{'t',"B\tB"});
  Assert::AreEqual(*++it, Token{'c',"b"});
  Assert::AreEqual(*++it, Token{'t',"C"});
  Assert::AreEqual(*++it, Token{'c',"a"});
  Assert::IsFalse(++it);
}

TEST_CASE("HTMLIterator", HTMLIteratorExampleHTML) {
  std::stringstream str(html3);
  HTMLIterator it(str);
  Assert::IsTrue(it);
  Assert::AreEqual(*it,   Token{'o',"html"});
  Assert::AreEqual(*++it, Token{'o',"head"});
  Assert::AreEqual(*++it, Token{'o',"title"});
  Assert::AreEqual(*++it, Token{'t',"SDP EXAM"});
  Assert::AreEqual(*++it, Token{'c',"title"});
  Assert::AreEqual(*++it, Token{'c',"head"});
  Assert::AreEqual(*++it, Token{'o',"body"});
  Assert::AreEqual(*++it, Token{'o',"h1"});
  Assert::AreEqual(*++it, Token{'t',"Variant 1"});
  Assert::AreEqual(*++it, Token{'c',"h1"});
  Assert::AreEqual(*++it, Token{'o',"h2"});
  Assert::AreEqual(*++it, Token{'t',"zada4a 1"});
  Assert::AreEqual(*++it, Token{'c',"h2"});
  Assert::AreEqual(*++it, Token{'t',"text ofzada4a 1."});
  Assert::AreEqual(*++it, Token{'o',"h1"});
  Assert::AreEqual(*++it, Token{'t',"Variant 2"});
  Assert::AreEqual(*++it, Token{'c',"h1"});
  Assert::AreEqual(*++it, Token{'t',"TODO"});
  Assert::AreEqual(*++it, Token{'c',"body"});
  Assert::AreEqual(*++it, Token{'c',"html"});
  Assert::IsFalse(++it);
}

TEST_CASE("HTMLIterator", HTMLIteratorUnbalancedHTML1) {
  std::stringstream str(html4);
  HTMLIterator it(str);
  Assert::IsTrue(it);
  Assert::AreEqual(*it,   Token{'o',"x"});
  Assert::AreEqual(*++it, Token{'o',"y"});
  Assert::AreEqual(*++it, Token{'c',"y"});
  Assert::AreEqual(*++it, Token{'o',"z"});
  Assert::AreEqual(*++it, Token{'c',"x"});
  Assert::IsFalse(++it);
}

TEST_CASE("HTMLIterator", HTMLIteratorUnbalancedHTML2) {
  std::stringstream str(html5);
  HTMLIterator it(str);
  Assert::AreEqual(*it,   Token{'o',"x"});
  Assert::AreEqual(*++it, Token{'t',"y"});
  Assert::AreEqual(*++it, Token{'c',"x"});
  Assert::AreEqual(*++it, Token{'c',"y"});
  Assert::IsFalse(++it);
}

TEST_CASE("HTMLIterator", HTMLIteratorUnbalancedHTML3) {
  std::stringstream str(html6);
  HTMLIterator it(str);
  Assert::AreEqual(*it,   Token{'o',"x"});
  Assert::AreEqual(*++it, Token{'o',"y"});
  Assert::AreEqual(*++it, Token{'t',"z"});
  Assert::AreEqual(*++it, Token{'c',"y"});
  Assert::IsFalse(++it);
}

TEST_CASE("Problem2", Problem2_CollectEmptyDoc) {
  std::stringstream str(html0);
  Assert::IsTrue(collect(HTMLIterator(str), {"html", "body"}).empty());
}

TEST_CASE("Problem2", Problem2_CollectOneTag) {
  std::stringstream str(html1);
  std::vector<std::string> r = collect(HTMLIterator(str), {"x"});
  Assert::AreEqual(r.size(), 1);
  Assert::AreEqual(r[0], "y");
}

TEST_CASE("Problem2", Problem2_CollectTwoTags) {
  std::stringstream str(html2);
  std::vector<std::string> r = collect(HTMLIterator(str), {"a", "b"});
  Assert::AreEqual(r.size(), 1);
  Assert::AreEqual(r[0], "B\tB");
}

TEST_CASE("Problem2", Problem2_CollectExample1) {
  std::stringstream str(html3);
  std::vector<std::string> r = collect(HTMLIterator(str), {"body", "h1"});
  Assert::AreEqual(r.size(), 2);
  Assert::AreEqual(r[0], "Variant 1");
  Assert::AreEqual(r[1], "Variant 2");
}

TEST_CASE("Problem2", Problem2_CollectExample2) {
  std::stringstream str(html3);
  std::vector<std::string> r = collect(HTMLIterator(str), {"html", "body"});
  Assert::AreEqual(r.size(), 2);
  Assert::AreEqual(r[0], "text ofzada4a 1.");
  Assert::AreEqual(r[1], "TODO");
}

TEST_CASE("Problem2", Problem2_CollectExample3) {
  std::stringstream str(html3);
  Assert::IsTrue(collect(HTMLIterator(str), {"html", "head"}).empty());
}

TEST_CASE("Problem2", Problem2_CollectExampleInvalidTags) {
  std::stringstream str(html3);
  Assert::IsTrue(collect(HTMLIterator(str), {"html", "title"}).empty());
}

TEST_CASE("Problem2", Problem2_CollectExampleInvalidTags2) {
  std::stringstream str(html3);
  Assert::IsTrue(collect(HTMLIterator(str), {"h1", "h2"}).empty());
}

TEST_CASE("Problem2", Problem2_CollectUnbalancedHTML1) {
  std::stringstream str(html4);
  std::vector<std::string> r = collect(HTMLIterator(str), {"h1", "h2"});
  Assert::AreEqual(r.size(), 1);
  Assert::AreEqual(r[0], "ERROR");
}

TEST_CASE("Problem2", Problem2_CollectUnbalancedHTML2) {
  std::stringstream str(html5);
  std::vector<std::string> r = collect(HTMLIterator(str), {"h1", "h2"});
  Assert::AreEqual(r.size(), 1);
  Assert::AreEqual(r[0], "ERROR");
}

TEST_CASE("Problem2", Problem2_CollectUnbalancedHTML3) {
  std::stringstream str(html6);
  std::vector<std::string> r = collect(HTMLIterator(str), {"h1", "h2"});
  Assert::AreEqual(r.size(), 1);
  Assert::AreEqual(r[0], "ERROR");
}
