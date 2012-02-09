answer = last $ foldr (\c w -> let w' = take c w ++ zipWith (+) w' (drop c w) in w')
                      ([1] ++ replicate 200 0)
                      [1,2,5,10,20,50,100,200]