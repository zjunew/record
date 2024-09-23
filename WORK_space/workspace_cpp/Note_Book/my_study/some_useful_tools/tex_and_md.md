## 基本用法  
* 括号
>括号可以直接用(..)输入，但是需要注意的是，有时候括号内的内容高度较大，需要改用\left(..\right)。例如\left(1+\dfrac{1}{n}\right)^n，效果

$\left(1+\dfrac{1}{n}\right)^n$

>输入大括号{}时需要用\{..\}，其中\起到了转义作用。
$$
f(x)=\begin{cases}
    x, & x>0, \\
    -x, & x\leq 0.
\end{cases}
$$

* 对于英文，可以用book、article和beamer；
* 对于中文，可以用ctexbook、ctexart和ctexbeamer，这些类型自带了对中文的支持。
* 一般也可以在\documentclass处设置基本参数，笔者通常设置默认字体大小为12pt，纸张大小为A4，单面打印。需要将第一行的内容替换为：
>\documentclass[12pt,a4paper,oneside]{ctexart}

* 加载宏包的代码是\usepackage{}。本份教程中，与数学公式与定理环境相关的宏包为amsmath、amsthm、amssymb，用于插入图片的宏包为graphicx

1. \newpaper  另起一页
2. 加宽  \textbf 

 * **图片**  
	```
	\begin{figure}[htbp]  
		\centering  
		\includegraphics[width=8cm]{图片.jpg}  
		\caption{图片标题}  
	\end{figure}
	```
* [htbp]的作用是自动选择插入图片的最优位置，\centering设置让图片居中，[width=8cm]设置了图片的宽度为8cm，\caption{}用于设置图片的标题。

#### 页面
* 一般情况下，LaTeX默认的页边距很大，为了让每一页显示的内容更多一些，我们可以使用geometry宏包，并在导言区加入以下代码：
```
\usepackage{geometry}
\geometry{left=2.54cm, right=2.54cm, top=3.18cm, bottom=3.18cm}
```
>设置字距  
\linespread{1.5}

如果需要的话，你可能想将你的文档分为章（Chatpers）、节（Sections）和小节（Subsections）。下列分节命令适用于 **article** 类型的文档：

-   `\section{...}`
-   `\subsection{...}`
-   `\subsubsection{...}`
-   `\paragraph{...}`
-   `\subparagraph{...}`

花括号内的文本表示章节的标题。对于 **report** 和 **book** 类型的文档我们还支持 `\chapter{...}` 的命令。

\textit{words in italics}
\textsl{words slanted}
\textsc{words in smallcaps}
\textbf{words in bold}
\texttt{words in teletype}
\textsf{sans serif words}
\textrm{roman words}
\underline{underlined words}
