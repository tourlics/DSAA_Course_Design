#ifndef PRECHECK_H
#define PRECHECK_H
#include <iostream>
#include<string.h>
using namespace std;
void showerror(char temp[],int e);
bool precheck(char temp[]);

void showerror(char temp[],int e){ //指出第一次出现错误的位置 
	for(int i=0;i<strlen(temp);i++){
		if(i==e) cout<<temp[e]<<"<| ";
		else cout<<temp[i];
	}
	cout<<endl;
}
bool precheck(char temp[]){
	MyStack<char> t;
	for(int i=0;i<strlen(temp);i++){
		if((temp[i]&0x80) && (temp[i+1]&0x80)){//如果字符高位为1且下一字符高位也是1则有中文字符
			cout<<"请不要输入中文字符"<<endl;
			showerror(temp,i+1);
			return false;
		}
		if(temp[i] == '='&& i!=strlen(temp)-1){ //如果等号出现在表达式中间则报错 
			cout<<"Invalid input"<<endl;
			showerror(temp,i);
			return false;
		}
		if(!base(temp[i])){
			cout<<"Please input the sign appointed！"<<endl;//出现未知符号 
			showerror(temp,i);
			return false; 
		}
		if((temp[i]=='('||temp[i]==')')&&i!=0&&i!=strlen(temp)-1&&base(temp[i-1])==1&&base(temp[i+1])==1){
			cout<<"Both sides of parenthesis are numbers!"<<endl; //符号省略 
			showerror(temp,i);
			return false;
		} 
		if(((base(temp[0])==2)&&temp[0]!='-')||(i==strlen(temp)-1&&base(temp[i])==2)||(base(temp[i])==2&&base(temp[i+1])==2)){
			cout<<"Signs redundancy!"<<endl;//符号冗余（重复输入） 
			showerror(temp,i);
			return false;
		}
		if(temp[i]=='.'&&base(temp[i+1])!=1){
			cout<<"The fraction part you put is wrong!"<<endl;//小数部分输入错误 
			showerror(temp,i);
			return false;
		}
		if(temp[i]=='(') t.push(temp[i]);
		if(temp[i]==')') t.pop();	
	}
	if(t.empty()) return true;
	else {
		cout<<"Parenthesis is not matching!"<<endl;//括号不匹配 
		return false;
	}	
}
#endif
