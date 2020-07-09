# Visitor Pattern
A simple example to try/learn the Visitor Pattern in C++



#### Some notes:

1. The original visitor pattern code written in c++: [visitor.cpp](./visitor.cpp). Running it you would get:

   ```
   virtual int Visitor1::visit(Visitable1&)
   virtual int BaseVisitor::visit(Visitable1&)
   virtual int Visitor1::visit(Visitable2&)
   virtual int Visitor2::visit(Visitable2&)
   ```
   
   Perfect!
   
2. Now try to modify it to use smart pointer: [wrong_shared_ptr_visitor.cpp](./wrong_shared_ptr_visitor.cpp). However, running it you would only get:

   ```
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   ```

   Because only `BaseVisitable` inherits `std::enable_shared_from_this<BaseVisitable>`, calling `shared_from_this()` from inside class `Visitable1` and `Visitable2` would return `shared_ptr<BaseVisitable>`. Need to downcast to get `shared_ptr<Visitable1>` or `shared_ptr<Visitable2>`.


3. Therefore, the correct implementation for visitor pattern using smart pointer should be like this one: [shared_ptr_visitor.cpp](./shared_ptr_visitor.cpp). Running it you would get:
   
   ```
   virtual int Visitor1::visit(std::shared_ptr<Visitable1>)
   virtual int BaseVisitor::visit(std::shared_ptr<Visitable1>)
   virtual int Visitor1::visit(std::shared_ptr<Visitable2>)
   virtual int Visitor2::visit(std::shared_ptr<Visitable2>)
   ```

4. Here is an example of using the visitor pattern we've got so far in a real program: [example_usage_visitor.cpp](./example_usage_visitor.cpp). Running it you would get:

   ```
   virtual int RemovePass::visit(std::shared_ptr<BatchOp>)
   virtual int Pass::visit(std::shared_ptr<BatchOp>)
   virtual int RemovePass::visit(std::shared_ptr<ShuffleOp>)
   virtual int PrintPass::visit(std::shared_ptr<ShuffleOp>)
   ```

   Deep learning framework might need to deal with various operators such as `BatchOp` and `ShuffleOp` here. We can use this visitor pattern to create different node/tree passes (`PrintPass` and `RemovePass` here), each pass dealing with certain operators and perform certain action towards these operators.
   
5. Now, there is a lot of duplicate code. How to clean the code a bit? To clean the `Visitor`, we may use CRTP pattern and the code becomes this: [wrong_visitor_clean.cpp](./wrong_visitor_clean.cpp). Running it you would get:

   ```
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   virtual int BaseVisitor::visit(std::shared_ptr<BaseVisitable>)
   ```

   The problem is that in `accept(BaseVisitor *v)`, the parameter `v` cannot atomically cast from class `BaseVisitor` to class `Visitor<Visitable1>` or `Visitor<Visitable2>`.

6. Therefore, the correct cleaned visitor implementation would be like this: [visitor_clean.cpp](./visitor_clean.cpp). Running it you would get:

   ```
   virtual int Visitor1::visit(std::shared_ptr<Visitable1>)
   virtual int Visitor1::visit(std::shared_ptr<Visitable2>)
   virtual int Visitor2::visit(std::shared_ptr<Visitable2>)
   ```

7. There are still a lot of duplicate code for `Visitable`. 

