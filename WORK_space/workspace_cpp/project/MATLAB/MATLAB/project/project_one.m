warning off
%上方
x1 = [0 13.5 30.9 42.5 60.8 69.7 83.6 91.8 101.4] ;
y1 = [0 28.7 33.9 28.5 28.1 5.6 -3.2 -15.2 -23.9] ;
%下方
x2 = [0 8.4 16 18.2 26.8 41.9 71.8 90.8 100.7 101.4] ;
y2 = [0 -9.6 -14.3 -23.1 -23.6 -32.1 -30.4 -41.7 -33.7 -23.9] ; 
%突出部分
x3 = [0 14.5 25.5] ;
y3 = [0 1.8 5.6] ;
x4 = [13.5 13.7 25.5] ;
y4 = [28.7 18.8 5.6] ;
plot(x1,y1,"*r")
hold on
plot(x2,y2, "*r")
plot(x3,y3,"*r")
plot(x4,y4,"*r")

count = 4 ;
disp("第一段曲线")
x1h = [0 13.5 30.9 42.5] ;
y1h = [0 28.7 33.9 28.5] ;
x = 0 :0.1 : 42 ;
y = zeros(421);
for i = 1 : 421
     y(i) = fit(x1h,y1h,count,x(i) , 0) ;
end
plot(x,y,"b-")
fit(x1h,y1h,count,x(i) , 1);

x2h = [30.9 42.5 60.8 69.7 ] ;
y2h = [33.9 28.5 28.1 5.6 ] ;
x = 42 :0.1 : 70 ;
y = zeros(281);
for i = 1 : 281
    y(i) = fit(x2h,y2h,count,x(i) , 0) ;
end
fit(x2h,y2h,count,x(i) , 1);
plot(x,y,"b-")

x3h = [69.7 83.6 91.8 101.4] ;
y3h = [5.6 -3.2 -15.2 -23.9] ;
x = 70 :0.1 : 102 ;
y = zeros(321);
for i = 1 : 321
     y(i) = fit(x3h,y3h,count,x(i) , 0) ;
end
fit(x3h,y3h,count,x(i) , 1);
plot(x,y,"b-")


disp("第二段曲线")
x1h = [0 8.4 16 18.2] ;
y1h = [0 -9.6 -14.3 -23.1] ;
x = 0 :0.1 : 18 ;
y = zeros(181);
for i = 1 : 181
    y(i) = fit(x1h,y1h,count,x(i) , 0) ;
end
fit(x1h,y1h,count,x(i) , 1);
plot(x,y,"b-")

x2h = [18.2 26.8 41.9 71.8] ;
y2h = [-23.1 -23.6 -32.1 -30.4] ;
x = 18 :0.1 : 72 ;
y = zeros(541);
for i = 1 : 541
    y(i) = fit(x2h,y2h,count,x(i) , 0) ;
end
fit(x2h,y2h,count,x(i) , 1);
plot(x,y,"b-")

x3h = [41.9 71.8 90.8 100.7 101.4] ;
y3h = [-23.6 -30.4 -41.7 -33.7 -23.9] ;
x = 72 :0.1 : 102 ;
y = zeros(301);
for i = 1 : 301
    y(i) = fit(x3h,y3h,count-1,x(i) , 0) ;
end
fit(x3h,y3h,count-1,x(i) , 1);
plot(x,y,"b-")

disp("第三段曲线（割补）")
x = 0 : 0.1 :25.5 ;
y = zeros (256) ;
for i = 1 : 256
    y(i) = fit(x3,y3,2,x(i) , 0) ;
end
fit(x3,y3,2,x(i) , 1);
plot(x,y,"b-")

x = 13.5 : 0.1 :25.5 ;
y = zeros (121) ;
for i = 1 : 121
    y(i) = fit(x4,y4,1,x(i) , 0) ;
end
 fit(x4,y4,1,x(i) , 1);
plot(x,y,"b-")