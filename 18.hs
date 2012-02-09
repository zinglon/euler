import Data.List
--entering the actual problem data is left as an exercise for the reader
rows = [[3],[7, 4],[2, 4, 6],[8, 5, 9, 3]]
answer = foldr1 (\r1 r2 -> zipWith (+) r1 (zipWith max r2 (tail r2))) rows