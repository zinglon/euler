digits :: Int -> [Int]
digits 0 = []
digits x = [x `mod` 10] ++ digits (x `div` 10)

factorial :: Integral a => a -> a
factorial x = product [1..x]

answer = sum $ filter (\x -> x ==  (sum . (map factorial) . digits) x) [10..2000000]