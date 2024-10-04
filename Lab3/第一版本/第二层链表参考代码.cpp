#include<iostream>
using std::string;
using std::cout;
using std::endl;
using std::cin;


/************************一，第一部分**********************************/
// Data结构体，储存最底层的数据：角色+对应的原石数量
struct Data
{
    string name;
    int stones;
};

// Node对象，包含了Data和下一个指针
class Node
{
    private:
        Data data;
        Node *next;
    
    public:
        Node(const Data &data):data(data),next(NULL){};    
        friend class Hero;    
};

// Hero对象，抽象整个链表类。
class Hero
{
    private:
        Node *head;
        int num;
    
    public:
        //1. 构建链表
        Hero(int n,const Data *datas):head(NULL),num(0){
            num=n;
            for(size_t i=0;i<n;i++){
                Node *temp=new Node(datas[i]);
                temp->next=head;
                head=temp;
            }
        }

        //2. 输出链表
        void showList(){
            cout<<"此账号拥有的角色以及所消耗的原石为："<<endl;
            cout<<"----------------------"<<endl;
            for(Node *p=head;p!=NULL;p=p->next){
                cout<<p->data.name<<" --> "<<p->data.stones<<endl;
                cout<<"   "<<"|"<<endl;
                cout<<"   "<<"|"<<endl;
            }
            cout<<"  "<<"NULL"<<endl;
            cout<<"----------------------"<<endl;
            cout<<endl;
        }

        //3. 清空链表
        void freeList(){
            cout<<"链表已经全部清空。"<<endl;
            while(head!=NULL){
                Node *temp=head;
                head=head->next;
                delete temp;
            }
            cout<<endl;
        }

        //4. 增添结点
        void append(const Data &data){
            Node *_new=new Node(data);
            num++;
            _new->next=head;
            head=_new;
        }
        
        //5. 查询是否有某个角色
        bool find(const string & name){
            for(Node *temp=head;temp!=NULL;temp=temp->next){
                if(temp->data.name==name){
                    cout<<"您已经拥有角色："<<name<<"，抽取此角色消耗原石 "<<temp->data.stones<<endl;
                    return true;
                }
            }
            cout<<"您还未拥有此角色"<<endl;
            return false;
        }

        //6. 输出五星角色的个数
        int heronums()const{
            cout<<"您拥有五星角色的个数为："<<num<<endl;
            return num;
        }
};


/************************************二，第二部分********************* */
int main(){
    // 构建Data数组
    Data datas[]{
        {"那维莱特",70},
        {"甘雨",143},
        {"芙宁娜",2},
    };
    int n=sizeof(datas)/sizeof(*datas);

    Hero hero1(n,datas);
    hero1.showList();

    //append的调试
    /*
    string name;
    cin>>name;
    int stone;
    cin>>stone;
    Data data{name,stone};
    hero1.append(data);
    hero1.showList();
    */
    hero1.heronums();
    //find的调试
    hero1.find("甘雨");
    
    return 0;
}