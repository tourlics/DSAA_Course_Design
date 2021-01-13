#include<iostream>
#include<stack>
#include<string.h>
#include<math.h>

using namespace std;
stack<double> data;
stack<char> sign;

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

void showerror(char temp[],int e){ //指出第一次出现错误的位置 
	for(int i=0;i<strlen(temp);i++){
		if(i==e) cout<<temp[e]<<"<| ";
		else cout<<temp[i];
	}
	cout<<endl;
}
bool precheck(char temp[]){
	stack<char> t;
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
			//如果优先级小于等于栈顶，则直接进行运算，把运算结果存入数值栈 
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

int main() {
	cout<<"---------Welcome!---------"<<endl;
	cout<<"----Input exit to exit----"<<endl; 
	double ans; //最终计算结果 
	while(1){
		char temp[300]; //存储读入的字符串，用于预处理等操作 
		memset(temp,0,300);  
		while(!data.empty()) data.pop();
		while(!sign.empty()) sign.pop(); //初始化
		cin.getline(temp,300);
		if(strcmp(temp,"exit")==0) break; //程序出口 
		//展示更精确的结果
		if(strcmp(temp,"show more")==0){  
			printf("ans = %.9lf\n",ans);
			continue;
		}
		//对空格进行处理
		for(int i=0;i<strlen(temp);i++){
			if(temp[i]==' ')
				for(int k=i;k<strlen(temp);k++) 
					temp[k] = temp[k+1];
		} 
		if(!precheck(temp)) continue; //预处理结果判断 
		//对'-'前没有数字的情况进行加0处理 
		if(temp[0]=='-'){
			int k = strlen(temp);
			for(k;k>0;k--) temp[k] = temp[k-1];
			temp[0] = '0';
		}
		for(int i=1;i<strlen(temp);i++){
			if(temp[i]=='-'&& base(temp[i-1])!=1&&temp[i-1]!=')'){
				int k = strlen(temp);
				for(k;k>i;k--) temp[k] = temp[k-1];
					temp[i] = '0';
			}
		}	
		//如果用户没有输入'='，在字符串末尾添加'=' 
		int k = strlen(temp);
		temp[k] = '\0';
		if(temp[k-1]!='=') {
			temp[k] = '=';
			temp[k+1] = '\0';
		}
		//运行异常检测 
		try{
			ans = calculate(temp);
			cout<<"ans = "<<ans<<endl;	
		}catch(const char*message){
			cout<<message<<endl;
		}	
	}
	return 0;
}
//-(-3+(3x(5/2+(3^2%5)+5)x2)/3)+((2x5-3)x2)=
//-(-2+3-5)=
//12+.3-.5x2
//.3+4-2x(3+5/2^3)-.3
//-3.4+4
//3.22.4+2?
//2.3x(3+3.4)-4/2.2
//(2-(-(-(-(-(-2)x3)x1)x.3)/2.3)-2)/2
//2.6125 + 0.04150390625

