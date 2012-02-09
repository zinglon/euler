primes = [2] ++ filter (\x -> not $ any (divides x) (candidates x)) [3,5..]
         where sqr x = x*x                 
               candidates x = takeWhile ((<=x).sqr) primes
               divides x y = mod x y == 0


squares = map (\x -> 2*x*x) [0..]

primesLess x = takeWhile (<=x) primes
squaresLess x = takeWhile (<=x) squares

answer = head $ [x | x <- [9,11..], not $ any (\p -> elem (x-p) (squaresLess (x-p))) (primesLess x)]