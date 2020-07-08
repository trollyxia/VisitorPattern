#include <memory>
#include <iostream>

class BatchOp;
class ShuffleOp;
class DatasetOp;

class Pass {
public:
  virtual int visit(std::shared_ptr<DatasetOp> c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual int visit(std::shared_ptr<BatchOp> c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual int visit(std::shared_ptr<ShuffleOp> c) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  virtual ~Pass()= default;
};

class RemovePass : public Pass{
public:
  int visit (std::shared_ptr<BatchOp> c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  int visit (std::shared_ptr<ShuffleOp> c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

class PrintPass : public Pass{
public:
  int visit(std::shared_ptr<ShuffleOp> c) override { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};


/*****************************************************************************/

class DatasetOp : public std::enable_shared_from_this<DatasetOp> {
public:
  virtual ~DatasetOp()= default;
  virtual int accept(Pass *v) { return v->visit(shared_from_this()); }
};

/** example of use */
class BatchOp : public DatasetOp {
  /* Visitable accept one BaseVisitor */
public:
  int accept(Pass *v) { return v->visit(std::static_pointer_cast<BatchOp>(shared_from_this())); }
};

class ShuffleOp : public DatasetOp {
  /* Visitable accept one BaseVisitor */
public:
  int accept(Pass *v) { return v->visit(std::static_pointer_cast<ShuffleOp>(shared_from_this())); }
};

int main(int argc, char **argv) {
  RemovePass remove_pass;
  PrintPass print_pass;
  std::shared_ptr<BatchOp> batch_op = std::make_shared<BatchOp>();
  std::shared_ptr<ShuffleOp> shuffle_op = std::make_shared<ShuffleOp>();

  std::shared_ptr<DatasetOp> op = batch_op;
  op->accept(&remove_pass);
  op->accept(&print_pass);
  op = shuffle_op;
  op->accept(&remove_pass);
  op->accept(&print_pass);
}