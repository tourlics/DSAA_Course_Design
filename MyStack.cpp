#include <iostream>
using namespace std;
template<class N>
struct Node {
   N value;
   Node<N> *next;
   Node();
   Node(N item, Node<N> *add = NULL); 
};
template<class N>
Node<N>::Node(){
   next = NULL;
}
template<class N>
Node<N>::Node(N item, Node<N> *add){
   value = item;
   next = add;
}

template<class S>
class MyStack {
	public:
	    MyStack();              
	    MyStack(MyStack<S> &item); 
	    ~MyStack();
	    void push(S &item);
	    void pop();
	    S top();
	    bool empty(); 
	    void clear();
	protected:
    	Node<S> *topnode;  
};

template<class S>
MyStack<S>::MyStack(){
   topnode=NULL;
}
template<class S>
MyStack<S>::~MyStack(){
	clear();
}
template<class S>
bool MyStack<S>::empty(){
  if(topnode==NULL)
     return true;
  else
     return false;
}
template<class S>
void MyStack<S>::push(S &item){
   Node<S> *newtop = new Node<S>(item, topnode);
   topnode = newtop;
}
template<class S>
void MyStack<S>::pop(){
   	if (topnode != NULL){
   		Node<S> *oldtop = topnode;
   		topnode = oldtop->next;
   		delete oldtop;
   	}
}

template<class S>
S MyStack<S>::top(){
   	if(!empty()){
   		return topnode->value;
  	} 
}
template<class S>
void MyStack<S>::clear() {
   while (!empty()) pop();
}
int main(){
	MyStack<int> a;
	for(int i=0;i<10;i++){
		a.push(i);
	}
	cout<<a.empty()<<endl;
	while(!a.empty()){
		if(a.top()==3) a.pop();
		cout<<a.top()<<endl;
		a.pop();
	}
	cout<<a.empty()<<endl;
	return 0;
}
