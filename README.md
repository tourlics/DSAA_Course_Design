* 本项目为2019年11月数据结构与算法设计课程设计源代码，主要实现了一个多功能计算器  
* 算法步骤详见[带括号表达式求值](https://www.cnblogs.com/icodes8238/p/12243275.html)   
* 版本说明：  
  * suffix:算法为将中缀表达式转成后缀表达式（还有bug）  
  除上面版本外，其它版本均为用双栈实现  
  * version 1 : 注释部分保留了边读入边处理  
  * version 2 : 全部读完以后再进行处理---optimised on Nov.7th  
	  对除数为0的情况抛出异常，使程序不会中断---optimised on Nov.9th  
	  对用户输入的空格进行预处理、输出精度最多可达到11位（由用户选择）---optimised on Nov.10th  
	  识别了字符串开头和末尾是符号问题、解决了用户输入中文字符时程序自动中断问题-optimised on Nov.11th  
	  加了注释、解决模数为0的问题、解决了一些细节问题---optimised on Nov.11th（Recommend）  
  * version 3 : 自己写栈MyStack代替STL中的栈（增加了clear功能）  
	  但是主题代码部分为了弥补自己写的栈鲁棒性不强对data.push(aRb())做了更改  
	  ----optimised on Nov.9th  
  version-submit : 实现文件联编，代码结构层次更加清晰   
