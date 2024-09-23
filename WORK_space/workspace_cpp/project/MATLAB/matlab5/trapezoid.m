function [out] = trapezoid(y,count)
    sum = 0 ;
    for i = 2 : count
        sum = sum + 2 * y(i) ; 
    end
    out = 60 *(sum + y(1) + y(count+1)) / 2 / count ;
    out = out /60 ;
end
