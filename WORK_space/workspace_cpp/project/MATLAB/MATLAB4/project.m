format long
F= @(x) x / ( 1 + x^4) ;
n = 10 ;
step = 10 / (n) ;
start  = -5;

x = -5: step : 5 ;
y=(n+1) ;


for i = 1 : 1 : n+1
    y(i)=F(x(i));
end

L = 0;



x0 = -5 : 0.05 : 5;
y0 =(201);
for i = 1 : 1 : 201
    y0(i)=F(x0(i));
end
plot(x0,y0,"b-")
hold on 
xlabel("x轴")
ylabel("Y轴")

xi = -5 : 0.05 : 5;
yi =(201);
for i = 1 : 1 : 201
    yi(i)=one(x,y,n,xi(i));
end
plot(xi,yi,"r-")