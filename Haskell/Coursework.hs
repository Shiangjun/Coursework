-- 6522056 zy22056 Xiangjun Peng

type Matrix a = [ [a] ]

-- 4 * 2 matrix
eg1 :: Matrix Int
eg1 = [ [1, 3],
        [0, 5],
        [-3, 4],
        [2, 2] ]

-- 2 * 3 matrix
eg2 :: Matrix Int
eg2 = [ [3, 1, 4],
        [-1, 0, 5] ]

-- 0 * 0 matrix, an empty matrix
eg3 :: Matrix Int
eg3 = [ [ ] ]

-- 2 * 1 matrix
eg4 :: Matrix Int
eg4 = [ [2],
        [3] ]

eg5 :: Matrix Double
eg5 = [ [6.2, 4.3, 7.4, -7.3],
        [9.3, 1.2, 0.4, -6.2] ]

-- Function empty
empty :: Matrix mat ->  Bool
empty mat = if (length(head mat) == 0) then True 
            else False

-- Function rowCount
rowCount :: Matrix mat -> Int
rowCount mat = if (length(mat) == 0) then 0
               else 1 + rowCount(tail(mat))

-- Function columnCount
columnCount :: Matrix mat -> Int
columnCount mat = if (length(head(mat)) == 0) then 0
                  else 1 + columnCount(map tail mat)

-- Function element'
element' :: Matrix mat -> Int -> Int -> mat
element' mat x y = head(drop y (head (drop x mat)))

-- Function element
element :: Matrix a -> Int -> Int -> Maybe a
element a x y = if (or((rowCount(a) <= x), (columnCount(a) <= y))) then Nothing
                else Just(element' a x y)

-- Function elementEth

data MatrixErr = NegIndex     -- represents an index being negative
               | RowTooLarge  -- represents a row index being too large for the matrix
               | ColTooLarge  -- represents a column index being too large for the matrix
               deriving Show

elementEth :: Matrix a -> Int -> Int -> Either MatrixErr a
elementEth a x y = if (or(x < 0, y < 0)) then
                       Left NegIndex
                     else if (rowCount(a) < x+1) then
                            Left RowTooLarge
                          else if (columnCount(a) < y+1) then
                                 Left ColTooLarge
                   else Right (element' a x y)

-- Function identity
flist :: Int -> [Int]
flist x  = if (x == 1) then [0]
           else [0] ++ flist (x-1)

fnest :: Int -> [[Int]]
fnest x  = if (x == 0) then [[]]
           else [flist (x)] ++ fnest (x-1) 

identityHelper :: Int -> [[Int]] -> [[Int]] -> Matrix Int
identityHelper x a b = if (x <= 0) then [a !! 0 ++ [1] ++ b !! 0]
                       else [a !! x ++ [1] ++ b !! x] ++ identityHelper (x-1) a b

identity :: Int -> Maybe (Matrix Int)
identity x = if (x <= 0) then Nothing
             else Just(identityHelper (x-1) a b)
                       where { 
                         a = fnest(x-1);
                         b = reverse(a)
                       };

-- Function addMat
--addMat :: Num a => Matrix mat -> Matrix mat -> Maybe (Matrix mat) 
--addMat x y = if (or((columnCount(x) != columnCount(y)),(rowCount(x) != rowCount(y)))) then Nothing
--             else Just(eg1)

-- Function mapMat
mapMat :: (a -> b) -> Matrix a -> Matrix b
mapMat x y = map (map x) y

-- Function compress
compress :: Num a => Matrix a -> Matrix a
compress [[]] = [[]]
compress mat = if (length(tail(mat)) == 0) then [[head(map sum mat)]]
               else [[head(map sum mat)]] ++ compress(tail(mat))

