#include <iostream>


using namespace std;
struct Node{
    int age;
    string name;
    string address;
    struct Node *next;

};
class QueueStack{
public:
    struct Node *fron = NULL;
    struct Node *rear = NULL;
    struct Node *top=NULL;
    int queuNum=0;
    int stackNum=0;

    void Enqueue(int age,string name,string address) {
	struct Node* temp =new struct Node[1];
    temp->age =age;
	temp->name=name;
	temp->address=address;
	temp->next =NULL;
	if(fron ==NULL && rear == NULL){
		fron = rear = temp;
	}
	rear->next = temp;
	rear = temp;
	queuNum++;
	cout<<"queue has "<<queuNum<<" elements"<<endl;
	cout<<"name: "<<name<<", age: "<<age<<", address: "<<address<<endl;
}
    void Dequeue() {
        struct Node* temp = fron;
        if(fron == NULL) {
            cout<<"Queue is Empty"<<endl;
            return;
        }
        if(fron == rear) {
            fron = rear = NULL;
        }
        else {
            fron = fron->next;
        }
        queuNum--;
        cout<<"queue has "<<queuNum<<" elements"<<endl;
        cout<<"name: "<<temp->name<<", age: "<<temp->age<<", address: "<<temp->address<<endl;
        delete(temp);
    }
    void pushStack(int age,string name,string address){
        struct Node *temp = new struct Node[1];
        temp->name = name;
        temp->age=age;
        temp->address=address;
        temp->next =NULL;

        if(top == NULL){
            top=temp;
        }
        else{
            temp->next=top;
            top=temp;

        }
        stackNum++;
        cout<<"Stack has "<<stackNum<<" elements"<<endl;
        cout<<"name: "<<temp->name<<", age: "<<temp->age<<", address: "<<temp->address<<endl;

    }
    void popStack(){
        struct Node *temp =top;
        if(top==NULL){
            cout<<"Stack is empty"<<endl;

        }
        else{

            top=top->next;
            stackNum--;
            cout<<"Stack has "<<stackNum<<" elements"<<endl;
            cout<<"name: "<<temp->name<<", age: "<<temp->age<<", address: "<<temp->address<<endl;
            delete(temp);
        }

    }

    void printQueue(){
        struct Node *ptr =fron;
        cout<<"*************************"<<endl;
        cout<<"number of elements : "<<queuNum<<endl;
        while(ptr!=NULL){
            cout<<ptr->name<<" , "<<ptr->age<<" , "<<ptr->address<<endl;
            ptr=ptr->next;
        }
        cout<<"*************************"<<endl;
    }

    void printStack(){
        struct Node *ptr =top;
        cout<<"*************************"<<endl;
        cout<<"number of elements : "<<stackNum<<endl;
        while(ptr!=NULL){
            cout<<ptr->name<<" , "<<ptr->age<<" , "<<ptr->address<<endl;
            ptr=ptr->next;
        }
        cout<<"*************************"<<endl;
    }





};


int main()
{
    QueueStack que;
    que.pushStack(25,"ahmed","Haram");
    que.pushStack(23,"gamal","dokki");
    que.pushStack(26,"omar","october");
    que.printStack();
    que.popStack();
    que.printStack();

    cout<<"##############################"<<endl;
    cout<<"##############################"<<endl;
    que.Enqueue(25,"Mohammed","Haram");
    que.Enqueue(23,"khalaf","dokki");
    que.Enqueue(26,"fawzy","october");
    que.printQueue();
     que.Dequeue();
     que.printQueue();
    return 0;
}
