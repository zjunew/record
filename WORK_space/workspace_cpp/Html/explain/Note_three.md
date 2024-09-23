# Html的链接使用：
>
    <!DOCTYPE html>
    <html>
    <head> 
    <meta charset="utf-8"> 
    <title>菜鸟教程</title> 
    </head>
    <body>

    <a href="https://www.runoob.com/" target="_blank">访问菜鸟教程!</a>

    <p>如果你将 target 属性设置为 &quot;_blank&quot;, 链接将在新窗口打开。</p>

    </body>
    </html>

要改变文字的位置，可以通过修改CSS样式来实现。

    a {
    padding: 10px 20px;
    background-color: #1aaefe;
    color: white;
    text-decoration: none;
    border-radius: 5px;
    display: block; /* 或者 inline-block */
    position: absolute;
    top: 50%;
    left: 50%;
    transform: translate(-50%, -50%);
    }

    <p>创建图片链接:
    <a href="http://www.runoob.com/html/html-tutorial.html">
    <img  border="10" src="smiley.gif" alt="HTML 教程" width="32" height="32"></a></p>

创建了两个 .link-container 容器来包裹链接，并使用绝对定位 (position: absolute;)
将它们放置在不同的位置。通过调整 .link-container:nth-child(1) 和 .link-container:nth-child(2) 
的样式，可以控制它们的垂直位置