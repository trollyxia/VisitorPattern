#include <iostream>
#include <memory>

class Visitable1;
class Visitable2;
class BaseVisitable;

class BaseVisitor {
public:
  virtual int visit(std::shared_ptr<BaseVisitable> c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual ~BaseVisitor()= default;
};

template<class T> class Visitor{
public:
  virtual int visit(std::shared_ptr<T> c){ std::cout << __PRETTY_FUNCTION__ << std::endl;}
};

class Visitor1 : public BaseVisitor, public Visitor<Visitable1>, public Visitor<Visitable2>{
public:
  int visit(std::shared_ptr<Visitable1> c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  int visit(std::shared_ptr<Visitable2> c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

class Visitor2 : public BaseVisitor, public Visitor<Visitable2>{
public:
  int visit(std::shared_ptr<Visitable2> c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

/*************************************************************************/

class BaseVisitable : public std::enable_shared_from_this<BaseVisitable> {
public:
  virtual ~BaseVisitable()= default;
  virtual int accept(BaseVisitor *v) { return 0; }

  template <typename Derived>
  inline std::shared_ptr<Derived> shared_from(Derived* that){
    return std::static_pointer_cast<Derived>(that->shared_from_this());
  }

  template<class T>
  int acceptHelper(std::shared_ptr<T> n, BaseVisitor* v){
    if(Visitor<T> *p = dynamic_cast<Visitor<T> *>(v))
      return p->visit(n);
  }

#define ACCEPT() int accept(BaseVisitor *v) { return acceptHelper(shared_from(this), v);}
};

class Visitable1 : public BaseVisitable {
  /* Visitable accept one BaseVisitor */
public:
  ACCEPT();
};

class Visitable2 : public BaseVisitable {
  /* Visitable accept one BaseVisitor */
public:
  ACCEPT();
};

int main(int argc, char **argv) {
  Visitor1 visitor1;
  Visitor2 visitor2;
  std::shared_ptr<Visitable1> visitable1 = std::make_shared<Visitable1>();
  std::shared_ptr<Visitable2> visitable2 = std::make_shared<Visitable2>();

  std::shared_ptr<BaseVisitable> visitable = visitable1;
  visitable->accept(&visitor1);
  visitable->accept(&visitor2);
  visitable = visitable2;
  visitable->accept(&visitor1);
  visitable->accept(&visitor2);

}