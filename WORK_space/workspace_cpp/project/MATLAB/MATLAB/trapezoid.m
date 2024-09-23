function [out] = trapezoid(y , count , h)
    sum = 0 ;
    for i = 2 : count
        sum = sum + 2 * y(i) ; 
    end
    out = h*(sum + y(1) + y(count+1)) / 2 / count ;
    
end
