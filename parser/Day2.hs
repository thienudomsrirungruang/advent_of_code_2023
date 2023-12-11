
import Parser
import Data.Char

type Obs = (Int, String)
type Group = [Obs]

pat :: Pattern (Int, [Group])
pat = Concat (Consume (cString "Game")
                >>$ Consume cSpace
                >>$ Consume cInt
                $>> Consume (cString ": ")) 
        groupPat (,)

groupPat :: Pattern [Group]
groupPat = strip $ listPat obsPat (strip $ Consume (cChar ';'))

obsPat :: Pattern [Obs]
obsPat = listPat
            (Concat (strip $ Consume cNonneg) (strip $ Consume $ cWhile isAsciiLower) (,))
            (Consume (cChar ','))

type State = (Int, Int, Int)

update :: Obs -> State -> State
update (n, "red") (r, g, b) = (r, g, b `max` n)
update (n, "green") (r, g, b) = (r, g `max` n, b)
update (n, "blue") (r, g, b) = (r `max` n, g, b)

answer :: State -> Int
answer (r, g, b) = r * g * b

calc :: String -> Int
calc line = let (num, groups) = extract $ parse pat line in
    let obs = concat groups in
    answer $ foldr update (0, 0, 0) obs

main = interact $ show . sum . map calc . lines
