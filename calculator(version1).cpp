#include<iostream>
#include<stack>
#include<string.h>
#include<math.h>

using namespace std;
stack<double> data;
stack<char> sign;

int priority(char ch){
	if(ch == '+'||ch == '-') return 1;
	if(ch == 'x'||ch == '/'|| ch== '%') return 2;
	if(ch == '^') return 3;
	if(ch == '(') return 0;
}

double aRb(char ch){
	double a,b;
	a = data.top();
	data.pop();
	b = data.top();
	data.pop();
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
				cout<<"divider can not be zero!"<<endl;
			}else {
				b /= a;
				break;
			}
		case '%' :
			b = (double)((int)b%(int)a);
			break;
		case '^' :
			b = pow(b,a);
			break;
	}
	return b;
}
void showerror(char temp[],int e){
	for(int i=0;i<strlen(temp);i++){
		if(i==e) cout<<temp[e]<<"<| ";
		else cout<<temp[i];
	}
	cout<<endl;
}
int base(char temp){
	char base_digtal[] = {"1234567890"};
	char base_sign[] = {"+-x/%^"};
	char base_others[] = {"().="};
	if(strchr(base_digtal,temp)) return 1;
	else if(strchr(base_sign,temp)) return 2;
	else if(strchr(base_others,temp)) return 3;
	else return 0;
}
bool precheck(char temp[]){
	
	stack<char> t;
	for(int i=0;i<strlen(temp);i++){
		if(temp[i] == '='&& i!=strlen(temp)-1){
			cout<<"invalid input"<<endl;
			showerror(temp,i);
			return false;
		}
		if(!base(temp[i])){
			cout<<"please input the sign appointed！"<<endl;
			showerror(temp,i);
			return false; 
		}
		if((temp[i]=='('||temp[i]==')')&&i!=0&&base(temp[i-1])==1&&base(temp[i+1])==1){
			cout<<"括号两边不能全为数字"<<endl;
			showerror(temp,i);
			return false;
		} 
		if(base(temp[i])==2&&base(temp[i+1])==2){
			cout<<"符号不能连续出现"<<endl;
			showerror(temp,i);
			return false;
		}
		if(temp[i]=='.'&&base(temp[i+1])!=1){
			cout<<"the fraction you put is wrong!"<<endl;
			showerror(temp,i);
			return false;
		}
		if(temp[i]=='(') t.push(temp[i]);
		if(temp[i]==')') t.pop();	
	}
	if(t.empty()) return true;
	else {
		cout<<"括号不匹配！"<<endl;
		return false;
	}	
}
double calculate(char temp[]){
	double d = 0;
	bool state_fraction = 0;//fraction
	bool state_sign = 1;//sign
	int count = 1;
	int s=0,t=0;
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
			}else if(temp[i]!=')'&&temp[i]!='='&&priority(temp[i])<=priority(sign.top())){
			//如果优先级小于栈顶，则直接进行运算，把运算结果存入数值栈 //注意等号放的位置 
				while(!sign.empty()&&priority(temp[i])<=priority(sign.top())){
					data.push(aRb(sign.top()));
					sign.pop();
				}
					
				sign.push(temp[i]);
			}else if(temp[i]!=')'&&temp[i]!='='&&priority(temp[i])>priority(sign.top())){
			//如果优先级大于栈顶，则入符号栈 
				sign.push(temp[i]);
			}else if(temp[i]==')'||temp[i]=='='){
			//如果遇到)或者=，则符号栈全部出栈，同时从数值栈取出两个数进行运算 
				while(!sign.empty()&&sign.top()!='('){//根据短路原则，注意顺序 
					data.push(aRb(sign.top()));
					sign.pop();
				}
				if(!sign.empty()) sign.pop();//弹出( 
			}
			state_sign = 1;	
		}
	}
	return data.top();
}

int main(){
	cout<<"Welcome!(input exit to exit)"<<endl;
	while(1){
		char temp[300];
		cin>>temp;
		if(strcmp(temp,"exit")==0) break; 
		if(!precheck(temp)) continue;
		if(temp[0]=='-'){
			int k = strlen(temp);
			for(k;k>0;k--) temp[k] = temp[k-1];
			temp[0] = '0';
			k = strlen(temp);
			if(temp[k-1]!='=') {
				temp[k] = '=';
				temp[k+1] = '\0';
			}
		}else{
			for(int i=0;i<strlen(temp);i++){
				if(temp[i]=='-'&& base(temp[i-1])!=1&&temp[i-1]!=')'){//注意此处优化了 
					int k = strlen(temp);
					for(k;k>i;k--) temp[k] = temp[k-1];
						temp[i] = '0';
				}
			}
			int k = strlen(temp);
			if(temp[k-1]!='=') {
				temp[k] = '=';
				temp[k+1] = '\0';
			}
		}
		
		
		cout<<"ans = "<<calculate(temp)<<endl;
		
	}
	//while(choice=='N'){
	/*	char temp[300];
		int i=0;
		char t = cin.get();
		if(t == '-') {
			temp[0] = '0';
			temp[1] = '-';
			i = 1;
		}else temp[0] = t;
		while(1){
			t = cin.get();
			if(t == '-' && base(temp[i])!=1) {
				temp[++i] = '0';
				temp[++i] = t;
			}else if(t == '\n') break;
			else temp[++i] = t;
		}
		
	*/
		//cout<<temp[strlen(temp)-1]<<endl;
		//for(int j=0;j<strlen(temp);j++){
		//	cout<<temp[j]<<" ";
		//}
		
		//continue;
		
		//cout<<"EXIT? press N to continue"<<endl;
		//cin>>choice;
		//cin.get();	
	//}
	//showerror(temp,2);
	//cout<<strlen(temp);
	
	
	return 0;
}
//-(-3+(3x(5/2+(3^2%5)+5)x2)/3)+((2x5-3)x2)=
//-(-2+3-5)=
//12+.3-.5x2
//.3+4-2x(3+5/2^3)-.3
//-3.4+4
//3.22.4+2?
//2.3x(3+3.4)-4/2.2



