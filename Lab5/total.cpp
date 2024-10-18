#include<iostream>

template<class T>
class Vector{
    protected:
    //size储存向量大小
        size_t size;

    //data储存数据
        T *data;

    public:
    /******************构造函数不能写成虚构函数**********/
    //1.初始化构造函数
        Vector(size_t size):size(size),data(new T[size]){}

    //2. 参数化构造函数
        Vector(size_t size,const T *arr):size(size),data(new T[size]){
            std::copy(arr,arr+size,data);
        }

/*
    //2. 移动构造函数
        Vector(Vector && other)noexcept:size(other.size),data(other.data){
            /*要把other全部清空 免得other析构时候把原本的数据清空了*/
/*
            other.size=0;
            other.data=nullptr;
        }
*/

    //3. 虚析构函数
        virtual ~Vector(){
            std::cout<<"调用了基类的纯虚函数"<<std::endl;
            delete []data;
        }

    //4. 虚移动赋值运算符
        virtual Vector& operator=(Vector && other){
            delete[]data;
            size=other.size;
            data=other.data;
            other.size=0;
            other.data=nullptr;
        }

    //5. 纯虚运算符重载+
        /*virtual Vector<T> operator+(const Vector<T> & other)=0;*/

    //6. 纯虚函数set: 更改某个索引的元素
        //超出界限就报错
        virtual void set(size_t index,const T & value)=0;

    //7. 纯虚函数get：得到某个索引的元素
        virtual T get(size_t index)const=0;

    //8. 虚函数display：展示数据
        virtual void display()const{
            for(size_t i=0;i<size;++i){
                std::cout<<data[i]<<",";
            }
            std::cout<<std::endl;
        }

};

template<class T>
class DerivedVector:public Vector<T>{
    public:
        //实现虚函数
        void set(size_t index,const T & value)override{
            if(index>=this->size){
                throw "超出界限！！设置不了！";
            }
            else{
                this->data[index]=value;
            }
        }

        T get(size_t index)const override{
            if(index>=this->size){
                throw "超出界限！！没有数据！";
            }
            return this->data[index];
        }
    /*
        DerivedVector<T> operator+(const Vector<T> & other)const override{
            return 
        }
    */
};

//字符串类已经是字符串了
class String:public Vector<std::string>{
    public:
        void set(size_t index,const std::string & value)override{
            if(index>=this->size){
                throw "超出界限！！不能设置！";
            }
            this->data[index]=value;
        }
        std::string get(size_t index)const override{
            if(index>=this->size){
                throw "超出界限！！没有数据！";
            }
            return this->data[index];
        }
};
int main(){
    std::cout<<0<<std::endl;
    return 0;
}