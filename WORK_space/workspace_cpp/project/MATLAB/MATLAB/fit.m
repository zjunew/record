function [num] = fit(x, y, degree,input ,flag)
    v = ones(length(x), degree + 1);
    for i = 1:degree
        v(:, i+1) = x.^i;
    end
    L = v' *v;
    b = v' *y';
    tar = L\b ;
    tar = rot90(rot90(tar));
    if flag ==1
        disp(rot90(tar))
    end
    num = polyval(tar,input);
end
