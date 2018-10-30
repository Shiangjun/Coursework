third :: [a] -> a
third xs = head(tail(tail(xs)))

thirds :: [a] -> a
thirds xs = xs !! 2

thirdss :: [a] -> a
thirdss (_:_:x:_) = x
