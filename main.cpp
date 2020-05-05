#include <iostream>

template <class T>
class SPtr {
public:
    SPtr(T *ptr) : Ptr(ptr) {
        Count = new uint();
        (*Count)++;
        std::cout << "Count initialized " << *Count << std::endl;
    }

    SPtr(SPtr *ptr) {
        Link(ptr);
    }

    ~SPtr() {
        Dispose();
    }

    T* Get() const {
        return Ptr;
    }

    void Set(T *ptr) {
        Ptr = ptr;
    }

    SPtr& operator=(const SPtr& right) {
        if (this == &right) {
            return *this;
        }

        Dispose();
        Link(right);
        return *this;
    }

    T* operator->() {
        return Ptr;
    }

    explicit operator T*() {
        return Ptr;
    }

private:
    T* Ptr;
    uint* Count;

    void Dispose() {
        if (!Ptr) {
            return;
        }
        (*Count)--;
        std::cout << "Count decreased " << *Count << std::endl;
        if ((*Count) == 0)
        {
            delete Ptr;
            delete Count;
        }
        Ptr = nullptr;
        Count = nullptr;
    }

    void Link(SPtr *ptr){
        Ptr = ptr->Ptr;

        Count = ptr->Count;
        (*Count)++;
        std::cout << "Count increased " << *Count << std::endl;
    }
};

void test1() {
    char* ptr = new char(97);
    std::cout << *ptr << std::endl;

    auto* sPtr = new SPtr<char>(ptr);
    std::cout << sPtr->Get() << std::endl;
    auto* sPtr2 = new SPtr<char>(sPtr);
    std::cout << sPtr2->Get() << std::endl;

    delete sPtr;
    std::cout << sPtr2->Get() << std::endl;

    delete sPtr2;
}

void test2 () {
    char* ptr = new char(102);

    auto* sPtr = new SPtr<char>(ptr);
    auto* sPtr2 = sPtr;

    std::cout << sPtr2->Get() << std::endl;
    delete sPtr;
    std::cout << sPtr2->Get() << std::endl;

    delete sPtr2;
}

int main() {
    test1();
    test2();

    return 0;
}
