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
            //std::cout<<"调用了基类的纯虚函数"<<std::endl;
            delete []data;
        }

    //4. 虚移动赋值运算符
        virtual Vector& operator=(Vector && other){
            if(size!=other.getSize()){
                throw "维度不同！！无法赋值";
            }
            delete[]data;
            size=other.size;
            data=other.data;
            other.size=0;
            other.data=nullptr;
            return *this;
        }

    //5. 纯虚运算符重载+
        virtual Vector<T>& operator+(const Vector<T> & other)=0;
        //得到size
        size_t getSize()const{
            return size;
        }

    //6. 纯虚函数set: 更改某个索引的元素
        //超出界限就报错
        virtual void set(size_t index,const T & value)=0;

    //7. 纯虚函数get：得到某个索引的元素
        virtual T get(size_t index)const=0;

    //8. 虚函数display：展示数据
        virtual void display()const{
            for(size_t i=0;i<size;++i){
                std::cout<<data[i]<<" ";
            }
            std::cout<<std::endl;
        }

};

template<class T>
class DerivedVector:public Vector<T>{
    public:
        DerivedVector(size_t size, const T *arr) : Vector<T>(size, arr) {}
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

        DerivedVector<T>& operator+(const Vector<T> & other) override{
            if(this->size!=other.getSize()){
                throw "维度不一样的向量不能相加";
            }
            for(size_t i=0;i<other.getSize();++i){
                this->data[i]+=other.get(i);
            }
            return *this;
            //return DerivedVector()
        }
};

//字符串类已经是字符串了
class String:public Vector<std::string>{
    public:
        String(size_t size, const std::string *arr) : Vector<std::string>(size, arr) {}
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

        String & operator+(const Vector<std::string>& other)override{
            size_t newsize=this->size+other.getSize();
            std::string* newdata=new std::string[newsize];

            for(size_t i=0;i<this->size;++i){
                newdata[i]=this->data[i];
            }
            for(size_t i=0;i<other.getSize();++i){
                newdata[i+this->size]=other.get(i);
            }
            this->size=newsize;
            this->data=newdata;
            return *this;
            /*
            //String* result = new String(this->size + other.getSize());
            delete this->data;
            //size_t s=this->size;
            this->size=this->size+other.getSize();
            this->data=new std::string[this->size];
            for(size_t i=0;i<this->size;++i){

            }
            */
            
        }
};
void menu1();
void menu2();
void menu3();
int main(){
    menu1();
    return 0;
}
void menu1(){
    
    //菜单1
    while (true){
        std::cout<<std::endl<<std::endl;
    std::cout<<"***************功能演示*************"<<std::endl;
    std::cout<<"*****1.向量演示*******"<<std::endl;
    std::cout<<"*****2.字符串演示*****"<<std::endl;
    std::cout<<"===================================="<<std::endl;
    std::cout<<"*******请输入操作(按0退出): ";
    int judge;
    std::cin>>judge;
    if(judge==0){
        break;
    }
    if(judge==1){
        menu2();
        continue;
    }
    if(judge==2){
        menu3();
        continue;
    }
    }
}

void menu2(){
    /*
    int arr1[3]{10,20,30};
    int arr2[3]{20,30,40};
    int arr3[4]{10,20,30,40};
    DerivedVector<int> vec1(3,arr1);    
    DerivedVector<int> vec3(4,arr3);
    DerivedVector<int> vec2(3,arr2);
    */
    while(true){
        int arr1[3]{10,20,30};
        int arr2[3]{20,30,40};
        int arr3[4]{10,20,30,40};
        DerivedVector<int> vec1(3,arr1);    
        DerivedVector<int> vec3(4,arr3);
        DerivedVector<int> vec2(3,arr2);
        std::cout<<std::endl<<std::endl;
        std::cout<<"~~说明：本菜单是测试派生类向量模板~~"<<std::endl;
        std::cout<<"~~测试数据有：~~"<<std::endl;
       // DerivedVector<int> vec1(3,arr1);
        std::cout<<"测试数据1（3维整数）: ";
        vec1.display();
       // DerivedVector<int> vec2(3,arr2);
        std::cout<<"测试数据2（3维整数）: ";
        vec2.display();
       // DerivedVector<int> vec3(4,arr3);
        std::cout<<"测试数据3（4维整数）: ";
        vec3.display();
        std::cout<<"**********派生向量·功能演示**********"<<std::endl;
        std::cout<<"*****1.“运算符=”功能演示*******"<<std::endl;
        std::cout<<"*****2.“运算符+”功能演示*******"<<std::endl;
        std::cout<<"*****3.“函数get”功能演示*******"<<std::endl;
        std::cout<<"*****4.“函数set”功能演示*******"<<std::endl;
        std::cout<<"*****5.“运算符=”异常操作功能演示"<<std::endl;
        std::cout<<"*****6.“运算符+”异常操作功能演示"<<std::endl;
        std::cout<<"*****7.“函数get”异常操作功能演示"<<std::endl;
        std::cout<<"*****8.“函数set”异常操作功能演示"<<std::endl;
        std::cout<<"===================================="<<std::endl;
        std::cout<<"*******请输入操作(按0退出): ";
        int judge;
        std::cin>>judge;        
        if(judge==0){
            break;
        }
        if(judge==1){
            //std::cout<<"可以"<<std::endl;
            std::cout<<std::endl<<"下面进行赋值运算符=的测试"<<std::endl;
            try{
                std::cout<<"将测试数据2赋值给测试数据1"<<std::endl;
                vec1=std::move(vec2);
                std::cout<<"输出测试数据1"<<std::endl;
                vec1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==2){
            std::cout<<std::endl<<"下面进行赋值运算符+的测试"<<std::endl;
            try{
                std::cout<<"将测试数据2与测试数据1相加"<<std::endl;
                int result_arr[3]{0,0,0};
                DerivedVector<int> result(3,result_arr);
                result=std::move(vec1+vec2);
                std::cout<<"输出相加后的向量"<<std::endl;
                result.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==3){
            std::cout<<std::endl<<"下面进行函数get的测试"<<std::endl;
            std::cout<<"函数get实现的功能是依据索引返回值，"<<std::endl;
            std::cout<<"例如依据索引3，得到数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中返回索引为2的数据:"<<std::endl;
                std::cout<<vec1.get(2)<<std::endl;
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==4){
            std::cout<<std::endl<<"下面进行函数set的测试"<<std::endl;
            std::cout<<"函数set实现的功能是依据索引修改值，"<<std::endl;
            std::cout<<"例如依据索引3，修改数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中修改索引为2的数据为1:"<<std::endl;
                vec1.set(2,1);
                vec1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==5){
            std::cout<<std::endl<<"下面进行赋值运算符=的异常测试"<<std::endl;
            try{
                std::cout<<"将测试数据3赋值给测试数据1"<<std::endl;
                vec1=std::move(vec3);
                std::cout<<"输出测试数据1"<<std::endl;
                vec1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==6){
            std::cout<<std::endl<<"下面进行赋值运算符+异常的测试"<<std::endl;
            try{
                std::cout<<"将测试数据3与测试数据1相加"<<std::endl;
                int result_arr[3]{0,0,0};
                DerivedVector<int> result(3,result_arr);
                result=std::move(vec1+vec3);
                std::cout<<"输出相加后的向量"<<std::endl;
                result.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
        }
        if(judge==7){
            std::cout<<std::endl<<"下面进行函数get的异常测试"<<std::endl;
            std::cout<<"函数get实现的功能是依据索引返回值，"<<std::endl;
            std::cout<<"例如依据索引3，得到数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中返回索引为3的数据:"<<std::endl;
                std::cout<<vec1.get(3)<<std::endl;
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==8){
            std::cout<<std::endl<<"下面进行函数set的异常测试"<<std::endl;
            std::cout<<"函数set实现的功能是依据索引修改值，"<<std::endl;
            std::cout<<"例如依据索引3，修改数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中修改索引为3的数据为1:"<<std::endl;
                vec1.set(3,1);
                vec1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
    }
}

void menu3(){
 std::string arr1[5]{"h","e","l","l","0"};
    std::string arr2[5]{"w","o","r","l","d"};
    std::string arr3[3]{"C","+","+"};
    while (true){
        String str1(5,arr1);
        String str2(5,arr2);
        String str3(3,arr3);
        std::cout<<std::endl<<std::endl;
        std::cout<<"~~说明：本菜单是测试派生类字符串~~"<<std::endl;
        std::cout<<"~~测试数据有：~~"<<std::endl;
        std::cout<<"测试数据1（hello）: ";
        str1.display();
        std::cout<<"测试数据2（world）: ";
        str2.display();
        std::cout<<"测试数据3（C++）: ";
        str3.display();
        std::cout<<"**********派生字符串·功能演示**********"<<std::endl;
        std::cout<<"*****1.“运算符=”功能演示*******"<<std::endl;
        std::cout<<"*****2.“运算符+”功能演示*******"<<std::endl;
        std::cout<<"*****3.“函数get”功能演示*******"<<std::endl;
        std::cout<<"*****4.“函数set”功能演示*******"<<std::endl;
        std::cout<<"*****5.“运算符=”异常操作功能演示"<<std::endl;
        //std::cout<<"*****6.“运算符+”异常操作功能演示"<<std::endl;
        std::cout<<"*****6.“函数get”异常操作功能演示"<<std::endl;
        std::cout<<"*****7.“函数set”异常操作功能演示"<<std::endl;
        std::cout<<"===================================="<<std::endl;
        std::cout<<"*******请输入操作(按0退出): ";
        int judge;
        std::cin>>judge;        
        if(judge==0){
            break;
        }
        if(judge==1){
            std::cout<<std::endl<<"下面进行赋值运算符=的测试"<<std::endl;
            try{
                std::cout<<"将测试数据2赋值给测试数据1"<<std::endl;
                str1=std::move(str2);
                std::cout<<"输出测试数据1"<<std::endl;
                str1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
        if(judge==2){
            std::cout<<std::endl<<"下面进行赋值运算符+的测试"<<std::endl;
                std::cout<<"将测试数据2与测试数据1相加"<<std::endl;
                std::string result_arr[10]{};
                String result(10,result_arr);
                result=std::move(str1+str2);
                std::cout<<"输出相加后的字符串"<<std::endl;
                result.display();
            continue;
        }
         if(judge==3){
            std::cout<<std::endl<<"下面进行函数get的测试"<<std::endl;
            std::cout<<"函数get实现的功能是依据索引返回值，"<<std::endl;
            std::cout<<"例如依据索引3，得到数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中返回索引为2的数据:"<<std::endl;
                std::cout<<str1.get(2)<<std::endl;
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
         if(judge==4){
            std::cout<<std::endl<<"下面进行函数set的测试"<<std::endl;
            std::cout<<"函数set实现的功能是依据索引修改值，"<<std::endl;
            std::cout<<"例如依据索引3，修改数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中修改索引为2的数据为X:"<<std::endl;
                str1.set(2,"X");
                str1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
         if(judge==5){
            std::cout<<std::endl<<"下面进行赋值运算符=异常的测试"<<std::endl;
            try{
                std::cout<<"将测试数据1赋值给测试数据3"<<std::endl;
                str3=std::move(str1);
                std::cout<<"输出测试数据1"<<std::endl;
                str1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        
        }
         if(judge==6){
            std::cout<<std::endl<<"下面进行函数get异常的测试"<<std::endl;
            std::cout<<"函数get实现的功能是依据索引返回值，"<<std::endl;
            std::cout<<"例如依据索引3，得到数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中返回索引为5的数据:"<<std::endl;
                std::cout<<str1.get(5)<<std::endl;
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
         if(judge==7){
            std::cout<<std::endl<<"下面进行函数set的测试"<<std::endl;
            std::cout<<"函数set实现的功能是依据索引修改值，"<<std::endl;
            std::cout<<"例如依据索引3，修改数据a[3]"<<std::endl;
            try{
                std::cout<<"在测试数据1中修改索引为5的数据为X:"<<std::endl;
                str1.set(5,"X");
                str1.display();
            }catch(const char*e){
                std::cerr<<e<<std::endl;
            }
            continue;
        }
    }
}