A = [1 2 4 8 8; 1 3 9 27 27; 1 4 16 64 64; 1 5 25 124.8 125];
X = [0 0  0  0];
x = [0 0 0 1];
b=[8 27 64 125];

B = [1 2 4 8 ; 1 3 9 27 ; 1 4 16 64 ; 1 5 25 124.8 ];
delB=[0 0 0 0 ;0 0 0 0 ;0 0 0 0 ; 0 0 0 0.2];
size = 4 ;
last = 5;
for k = 2 : size
    for j = k:size
        A(j , :) = A(j, :) - A(k-1, :) * (A(j, k-1) / A(k-1, k-1));
        
    end
end
s="原始高斯消去算法程序将矩阵变为：";
disp(s);
disp(A);

X(size) = A(size,last) / A(size,size);
for i = size : -1 : 1 
    sum = 0;
    for j = i+1 : size 
        sum = sum + A(i,j) * X(j);
    end
    A(i,last) = A(i,last) - sum;
    X(i) = A(i,last) / A(i,i);
end

s="得到的解向量为：";
disp(s);
disp(X);
s="得到的cond(A)为：";
disp(s);
disp(cond(B));
s="A^-1的范数norm(A^-1):";
disp(s);

disp(norm(inv(B)));

s="b的范数norm(B):";
disp(s);
disp(norm(b,2));
s="误差的范数";
disp(s);
disp(norm(X-x));