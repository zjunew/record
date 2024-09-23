function [X] = Gaussian_elimination(inputArg1,inputArg2,n)
%GAUSS 此处显示有关此函数的摘要
%   此处显示详细说明
    C = inputArg1;
    b = inputArg2;
    A = [C b];
    size = n+1;
    last = size+1;
    X = zeros(n+1,1);
    for k = 2 : size
        for j = k:size
            A(j , :) = A(j, :) - A(k-1, :) * (A(j, k-1) / A(k-1, k-1));
            
        end
    end
    
    X(size) = A(size,last) / A(size,size);
    for i = size : -1 : 1 
        sum = 0;
        for j = i+1 : size 
            sum = sum + A(i,j) * X(j);
        end
        A(i,last) = A(i,last) - sum;
        X(i) = A(i,last) / A(i,i);
    end
    disp("Y out=");
    disp(X(size-1));
    disp("X out=");
    disp(X(1)*4);
end

