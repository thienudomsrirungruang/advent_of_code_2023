
import Data.Char

type Obs = (Int, String)
type Group = [Obs]

parseObs :: [String] -> (Group, [String])
parseObs line = let (num, rest) = (read $ head line, tail line) in
    let (color, rest') = (init $ head rest, tail rest) in
    if last (head rest) == ','
        then let (gs, rest'') = parseObs rest' in ((num, color) : gs, rest'')
        else ([(num, color)], rest')

parseGroups :: [String] -> [Group]
parseGroups line = let (obs, rest) = parseObs line in
    if null rest then [obs] else obs : parseGroups rest

parse :: String -> (Int, [Group])
parse line = let ws = words line in
    let num = read $ init (ws !! 1) in
    let groups = parseGroups $ drop 2 ws in
    (num, groups)

limit :: String -> Int
limit "red" = 12
limit "green" = 13
limit "blue" = 14
limit s = error ("Unknown color " ++ s)

strip :: String -> String
strip xs = reverse $ dropWhile isSpace $ reverse $ dropWhile isSpace xs

calc :: String -> Int
calc line = let (num, groups) = parse (strip line ++ ";") in
    let obs = concat groups in
    let feasible = all (\(n, c) -> n <= limit c) obs in
    if feasible then num else 0
main = interact $ show . sum . map calc . lines
