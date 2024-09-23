I = @(x) (60 - x )^2 +(60 - x )*sin(sqrt(x)); 
R = @(x) 10*I(x) + 2* I(x)^(2/3) ;

T = (5) ;
S = (4) ;
C = (3) ;
r = (2) ;

j = 0;
for count = 2 : 2 : 10
    j = j + 1 ;
    x = 0 : 60/count :60 ;
    y = (count+1) ;
    for i = 1 : 1 : count +1 
        y(i) = I(x(i))*R(x(i));
    end
    T(j) = trapezoid(y , count) ;
end

for i = 1 : 4
    S(i) = 4/3 * T(i+1) - 1/3 *T(i);
end

for i = 1 : 3
    C(i) = S(i+1) *16 /15 - S(i) /15 ;
end

for i = 1 : 2 
    r(i) = 64/63 *C(i+1) - 1/63 *C(i);
end

disp(T)
disp(S)
disp(C)
disp(r)