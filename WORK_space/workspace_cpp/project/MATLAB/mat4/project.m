x = 0 : 8 : 40;
y = [14.621 11.843 9.870 8.418 7.305 6.413];
size= 4;
%plot(x,y,"r*")
%hold on

fit(x,y,5,27);
%xi = 0 : 0.1 :40;
%yi=zeros(401);
%for i = 1:401
 %   yi(i)=interpolation(x,y,size,xi(i));
%end
%plot(xi,yi,"-b")
for i = 1:5
    s=i+" 次拟合：";
    disp(s);
    disp(interpolation(x,y,i,27))
end
%interpolation(x,y,size,27)
