#include <functional>
#include <iostream>

struct A
{
    virtual ~A() = default;
    virtual void pook()
    {
        std::cout << "A: pook" << std::endl;
    }

    int m_A;

    void SetAPrtyVirtual11(int a)
    {
        m_A = a;
    }

    static decltype(std::mem_fn(&A::SetAPrtyVirtual11)) SetAPrtyVirtual11_FuncPtr;
};
auto A::SetAPrtyVirtual11_FuncPtr = std::mem_fn(&A::SetAPrtyVirtual11);

struct I
{
    virtual void fee() = 0;
};

#if 1
struct B : A, I
{
    void SetAPrtyVirtual11(int a)
    {
        m_A = a;
    }

    void pook() override
    {
        std::cout << "B: pook" << std::endl;
    }

    void fee() override
    {
        std::cout << "B: fee" << std::endl;
    }

    static decltype(std::mem_fn(&B::SetAPrtyVirtual11)) SetAPrtyVirtual11_FuncPtr;
};
auto B::SetAPrtyVirtual11_FuncPtr = std::mem_fn(&B::SetAPrtyVirtual11);
#endif

int main()
{
    B b;

    void* foo = &B::SetAPrtyVirtual11_FuncPtr;
    auto a = reinterpret_cast<decltype(std::mem_fn(&B::SetAPrtyVirtual11))>(foo);
    return sizeof(B::SetAPrtyVirtual11_FuncPtr);
}
