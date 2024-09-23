format long;
F=@(x) 90* tand(x)- 9 * 9.81 / 2 / cosd(x)^2+ 0.8;
x1=35;
x2=40;
x3=50;
x4=55;
count1=0;
count2=0;
err= 1e-7;
help = 0;
while abs(x2-help) > err
    help=x2;
    x2 = x1 - F(x1) * (x1 - x2) /(F(x1) - F(x2));
    count1 = count1 + 1 ; 
end
s1="循环了：  "+num2str(count1)+"次    结果为：  "+num2str(x2,10);
disp(s1)
help = 0 ;
while abs(x4 - help) > err
    help =x4;
    x4 = x3 - F(x3) * (x3 - x4) /(F(x3) - F(x4));
    count2 = count2 + 1 ; 
end
s2="循环了：  "+num2str(count2)+"次    结果为：  "+num2str(x4,10);
disp(s2)