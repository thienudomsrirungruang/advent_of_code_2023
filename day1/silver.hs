import Data.Char

calc :: String -> Int
calc line = let ds = filter (`elem` ['0'..'9']) line
    in 10 * digitToInt (head ds) + digitToInt (last ds)

main = interact $ show . sum . map calc . lines
