import Data.List
import Text.Printf

-- Thank you, Funkschy!

main :: IO ()
main = do
  filecontent <- readFile "input.txt"
  let filelines = lines filecontent
  let pt1 = sum $ map (length . nub . sort) $ words $ concatMap (\c -> if c == "" then " " else c) filelines
  printf "%s %d" "pt.1:" pt1
