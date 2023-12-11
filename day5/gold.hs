
import Parser

type Seeds = [Int]

type Map = [(Int, Int, Int)]

type Input = (Seeds, [Map])

pat :: Pattern Input
pat = seedPat $>$ Star mapPat id

seedPat :: Pattern Seeds
seedPat = Consume cWord >>$ Consume cSpace >>$ Star (strip $ Consume cNonneg) id

mapPat :: Pattern Map
mapPat = strip $ strip (Consume cWord) >>$ Consume (cString "map:")
                >>$ Star (strip $ Apply (\[x, y, z] -> (x, y, z)) $ listPat (Consume cNonneg) (Consume $ cChar ' ')) id

type Range = (Int, Int) -- start, len
type Ranges = [Range]

inter :: (Int, Int) -> Range
inter (l, r) = (l, r-l)

valid :: Ranges -> Ranges
valid = filter ((>0) . snd)

doMapsOnRange :: Map -> Range -> Ranges
doMapsOnRange [] r = [r]
doMapsOnRange ((x, y, z):ms) (s, l) =
    let leftRange = inter (s, (s+l) `min` y)
        rightRange = inter ((y+z) `max` s, s+l)
        midRange = inter (x `max` (s+x-y), (x+z) `min` (s+l+x-y))
    in valid [midRange] ++ doMaps ms (valid [leftRange, rightRange])

doMaps :: Map -> Ranges -> Ranges
doMaps m = concatMap (doMapsOnRange m)

solveOne :: [Map] -> Ranges -> Ranges
solveOne = flip $ foldl (flip doMaps)

minR :: Range -> Int
minR (s, l) = s

minRs :: Ranges -> Int
minRs = minimum . map minR

rangeify :: [Int] -> Ranges
rangeify (x:l:xs) = (x, l) : rangeify xs
rangeify [] = []

solve :: Input -> Int
solve (seeds, maps) = minRs (solveOne maps $ rangeify seeds)

main :: IO ()
main = interact $ show . solve . extract . parse pat
