```css
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>菜鸟教程</title>
<style>
body {
	background-color:#d0e4fe;
}
h1 {
	color:orange;
	text-align:center;
}
p {
	font-family:"Times New Roman";
	font-size:20px;
}
</style>
</head>

<body>

<h1>CSS 实例!</h1>
<p>这是一个段落。</p>

</body>
</html>
```
CSS 规则由两个主要的部分构成：  
选择器，以及一条或多条声明:
>id 选择器可以为标有特定 id 的 HTML 元素指定特定的样式。

>HTML元素以id属性来设置id选择器,CSS 中 id 选择器以 "#" 来定义。

>class例子：
```css
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8"> 
<title>菜鸟教程(runoob.com)</title> 
<style>
.center
{
	text-align:center;
}
</style>
</head>

<body>
<h1 class="center">标题居中</h1>
<p class="center">段落居中。</p> 
</body>
</html>
```
### 插入样式表的方法有三种:
>
* 外部：  
每个页面使用 <link> 标签链接到样式表。 <link> 标签在（文档的）头部：
```css
<head>
<link rel="stylesheet" type="text/css" href="mystyle.css">
</head>
```
浏览器会从文件 mystyle.css 中读到样式声明，并根据它来格式文档。  

