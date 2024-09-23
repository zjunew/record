format long;
F=@(x) 90* tand(x)- 9 * 9.81 / 2 / cosd(x)^2+ 0.8;
x1=35;
x2=40;
x3=50;
x4=55;
count1=0;
count2=0;
err = 1e-7;
help = 0;
xr1=1;
xr2=1;
while abs(help-xr1) > err
    xr1=x2-F(x2) * ( x1 - x2 ) / (F(x1) - F(x2));
    if (F(xr1) == 0)
        break;
    end
    if F(xr1)*F(x2)<0
        help = x1;
        x1 = xr1;
    else
        help = x2;
        x2 = xr1;
    end
    count1 = count1 + 1 ;
end
s1="循环了：  "+num2str(count1)+"次    结果为：  "+num2str(xr1,10);
disp(s1)
help=0;
while abs(help - xr2)>err
    xr2=x4-F(x4) * ( x3 - x4 ) / (F(x3) - F(x4));
    if (F(xr2) == 0)
        break;
    end
    if F(xr2)*F(x4)<0
        help = x3;
        x3 = xr2;
    else
        help = x4;
        x4 = xr2;
    end
    count2 = count2 + 1 ;
end
s2="循环了：  "+num2str(count2)+"次    结果为：  "+num2str(xr2,10);
disp(s2)