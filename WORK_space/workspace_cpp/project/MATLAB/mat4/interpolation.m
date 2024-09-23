function [num] = interpolation(x, y, degree,input)
    v = ones(length(x), degree + 1);
    for i = 1:degree
        v(:, i+1) = x.^i;
    end
    
    L = v' *v;
   
    b = v' *y';
    tar = L\b ;
    tar = rot90(rot90(tar));
    num = polyval(tar,input);
end
