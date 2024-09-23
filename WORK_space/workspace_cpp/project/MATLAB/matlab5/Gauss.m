function [out] = Gauss(tar)
    I = @(x) (60 - x )^2 +(60 - x )*sin(sqrt(x)); 
    R = @(x) 10*I(x) + 2* I(x)^(2/3) ;

    x = 0 : 60 / tar : 60 ;
    
    
    sum = 0 ;

    for i  = 1 : 1 : tar 
        temp = ( (x(i)+x(i+1) ) + (x(i+1)-x(i))*(-sqrt(3)/3))/2 ;
        sum = sum + I(temp)*R(temp) ;
        temp = ( (x(i)+x(i+1) ) + (x(i+1)-x(i))*(sqrt(3)/3))/2 ;
        sum = sum + I(temp)*R(temp) ;
    end

    out = sum /tar *30;
    out = out /60 ;
end

