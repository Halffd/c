#include <iostream>
using namespace std;

class A { public: virtual void foo() { cout << "A" << endl; } };
class B : virtual public A { public: void foo() override { cout << "B" << endl; } };
class C : virtual public A { public: void foo() override { cout << "C" << endl; } };

class D : public B, public C {
public:
    void foo() override { cout << "D" << endl; } // Resolves ambiguity
};

int main() {
    D d;
    d.foo(); // Output: D (without overriding, compile error due to ambiguity)
    return 0;
}