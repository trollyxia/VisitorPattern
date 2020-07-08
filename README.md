# VisitorPattern
A simple example to try/learn the Visitor Pattern in C++



#### Running results:

1. visitor.cpp:

   ```
   virtual int Visitor1::visit(Visitable1&)
   virtual int BaseVisitor::visit(Visitable1&)
   virtual int Visitor1::visit(Visitable2&)
   virtual int Visitor2::visit(Visitable2&)
   ```

2. shared_ptr_visitor.cpp:
   
   ```
   virtual int Visitor1::visit(std::shared_ptr<Visitable1>)
   virtual int BaseVisitor::visit(std::shared_ptr<Visitable1>)
   virtual int Visitor1::visit(std::shared_ptr<Visitable2>)
   virtual int Visitor2::visit(std::shared_ptr<Visitable2>)
   ```
   


3. wrong_shared_ptr_visitor.cpp:

   ```
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   ```

   Because only `BaseVisitable` inherits `std::enable_shared_from_this<BaseVisitable>`, calling `shared_from_this()` from inside class `Visitable1` and `Visitable2` would return `shared_ptr<BaseVisitable>`. Need to downcast to get `shared_ptr<Visitable1>` or `shared_ptr<Visitable2>`.

4. 