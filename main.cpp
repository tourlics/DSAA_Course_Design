#include <iostream>
#include "MyStack.h"
#include "calculate.h"
#include "precheck.h"
using namespace std;
int main() {
	cout<<"---------Welcome!---------"<<endl;
	cout<<"----Input exit to exit----"<<endl; 
	double ans; //最终计算结果 
	while(1){
		char temp[300]; //存储读入的字符串，用于预处理等操作 
		memset(temp,0,300);  
		data.clear();
		sign.clear(); //初始化
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
