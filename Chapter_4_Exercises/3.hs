safetail :: [a] -> [a]
safetail xs = if null xs then [] else tail xs

safetails :: [a] -> [a]
safetails xs | null xs   = []
             | otherwise = tail xs

safetailss :: [a] -> [a]
safetailss [] = []
safetailss (_:xs) = xs
