function [L] = one(x,y, n,t)
%ONE 此处显示有关此函数的摘要
%   此处显示详细说明
L = 0;

for i = 1 : 1 : n+1
    temp = y(i) ;
    for j = 1 : 1 : n+1
        if i~=j
            temp = temp * (t - x(j)) / (x(i) - x(j)) ;
        end
    end
    L = L + temp ;
end

end

