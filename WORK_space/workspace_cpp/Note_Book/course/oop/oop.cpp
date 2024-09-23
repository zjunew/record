#include <iostream>
using namespace std;

class A
{
public:
  A(int i) : mi(i) {}
  A(const A& rhs) : mi(rhs.mi)
  {
    cout << "A::A(&)" << endl;
  }
  A& operator=(const A&rhs)
  {
    mi = rhs.mi;
    cout << "A::operator=()" << endl;
    return *this;
  }
  virtual void f()
  {
    cout << "A::f(), " << mi << endl;
  }
protected:
  int mi;
};

class B : public A
{
public:
  B(int i, int j) : A(i), mj(j) {}
  void f() override
  {
    cout << "B::f(), " << mi << ", " << mj << endl;
  }
private:
  int mj;
};

int main()
{
  A a1(1);
  B b(3,4);

  A& ra = b;
  ra.f();//B::f(), 3, 4
  ra = a1;//A::operator=()
  ra.f();//B::f(), 1, 4

  A a2 = b;//A::A(&)
  a2.f();//A::f(), 1
}