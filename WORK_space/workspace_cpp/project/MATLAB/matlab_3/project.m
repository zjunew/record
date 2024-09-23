n = 20;
A=zeros( n+1 ,n+1 ) ;
b=zeros(n+1 , 1);
A(1,1) = 3.4 ;
A(1,2) = -2.4 ;
b(1,1) = 0.9 ;

for i =  2 : 1 : n
    A(i,i-1) = 1 ;
    A(i,i) = -3.4 ;
    A(i,i+1) = 2.4 ;
end
A(n,n) = 4;
A(n,n+1) =-1;
A(n+1 , n-1) =-5;
A(n+1,n) = 5;
A(n+1,n+1)  =3 ;
%disp(A);
%disp(b);
disp("Gaussian_elimination:");
Gaussian_elimination( A, b ,n);
disp("QR_method:");
QR_method(A,b,n);
disp("Jacobi:")
Jacobi(A,b,n);