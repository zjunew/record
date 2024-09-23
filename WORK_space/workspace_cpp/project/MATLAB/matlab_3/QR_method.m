function [x] = QR_method(A,b,n)
%LU_METHOD 此处显示有关此函数的摘要
%   此处显示详细说明
    [Q, R] = qr(A);
    y = Q' * b;
    x = R \ y;
   % disp(x)
    disp("Y out=");
    disp(x(n));
    disp("X out=");
    disp(x(1)*4);
end
