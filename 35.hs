primes = [2] ++ [x | x <- [3,5..], not $ any (divides x) (candidates x)]
         where candidates x = takeWhile ((x >=).sqr) primes
               sqr x = x*x
               divides x y = mod x y == 0

-- this would certainly be faster with a sieve, but what a pain
primesLess x = takeWhile (<=x) primes
                  
rotate l = tail l ++ [head l]

circular p = (not $ any (\c -> elem c ['0','2','4','6','8']) pstr)
             && all (\x -> (==x) $ last $ primesLess x) (take (length pstr - 1) $ drop 1 $ map read $ iterate rotate pstr) 
             where pstr = show p

answer = (1+) $ length $ filter circular (primesLess 1000000)