import Data.List
import Text.Printf

-- Thank you, rexim!
tail' :: [a] -> [a]
tail' (_:xs) = xs
tail' [] = []

splitOn :: Eq a => a -> [a] -> [[a]]
splitOn _ [] = []
splitOn d s = x:splitOn d (tail' s')
  where (x, s') = span (/= d) s
--

-- Thank you, Funkschy!
main :: IO ()
main = do
  filecontent <- readFile "input.txt"
  let filelines = lines filecontent
  let pt1 = sum $ map (length . nub . sort) $ words $ concatMap (\c -> if c == "" then " " else c) filelines
  let pt2 = sum $ map (length . foldl1 intersect) $ splitOn "" filelines
  printf "pt.1: %d\n" pt1
  printf "pt.2: %d" pt2
--
