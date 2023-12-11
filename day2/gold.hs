
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

strip :: String -> String
strip xs = reverse $ dropWhile isSpace $ reverse $ dropWhile isSpace xs

type State = (Int, Int, Int)

update :: Obs -> State -> State
update (n, "red") (r, g, b) = (r, g, b `max` n)
update (n, "green") (r, g, b) = (r, g `max` n, b)
update (n, "blue") (r, g, b) = (r `max` n, g, b)

answer :: State -> Int
answer (r, g, b) = r * g * b

calc :: String -> Int
calc line = let (num, groups) = parse (strip line ++ ";") in
    let obs = concat groups in
    answer $ foldr update (0, 0, 0) obs

main = interact $ show . sum . map calc . lines
