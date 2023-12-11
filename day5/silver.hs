
import Parser

type Seeds = [Int]

type Map = [(Int, Int, Int)]

type Input = (Seeds, [Map])

pat :: Pattern Input
pat = Concat seedPat (Star mapPat id) (,)

seedPat :: Pattern Seeds
seedPat = Consume cWord >>$ Consume cSpace >>$ Star (strip $ Consume cNonneg) id

mapPat :: Pattern Map
mapPat = strip $ strip (Consume cWord) >>$ Consume (cString "map:")
                >>$ Star (strip $ Apply (\[x, y, z] -> (x, y, z)) $ listPat (Consume cNonneg) (Consume $ cChar ' ')) id

doMap :: Map -> Int -> Int
doMap [] s = s
doMap ((x, y, z):ms) s = if y <= s && s < y+z then x+(s-y) else doMap ms s

solveOne :: [Map] -> Int -> Int
solveOne = flip $ foldl (flip doMap)

solve :: Input -> Int
solve (seeds, maps) = minimum (map (solveOne maps) seeds)

main :: IO ()
main = interact $ show . solve . extract . parse pat
-- main = interact $ show . parse pat

