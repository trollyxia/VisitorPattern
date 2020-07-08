#include <iostream>
#include <memory>

class Visitable1;
class Visitable2;
class BaseVisitable;

class BaseVisitor {
public:
  virtual int visit(BaseVisitable &c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual int visit(Visitable1 &c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual int visit(Visitable2 &c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual ~BaseVisitor()= default;
};

class Visitor1 : public BaseVisitor{
public:
  int visit(Visitable1 &c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  int visit(Visitable2 &c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

class Visitor2 : public BaseVisitor{
public:
  int visit(Visitable2 &c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

/*************************************************************************/

class BaseVisitable {
public:
  virtual ~BaseVisitable()= default;
  virtual int accept(BaseVisitor *v) { return v->visit(*this); }
};

class Visitable1 : public BaseVisitable {
  /* Visitable accept one BaseVisitor */
public:
  int accept(BaseVisitor *v) { return v->visit(*this); }
};

class Visitable2 : public BaseVisitable {
  /* Visitable accept one BaseVisitor */
public:
  int accept(BaseVisitor *v) { return v->visit(*this); }
};

int main(int argc, char **argv) {
  Visitor1 visitor1;
  Visitor2 visitor2;
  Visitable1 visitable1;
  Visitable2 visitable2;

  BaseVisitable *visitable = &visitable1;
  visitable->accept(&visitor1);
  visitable->accept(&visitor2);
  visitable = &visitable2;
  visitable->accept(&visitor1);
  visitable->accept(&visitor2);

}