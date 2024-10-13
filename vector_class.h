#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <initializer_list>
#include<string>
using namespace std;

template <typename T>
class Vector {
private:
    T* data;          // 指向数组的指针
    size_t size;      // 当前元素数量
    size_t capacity;  // 数组的总容量

public:

    Vector(size_t size=0) : size(size), capacity(size) ;

    Vector(size_t size, T value) : size(size), capacity(size) ;

    // 使用初始化列表的构造函数
    Vector(std::initializer_list<T> init) : size(init.size()), capacity(init.size());

    // 拷贝构造函数
    Vector(const Vector& other) : size(other.size), capacity(other.capacity) ;

    // 赋值运算符
    Vector& operator=(const Vector& other) ;

    // 析构函数
    ~Vector();

    // 获取元素数量
    size_t getSize() const;

    // 获取容量
    size_t getCapacity() const ;

    // 向量增加元素
    void push_back(const T& value) ;

    // 删除最后一个元素
    void pop_back();
    // 向量插入元素
    void insert(size_t index, const T& value);

    //向量范围插入
    void insert(size_t index, size_t count, const T& value);

    // 向量删除元素
    void erase(size_t index) ;

    //向量范围删除
    void erase(size_t index, size_t count) ;

    // 清空向量
    void clear() ;

    // 下标运算符重载
    T& operator[](size_t index) const;

    Vector<T> operator+(const Vector<T> & other) const;

    Vector<T>& operator+=(const Vector<T> & other);

    bool operator==(const Vector<T> & other) const;

    bool operator!=(const Vector<T> & other) const; 

    bool operator>(const Vector<T> & other) const;

    bool operator<(const Vector<T> & other) const;

    bool operator>=(const Vector<T> & other) const;

    bool operator<=(const Vector<T> & other) const;
    //重载输出流运算符
    friend ostream& operator<<(ostream& out, const Vector<T>& vec);

    friend istream& operator>>(istream& in, Vector<T>& vec) ;

private:
    // 重新分配空间
    void resize() {
        size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
};

    template<typename T> Vector<T>:: Vector(size_t size=0) : size(size), capacity(size) {
        data = new T[capacity];
    }

    template<typename T> Vector<T>::Vector(size_t size, T value) : size(size), capacity(size) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    // 使用初始化列表的构造函数
    template<typename T> Vector<T>::Vector(std::initializer_list<T> init) : size(init.size()), capacity(init.size()) {
        data = new T[capacity];
        size_t index = 0;
        for (const auto& value : init) {
            data[index++] = value;
        }
    }

    // 拷贝构造函数
    template<typename T> Vector<T>::Vector(const Vector& other) : size(other.size), capacity(other.capacity) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    

    // 赋值运算符
    template<typename T> Vector<T> &  Vector<T>:: operator=(const Vector& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            for (size_t i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // 析构函数
   template<typename T> Vector<T>::  ~Vector() {
        delete[] data;
    }

    // 获取元素数量
    template<typename T> size_t Vector<T>::getSize() const {
        return size;
    }

    // 获取容量
    template<typename T> size_t Vector<T>:: getCapacity() const {
        return capacity;
    }

    // 向量增加元素
    template<typename T> void Vector<T>:: push_back(const T& value) {
        if (size >= capacity) {
            resize();
        }
        data[size++] = value;
    }

    // 删除最后一个元素
    template<typename T> void Vector<T>:: pop_back() {
        if (size > 0) {
            --size;
        }
    }

    // 向量插入元素
    template<typename T> void Vector<T>:: insert(size_t index, const T& value) {
        if (size >= capacity) {
            resize();
        }
        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        ++size;
    }

    //向量范围插入
    template<typename T> void Vector<T>:: insert(size_t index, size_t count, const T& value) {
        if (size + count > capacity) {
               resize();
        }
        for (size_t i = size; i > index; --i) {
            data[i+count] = data[i ];
        }
        for (size_t i = index; i < index + count; ++i) {
            data[i] = value;
        }
        cout << capacity << endl;
        size += count;
    }

    // 向量删除元素
    template<typename T> void Vector<T>:: erase(size_t index) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }
        --size;
    }

    //向量范围删除
    template<typename T> void Vector<T>:: erase(size_t index, size_t count) {
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        if (index + count > size) {
            count = size - index;
        }
        for (size_t i = index; i < size - count; ++i) {
            data[i] = data[i + count];
        }
        size -= count;
    }

    // 清空向量
    template<typename T> void Vector<T>:: clear() {
        size = 0;
        }

    // 下标运算符重载
    template<typename T> T& Vector<T>::  operator[](size_t index) const{
        if (index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    template<typename T> Vector<T> Vector<T>::  operator+(const Vector<T> & other) const{
        if(this->size!= other.size) throw std::invalid_argument("Vector sizes do not match");
        Vector<T> result(this->size);
        for(size_t i=0;i<this->size;i++){
            result[i] = this->data[i] + other.data[i];
        }
        return result;
    }    

    template<typename T> Vector<T>& Vector<T>:: operator+=(const Vector<T> & other) {
        if(this->size!= other.size) throw std::invalid_argument("Vector sizes do not match");
        for(size_t i=0;i<this->size;i++){
            this->data[i] += other.data[i];
        }
        return *this;
    }

    template<typename T> bool Vector<T>:: operator==(const Vector<T> & other) const{
        if(this->size!= other.size) return false;    
        for(size_t i=0;i<this->size;i++){
            if(this->data[i] != other.data[i]) return false;
        }
        return true;
    }

    template<typename T> bool Vector<T>:: operator!=(const Vector<T> & other) const{
        return !(*this == other);
    }

    template<typename T> bool Vector<T>:: operator>(const Vector<T> & other) const{
        if(this->size != other.size) throw std::invalid_argument("Vector sizes do not match");
        for(size_t i=0;i<this->size;i++){
            if(this->data[i] <= other.data[i]) return false;
        }
        return true;
    }

    template<typename T> bool Vector<T>:: operator<(const Vector<T> & other) const{
        if(this->size != other.size) throw std::invalid_argument("Vector sizes do not match");
        for(size_t i=0;i<this->size;i++){    
            if(this->data[i] >= other.data[i]) return false;
        }
        return true;
    }

    template<typename T> bool Vector<T>:: operator>=(const Vector<T> & other) const{
        if(this->size != other.size) throw std::invalid_argument("Vector sizes do not match");
        for(size_t i=0;i<this->size;i++){
            if(this->data[i] < other.data[i]) return false;
        }
        return true;
    }

   template<typename T> bool Vector<T>:: operator<=(const Vector<T> & other) const{
        if(this->size != other.size) throw std::invalid_argument("Vector sizes do not match");
        for(size_t i=0;i<this->size;i++){
            if(this->data[i] > other.data[i]) return false;
        }
        return true;
    }
     template<typename T> ostream& operator<<(ostream& out, const Vector<T>& vec) {
        out << "(" ;
        for (size_t i = 0; i < vec.size; ++i) {
            out  << vec.data[i];
            if (i != vec.size - 1) {
                out << ", ";
            }
        }
        out << ")";
        return out;
    }

   template<typename T> istream& operator>>(istream& in, Vector<T>& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            in >> vec.data[i];
        }
        return in;
    }

// 测试示例
void testVector() {
    string s1 = "hello";
    Vector<int> v1(5, 1);
    Vector<int> v2(v1);
    cout << v1+v2 << endl;
    v1.insert(1,3,2);
    cout << v1;
}



#endif // VECTOR_CLASS_H