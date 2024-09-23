x = 0 : 8 : 40;
y = [14.621 11.843 9.870 8.418 7.305 6.413];
Y = log(y) ;
size= 1;
plot(x,y,"r*")
hold on

xi = 0 : 0.1 :40;
yi=zeros(401);
for i = 1:401
    yi(i)=interpolation(x,Y,size,xi(i));
    yi(i) = exp(yi(i));
end
plot(xi,yi,"-b")
for i = 1:5
    s=i+" 次拟合：";
    disp(s);
    disp(exp(interpolation(x,Y,i,27)))
end