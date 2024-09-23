format long
F= @(x) x / ( 1 + x^4) ;
n = 10 ;
step = 10 / (n) ;
start  = -5;

x = -5: step : 5 ;
y=(n+1) ;

t = 5;
for i = 1 : 1 : n+1
    y(i)=F(x(i));
end

for i = 1 : 1 : n
    %k =( y(i) - y(i+1)) /( x(i) - x(i-1));
    %b = y(i) - k *x(i);
     plot([x(i),x(i+1)],[y(i),y(i+1)],"b-")
     hold on
end
xi = -5 : 0.05 : 5;
yi =(201);
for i = 1 : 1 : 201
    yi(i)=F(xi(i));
end
plot(xi,yi,"r-")
xlabel("x轴")
ylabel("Y轴")