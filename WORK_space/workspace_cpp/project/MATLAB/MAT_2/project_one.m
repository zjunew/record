format long;
F=@(x) 90* tand(x)- 9 * 9.81 / 2 / cosd(x)^2+ 0.8;
x1=35;
x2=40;
x3=50;
x4=55;
count1=0;
count2=0;
err=1e-7;
xm1=0;
while abs(m1-xm1)>err 
    m1 = (x1 + x2) / 2 ;
    if(F(m1)==0)
        break
    end
    if(F(m1) * F(x1) < 0)
        xm1=x2;
        x2=m1;
        
    else
        xm1=x1;
        x1=m1;
    end
    count1=count1+1;
end
s1="循环了：  "+num2str(count1)+"次    结果为：  "+num2str(m1,10);
disp(s1)
xm2=0;
while abs(m2-xm2)>err 
    m2 = (x3 + x4) / 2 ;
    if(F(m2)==0)
        break
    end
    if(F(m2) * F(x3) < 0)
        xm2=x4;
        x4=m2;
    else
        xm2=x3;
        x3=m2;
    end
    count2=count2+1;
end
s2="循环了：  "+num2str(count2)+"次    结果为：  "+num2str(m2,10);
disp(s2)