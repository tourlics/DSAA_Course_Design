#include<iostream>
#include<stack>
#include<string.h>
#include<math.h>
#include<vector>

using namespace std;
stack<double> data;
stack<char> sign;
vector<double> suf;

int priority(char ch){
	if(ch == '+'||ch == '-') return 1;
	if(ch == 'x'||ch == '/'|| ch== '%') return 2;
	if(ch == '^') return 3;
}
char vchanges(double a){
	if(a==100000) return '+';
	if(a==100001) return '-';
	if(a==100002) return 'x';
	if(a==100003) return '/';
	if(a==100004) return '%';
	if(a==100005) return '^';
}
double schangev(char a){
	if(a=='+') return 100000;
	if(a=='-') return 100001;
	if(a=='x') return 100002;
	if(a=='/') return 100003;
	if(a=='%') return 100004;
	if(a=='^') return 100005;
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
	//cout<<b<<endl;
	return b;
}
bool precheck(char temp[]){
	char base[] = {"+-x/%^()1234567890.="};
	stack<char> t;
	for(int i=0;i<strlen(temp);i++){
		if(strchr(base,temp[i])==NULL){
			cout<<"please input the sign appointed！"<<endl;
			return false; 
		}
		if(temp[i]=='.'&&(temp[i+1]>='9'||temp[i+1]<='0'||temp[i-1]>='9'||temp[i-1]<='0')){
			cout<<"the fraction you put is wrong!"<<endl;
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
void exchange(char temp[]){
	double d = 0;
	bool state_fraction = 0;//fraction
	bool state_sign = 1;//sign
	int count = 1;
	int s=0,t=0;
	for(int i=0;i<strlen(temp);i++){
		//把数字字符处理成数值 
		if(!state_fraction&&temp[i]<='9'&&temp[i]>='0'){
			d *= 10; 
			d += (double)(temp[i] - '0');
			state_sign=0;
		}else if(temp[i]=='.'){
			state_fraction = 1;
			
		}else if(state_fraction&&temp[i]<='9'&&temp[i]>='0'){
			d += (double)(temp[i] - '0')/pow(10,count);
			count++;
			state_sign=0;
		}else{
			if(!state_sign) {
				suf.push_back(d);
				//cout<<d<<endl;
			}
			d = 0;
			state_fraction = 0;
			count = 1;
			if(sign.empty()||temp[i]=='('||sign.top()=='('){
				sign.push(temp[i]);
			}else if(sign.top()!='('&&temp[i]!=')'&&temp[i]!='='&&priority(temp[i])>=priority(sign.top())){
				sign.push(temp[i]);
			}else if(sign.top()!='('&&temp[i]!=')'&&temp[i]!='='&&priority(temp[i])<priority(sign.top())){
				while (!sign.empty()){
                    suf.push_back(schangev(sign.top()));
                    sign.pop();
                }
                sign.push(temp[i]);
			}else if(temp[i] == ')'){
				while(!sign.empty() && sign.top()!='('){
					suf.push_back(schangev(sign.top()));
					sign.pop();
				}
				sign.pop();	
			}else if(temp[i] == '='){
				while (!sign.empty()){//如果堆栈不为空，则将其中的元素全部弹出
			       suf.push_back(schangev(sign.top()));
			       sign.pop();
			    }
			}
			state_sign = 1;	
		}
	}
	
}
void show(vector<double> suf){
	vector<double>::iterator it=suf.begin();
	for(;it!=suf.end();it++)  {
    	cout<<*it<<" ";
	}
}
double calculate(vector<double> suf){
	vector<double>::iterator it=suf.begin();  //  用迭代器遍历 
    for(;it!=suf.end();it++)  {
    	if(*it<100000) data.push(*it);
    	if(*it>=100000) {
    		char c = vchanges(*it);
    		data.push(aRb(c));
		}
	}
	return data.top();
}

int main(){
	char temp[300];
	cin>>temp;
	if(!precheck(temp)) return 0;
	exchange(temp);
	//show(suf);
	cout<<calculate(suf);
	
	return 0;
}
//3x(2.5+6/3)+8=
