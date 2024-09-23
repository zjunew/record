format long;
F=@(x) 90* tand(x)- 9 * 9.81 / 2 / cosd(x)^2+ 0.8;
x1=40;
x4=50;
count1=0;
count2=0;
err= 1e-7;
G1=@(x) atand( (9 * 9.81 / 2 / cosd(x)^2 - 0.8) /90 );
G2=@(x) 90* tand(x)- 9 * 9.81 / 2 / cosd(x)^2+ 0.8 + x;
while abs( G1(x1) - x1 )>err
    x1 = G1(x1);
    count1 = count1 + 1 ;
end
s1="循环了：  "+num2str(count1)+"次    结果为：  "+num2str(G1(x1),10);
disp(s1)
while abs(G2(x4)-x4)>err
    x4 = G2(x4);
    count2 = count2 + 1 ;
end
s1="循环了：  "+num2str(count2)+"次    结果为：  "+num2str(G2(x4),10);
disp(s1)