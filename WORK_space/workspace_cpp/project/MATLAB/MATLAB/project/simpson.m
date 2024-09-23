function [out] = simpson(y , count ,h)
    h=h/count ;
    sum = 0;
    for i = 2 : 2 :count
        sum = sum + 4 * y(i) + 2* y(i+1);
    end
    sum = ( sum + y(1) - y(count+1) ) * h /3 ;
    out = sum ;

end
