import Numeric (showIntAtBase)

showBinary :: (Integral a, Show a) => a -> String
showBinary = ($"") . (showIntAtBase 2 (head.show))

palindrome s = s == (reverse s)

answer = foldl1 (+) $ filter (\x -> (palindrome $ show x) && (palindrome $ showBinary x)) [1,3..1000000]
