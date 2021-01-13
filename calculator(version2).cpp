#include<iostream>
#include<stack>
#include<string.h>
#include<math.h>

using namespace std;
stack<double> data;
stack<char> sign;

int priority(char ch){ //��������ȼ��ж� 
	if(ch == '+'||ch == '-') return 1;
	if(ch == 'x'||ch == '/'|| ch== '%') return 2;
	if(ch == '^') return 3;
	if(ch == '(') return 0;
}

double aRb(char ch){ //�ж��������� 
	double a,b;
	a = data.top();
	data.pop();
	b = data.top();
	data.pop(); //����ȡ��ջ������Ԫ�� 
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
				throw "Divider can not be zero!"; //����Ϊ0���׳��쳣 
			}else {
				b /= a;
				break;
			}
		case '%' :
			if(a==0){
				throw "divider can not be zero!"; //����Ϊ0���׳��쳣
			}else {
				b = (double)((int)b%(int)a);
				break;
			}
		case '^' :
			b = pow(b,a); //�˷����������� 
			break;
	}
	return b;
}

int base(char temp){ //�ж��ַ����� 
	char base_digtal[] = {"1234567890"};
	char base_sign[] = {"+-x/%^"};
	char base_others[] = {"().="};
	if(strchr(base_digtal,temp)) return 1;
	else if(strchr(base_sign,temp)) return 2;
	else if(strchr(base_others,temp)) return 3;
	else return 0;
}

void showerror(char temp[],int e){ //ָ����һ�γ��ִ����λ�� 
	for(int i=0;i<strlen(temp);i++){
		if(i==e) cout<<temp[e]<<"<| ";
		else cout<<temp[i];
	}
	cout<<endl;
}
bool precheck(char temp[]){
	stack<char> t;
	for(int i=0;i<strlen(temp);i++){
		if((temp[i]&0x80) && (temp[i+1]&0x80)){//����ַ���λΪ1����һ�ַ���λҲ��1���������ַ�
			cout<<"�벻Ҫ���������ַ�"<<endl;
			showerror(temp,i+1);
			return false;
		}
		if(temp[i] == '='&& i!=strlen(temp)-1){ //����Ⱥų����ڱ��ʽ�м��򱨴� 
			cout<<"Invalid input"<<endl;
			showerror(temp,i);
			return false;
		}
		if(!base(temp[i])){
			cout<<"Please input the sign appointed��"<<endl;//����δ֪���� 
			showerror(temp,i);
			return false; 
		}
		if((temp[i]=='('||temp[i]==')')&&i!=0&&i!=strlen(temp)-1&&base(temp[i-1])==1&&base(temp[i+1])==1){
			cout<<"Both sides of parenthesis are numbers!"<<endl; //����ʡ�� 
			showerror(temp,i);
			return false;
		} 
		if(((base(temp[0])==2)&&temp[0]!='-')||(i==strlen(temp)-1&&base(temp[i])==2)||(base(temp[i])==2&&base(temp[i+1])==2)){
			cout<<"Signs redundancy!"<<endl;//�������ࣨ�ظ����룩 
			showerror(temp,i);
			return false;
		}
		if(temp[i]=='.'&&base(temp[i+1])!=1){
			cout<<"The fraction part you put is wrong!"<<endl;//С������������� 
			showerror(temp,i);
			return false;
		}
		if(temp[i]=='(') t.push(temp[i]);
		if(temp[i]==')') t.pop();	
	}
	if(t.empty()) return true;
	else {
		cout<<"Parenthesis is not matching!"<<endl;//���Ų�ƥ�� 
		return false;
	}	
}
double calculate(char temp[]){
	double d = 0;
	bool state_fraction = 0;//�жϵ�ǰ�����ַ���С����ǰ�滹�Ǻ��� 
	bool state_sign = 1;//�ж�һ�����Ƿ���� 
	int count = 1;
	for(int i=0;i<strlen(temp);i++){
		//�������ַ��������ֵ 
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
			if(temp[i]=='('||sign.empty()){//�����(��ջΪ��ֱ����ջ 
				sign.push(temp[i]);
			}else if(temp[i]==')'||temp[i]=='='){
			//�������)����=�������ջȫ����ջ��ͬʱ����ֵջȡ���������������� 
				while(!sign.empty()&&sign.top()!='('){//���ݶ�·ԭ��ע��˳�� 
					double res = aRb(sign.top());
					data.push(res);
					sign.pop();
				}
				if(!sign.empty()) sign.pop();//����( 
			}else if(priority(temp[i])<=priority(sign.top())){
			//������ȼ�С�ڵ���ջ������ֱ�ӽ������㣬��������������ֵջ 
			//�Ⱥŵ�λ�þ��������ҽ�������  
				while(!sign.empty()&&priority(temp[i])<=priority(sign.top())){
					double res = aRb(sign.top());
					data.push(res);
					sign.pop();
				}		
				sign.push(temp[i]);
			}else if(priority(temp[i])>priority(sign.top())){
			//������ȼ�����ջ�����������ջ 
				sign.push(temp[i]);
			}
			state_sign = 1;	//�����������ַ���ʾ���ֲ����Ѷ��� 
		}
	}
	return data.top(); //ջ��Ԫ�ؼ�Ϊ���������� 
}

int main() {
	cout<<"---------Welcome!---------"<<endl;
	cout<<"----Input exit to exit----"<<endl; 
	double ans; //���ռ����� 
	while(1){
		char temp[300]; //�洢������ַ���������Ԥ����Ȳ��� 
		memset(temp,0,300);  
		while(!data.empty()) data.pop();
		while(!sign.empty()) sign.pop(); //��ʼ��
		cin.getline(temp,300);
		if(strcmp(temp,"exit")==0) break; //������� 
		//չʾ����ȷ�Ľ��
		if(strcmp(temp,"show more")==0){  
			printf("ans = %.9lf\n",ans);
			continue;
		}
		//�Կո���д���
		for(int i=0;i<strlen(temp);i++){
			if(temp[i]==' ')
				for(int k=i;k<strlen(temp);k++) 
					temp[k] = temp[k+1];
		} 
		if(!precheck(temp)) continue; //Ԥ�������ж� 
		//��'-'ǰû�����ֵ�������м�0���� 
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
		//����û�û������'='�����ַ���ĩβ���'=' 
		int k = strlen(temp);
		temp[k] = '\0';
		if(temp[k-1]!='=') {
			temp[k] = '=';
			temp[k+1] = '\0';
		}
		//�����쳣��� 
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

