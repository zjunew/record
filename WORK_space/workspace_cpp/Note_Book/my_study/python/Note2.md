# 正则表达式：
>字符匹配
>>普通字符：普通字符按照字面意义进行匹配，例如匹配字母 "a" 将匹配到文本中的 "a" 字符。  
元字符：元字符具有特殊的含义，例如 \d 匹配任意数字字符，\w 匹配任意字母数字字符，. 匹配任意字符（除了换行符）等。

>量词
>>*：匹配前面的模式零次或多次。  
+：匹配前面的模式一次或多次。  
?：匹配前面的模式零次或一次。  
{n}：匹配前面的模式恰好 n 次。  
{n,}：匹配前面的模式至少 n 次。  
{n,m}：匹配前面的模式至少 n 次且不超过 m 次。  

>字符类
>>[ ]：匹配括号内的任意一个字符。例如，[abc] 匹配字符 "a"、"b" 或 "c"。  
[^ ]：匹配除了括号内的字符以外的任意一个字符。例如，[^abc] 匹配除了字符 "a"、"b" 或 "c" 以外的任意字符。

>边界匹配
>>^：匹配字符串的开头。  
$：匹配字符串的结尾。  
\b：匹配单词边界。  
\B：匹配非单词边界。  

>分组和捕获
>>( )：用于分组和捕获子表达式。  
(?: )：用于分组但不捕获子表达式。  

>特殊字符
>>\：转义字符，用于匹配特殊字符本身。  
.：匹配任意字符（除了换行符）。  
|：用于指定多个模式的选择。  

### 其他点：

* *和 + 限定符都是贪婪的，因为它们会尽可能多的匹配文字，只有在它们的后面加上一个 ? 就可以实现非贪婪或最小匹配。  


## 正则表达式的先行断言(lookahead)和后行断言(lookbehind)  
https://www.runoob.com/w3cnote/reg-lookahead-lookbehind.html

### 修饰符（标记）：
>标记不写在正则表达式里，标记位于表达式之外，格式如下：  
/pattern/flags

>**g** -global 全局匹配  查找字符串中所有的匹配项  
**i** -ignore 不区分大小写  
**m** -multi line  多行匹配  
**s** 特殊字符圆点 . 中包含换行符 \n

### 继承：
```python
#!/usr/bin/python3
 
#类定义
class people:
    #定义基本属性
    name = ''
    age = 0
    #定义私有属性,私有属性在类外部无法直接进行访问
    __weight = 0
    #定义构造方法
    def __init__(self,n,a,w):
        self.name = n
        self.age = a
        self.__weight = w
    def speak(self):
        print("%s 说: 我 %d 岁。" %(self.name,self.age))
 
#单继承示例
class student(people):
    grade = ''
    def __init__(self,n,a,w,g):
        #调用父类的构函
        people.__init__(self,n,a,w)
        self.grade = g
    #覆写父类的方法
    def speak(self):
        print("%s 说: 我 %d 岁了，我在读 %d 年级"%(self.name,self.age,self.grade))
 
#另一个类，多继承之前的准备
class speaker():
    topic = ''
    name = ''
    def __init__(self,n,t):
        self.name = n
        self.topic = t
    def speak(self):
        print("我叫 %s，我是一个演说家，我演讲的主题是 %s"%(self.name,self.topic))
 
#多继承
class sample(speaker,student):
    a =''
    def __init__(self,n,a,w,g,t):
        student.__init__(self,n,a,w,g)
        speaker.__init__(self,n,t)
 
test = sample("Tim",25,80,4,"Python")
test.speak()   #方法名同，默认调用的是在括号中参数位置排前父类的方法
```
* 需要注意圆括号中父类的顺序，若是父类中有相同的方法名，而在子类使用时未指定，python从左至右搜索 即方法在子类中未找到时，从左到右查找父类中是否包含方法。

