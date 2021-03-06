# 编译大作业文档

黄子懿 

李在弦 

肖岚 

## 简介

这是一个简单的C2Python代码转换器，使用java语言和ANTLR工具完成。

## 内容清单

/src/main:

​	/MyCompiler.java ：入口类，语义处理器

​	/MyException.java ：自定义的语法错误类

​	/CCompiler.g4：ANTLR语法/词法规则文件

/src/gen:ANTLR语法工具生成文件

## 使用方法

运行jar程序，输入文件名（不包括.c后缀名），会生成同名文件

## 实现的语法特性

- 一般赋值、定义、判断语句
- for,if-else-elseif,while控制语句
- 函数定义
- 变量名检查（变量重定义/未定义不允许）
- struct结构体定义，结构体名/属性名检查
- 入口函数检查
- 一些基本的c函数转换

## 实现方法

借助ANTLR语法工具，实现了语法树的建立

![语法树](C:\Users\Administrator\Desktop\语法树.png)

图一：语法树（部分）

具体语法规则可见CCompiler.g4文件

在ANTLR语法树的基础上，使用ANTLR提供的visitor工具访问语法树

```java
	try {
            ANTLRInputStream input = new ANTLRInputStream(c);
            CCompilerLexer lexer = new CCompilerLexer(input);
            CommonTokenStream tokens = new CommonTokenStream(lexer);
            CCompilerParser parser = new CCompilerParser(tokens);
            ParseTree tree = parser.prog();

            MyCompiler compiler = new MyCompiler(py);
            compiler.visit(tree);
        } catch (RecognitionException e ){
            System.out.println(name + ".c ilegal");
            e.printStackTrace();
            return ;
        }
```

#### 一些具体的功能实现

- 类型与声明：python是弱类型的语言，在变量/函数定义时我们选择不定义变量的类型，而且在python中不存在变量的声明，我们选择当被声明的变量是一个数组时，使用简单初始化来代替声明，在此后的使用中就可以直接使用Index对数组内容进行访问
- 指针：python中没有指针的概念（事实上，几乎都是指针），无论是int还是int*，我们选择一视同仁，这样选择的弊处是无法通过指针来构造指向相同值的量，但这是python的语法特点，无法避免
- 字符串，在c语言中字符串是数组的一个特例，但在python中字符串是个不可变量，我们使用字符串
- 变量、属性检查：使用var_check、var_def、type_check进行（MyCompiler.java:84~155)，维护Map来进行完成
- for:python中的for和c风格不太相同，使用while替换for，做了一个特殊处理：当遇到continue/break的时候，可能会错误的跳过for的第三个语句，所以我们维护一个操作栈来维护当前循环的递增变量
- ++等不同的操作符及函数：交换功能相似的操作符函数
- 预处理：忽略

#### 一些还可以进行的工作

- 一句定义多个变量
- 函数检查
- 预处理
- 更多语法功能





