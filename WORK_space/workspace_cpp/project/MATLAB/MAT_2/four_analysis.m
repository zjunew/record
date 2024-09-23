format long;
F=@(x) 90* tand(x)- 9 * 9.81 / 2 / cosd(x)^2+ 0.8;
x1=35;
x2=40;
x3=50;
x4=52;
count1=0;
count2=0;
G=@(x) 90/cosd(x)^2 - 9 * 9.81 *sind(x)  / cosd(x)^3;

while count1<10
   
    x1 = x1 - F(x1)/G(x1);
    count1 = count1+1 ;
    s1="循环了：  "+num2str(count1)+"次    结果为：  "+num2str(x1,10)...
        +"F(x1)为： "+num2str(F(x1)) +"   G(x1)为: "+ num2str(G(x1))   ;
    disp(s1)
end

while count2<10
    
    x4 = x4 - F(x4)/G(x4);
    count2 = count2 + 1;
    s2="循环了：  "+num2str(count2)+"次    结果为：  "+num2str(x4,11)...
            +"F(x4)为： "+num2str(F(x4)) +"   G(x4)为: "+ num2str(G(x4)) ;
    disp(s2)
end

