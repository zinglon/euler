import Data.List
digits :: Int -> [Int]
digits 0 = []
digits x = [x `mod` 10] ++ digits (x `div` 10)

unique :: Eq a => [a] -> Int -> [[a]]
unique _ 0 = []
unique xs 1 = [[x] | x <- xs]
unique xs c = concat [map ([x] ++) (unique (delete x xs) (c-1)) | x <- xs]

things = 
  -- a * bcde = fghi
  [(x,y,x*y) | (x,y) <- [(a, 1000*b + 100*c + 10*d + e) | [a,b,c,d,e] <- unique [1..9] 5, a*b < 10], x*y < 10000, not $ elem 0 $ digits (x*y), 9 == (length $ nub $ (digits x) ++ (digits y) ++ (digits $ x*y))]
  ++
  -- ab * cde = fghi
  [(x,y,x*y) | (x,y) <- [(10*a + b, 100*c + 10*d + e) | [a,b,c,d,e] <- unique [1..9] 5], x*y < 10000, not $ elem 0 $ digits (x*y), 9 == (length $ nub $ (digits x) ++ (digits y) ++ (digits $ x*y))]

answer = sum $ nub [z | (x,y,z) <- things]