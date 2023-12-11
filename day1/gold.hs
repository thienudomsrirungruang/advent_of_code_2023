import Data.Char

digitWords :: [(String, Int)]
digitWords = [("one", 1), ("two", 2), ("three", 3), ("four", 4), ("five", 5),
    ("six", 6), ("seven", 7), ("eight", 8), ("nine", 9)]

isPrefixOf :: String -> String -> Bool
isPrefixOf "" _ = True
isPrefixOf _ "" = False
isPrefixOf (x:xs) (y:ys) = x == y && isPrefixOf xs ys

digits :: String -> [Int]
digits line = if null line then [] else
    let ws = digitWords >>= \(w, i) -> [i | w `isPrefixOf` line] in
    let ds = [digitToInt (head line) | head line `elem` ['0'..'9']] in
    ds ++ ws ++ digits (tail line)

calc :: String -> Int
calc line = let ds = digits line
    in 10 * head ds + last ds
main = interact $ show . sum . map calc . lines
