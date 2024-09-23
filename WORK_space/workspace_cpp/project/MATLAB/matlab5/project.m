I = @(x) (60 - x )^2 +(60 - x )*sin(sqrt(x)); 
R = @(x) 10*I(x) + 2* I(x)^(2/3) ;

count = 50;
x = 0 : 60/count :60 ;
y = (count+1) ;
for i = 1 : 1 : count +1 
    y(i) = I(x(i))*R(x(i));
end

plot(x,y,"r-")
disp("当分割区间数为："+ count)
disp("trapezoid的结果：")
disp(trapezoid(y , count ));

disp("simpson的结果：")
disp(simpson(y , count ) );

disp("Romberg的结果：")
Romberg();

for tar = [5 ,10 , 50 ,100 ]
    disp("Gauss的结果：")
    disp("当分割区间数为："+ tar )
    disp(Gauss(tar))
end