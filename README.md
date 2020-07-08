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
   


3. 

