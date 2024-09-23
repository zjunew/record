function [x] = Jacobi(A , b ,n)
%GAUSS_SEIDEL 此处显示有关此函数的摘要
%   此处显示详细说明
    count = 0;
    x0 = zeros(n+1,1);
    D = diag(diag(A));
    L = -tril(A,-1);
    U = -triu(A,1);
    G = (D-L)\U;
    f = (D-L)\b;
    x = G*x0+f;
    eps = 1e-8;
    while norm(x-x0) > eps &&count <200
        x0 = x;
        x = G* x0 + f ;
        count = count+1;
    end
    disp("迭代次数：")
    disp(count);
    disp("Y out=");
    disp(x(n));
    disp("X out=");
    disp(x(1)*4);
end

