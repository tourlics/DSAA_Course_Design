#ifndef CALCULATE_H
#define CALCULATE_H
#include <iostream>
#include<string.h>
#include<math.h>
using namespace std;
MyStack<double> data;
MyStack<char> sign;
int priority(char );
double aRb(char );
int base(char );
double calculate(char temp[]);

int priority(char ch){ //运算符优先级判断 
	if(ch == '+'||ch == '-') return 1;
	if(ch == 'x'||ch == '/'|| ch== '%') return 2;
	if(ch == '^') return 3;
	if(ch == '(') return 0;
}

double aRb(char ch){ //判断运算类型 
	double a,b;
	a = data.top();
	data.pop();
	b = data.top();
	data.pop(); //依次取出栈顶两个元素 
	switch(ch){
		case '+' :
			b += a;
			break;
		case '-' :
			b -= a;
			break;
		case 'x' :
			b *= a;
			break;
		case '/' :
			if(a==0){
				throw "Divider can not be zero!"; //除数为0，抛出异常 
			}else {
				b /= a;
				break;
			}
		case '%' :
			if(a==0){
				throw "divider can not be zero!"; //除数为0，抛出异常
			}else {
				b = (double)((int)b%(int)a);
				break;
			}
		case '^' :
			b = pow(b,a); //乘方、开方运算 
			break;
	}
	return b;
}

int base(char temp){ //判断字符类型 
	char base_digtal[] = {"1234567890"};
	char base_sign[] = {"+-x/%^"};
	char base_others[] = {"().="};
	if(strchr(base_digtal,temp)) return 1;
	else if(strchr(base_sign,temp)) return 2;
	else if(strchr(base_others,temp)) return 3;
	else return 0;
}

double calculate(char temp[]){
	double d = 0;
	bool state_fraction = 0;//判断当前数字字符在小数点前面还是后面 
	bool state_sign = 1;//判断一个数是否读完 
	int count = 1;
	for(int i=0;i<strlen(temp);i++){
		//把数字字符处理成数值 
		if(!state_fraction&&base(temp[i])==1){
			d *= 10; 
			d += (double)(temp[i] - '0');
			state_sign=0;
		}else if(temp[i]=='.'){
			state_fraction = 1;
			
		}else if(state_fraction&&(base(temp[i])==1)){
			d += (double)(temp[i] - '0')/pow(10,count);
			count++;
			state_sign=0;
		}else{
			if(!state_sign) {
				data.push(d);
			}
			d = 0;
			state_fraction = 0;
			count = 1;
			if(temp[i]=='('||sign.empty()){//如果是(或栈为空直接入栈 
				sign.push(temp[i]);
			}else if(temp[i]==')'||temp[i]=='='){
			//如果遇到)或者=，则符号栈全部出栈，同时从数值栈取出两个数进行运算 
				while(!sign.empty()&&sign.top()!='('){//根据短路原则，注意顺序 
					double res = aRb(sign.top());
					data.push(res);
					sign.pop();
				}
				if(!sign.empty()) sign.pop();//弹出( 
			}else if(priority(temp[i])<=priority(sign.top())){
			//如果优先级小于栈顶，则直接进行运算，把运算结果存入数值栈 
			//等号的位置决定从左到右进行运算  
				while(!sign.empty()&&priority(temp[i])<=priority(sign.top())){
					double res = aRb(sign.top());
					data.push(res);
					sign.pop();
				}		
				sign.push(temp[i]);
			}else if(priority(temp[i])>priority(sign.top())){
			//如果优先级大于栈顶，则入符号栈 
				sign.push(temp[i]);
			}
			state_sign = 1;	//遇到非数字字符表示数字部分已读完 
		}
	}
	return data.top(); //栈顶元素即为最终运算结果 
}

#endif
