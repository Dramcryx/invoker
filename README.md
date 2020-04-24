# invoker
## Keep calling till stack do you apart
Syntax sugar for your code (`C++ >= 11`)

Many void setters?
```cpp
A a;
auto l = [](A & a){ a.y(); };
a.z();
a.x();
l(a);
```
Or you just want to make a pipeline? Use invoker:
```cpp
auto res = invoker<A>{a}(&A::z)(&A::x)(l)
                        ([](A & a){return a.y();})
                        (&A::y)(&A::z)(l)
                        ([](A & a){return std::vector<A>{10, a};})
```
You can stop at any time and get last result value if function is not void by casting to type
```cpp
int result = invoker<A>{a}([](A & a) -> int { return a.y(); });
```
or by calling `.ret`
```cpp
auto result = invoker<A>{a}([](A & a) -> int { return a.y(); }).ret;
```
