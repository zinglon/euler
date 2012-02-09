primes = [2] ++ [x | x <- [3,5..], not $ any (divides x) (candidates x)]
         where candidates x = takeWhile ((x >=).sqr) primes
               sqr x = x*x
               divides x y = mod x y == 0
