function [L] = fit(x,y, n,t)

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

