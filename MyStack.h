#ifndef MY_STACK_H
#define MY_STACK_H
#include<iostream> 
template<class N>
struct Node {
   N value;
   Node<N> *next;
   Node();
   Node(N item, Node<N> *add = NULL); 
}; //创建链表结点 
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
	    MyStack(MyStack<S> &item); //有参构造函数 
	    ~MyStack();
	    void push(S &item); //入栈操作 
	    void pop();        //出栈操作 
	    S top();           //访问栈顶元素 
	    bool empty();      //判断栈是否为空 
	    void clear();      //清空栈（优化了STL） 
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

#endif
