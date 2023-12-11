{-# LANGUAGE ExistentialQuantification #-}

module Parser where

import Data.Char

data Pattern a = Nil a
    | forall b. Apply (b -> a) (Pattern b)
    | Consume (Consumer a)
    | forall b c. OrElse (Pattern b) (b -> a) (Pattern c) (c -> a)
    | forall b c. Concat (Pattern b) (Pattern c) (b -> c -> a)
    | forall b. Star (Pattern b) ([b] -> a)

type Consumer a = String -> Maybe (a, String)

parse :: Pattern a -> String -> Maybe (a, String)
parse (Nil v) xs = Just (v, xs)
parse (Apply f p) xs = do
    (v, xs') <- parse p xs
    return (f v, xs')
parse (Consume c) xs = c xs
parse (OrElse p1 f1 p2 f2) xs = case parse p1 xs of
    Nothing -> do
        (v, xs') <- parse p2 xs
        return (f2 v, xs')
    Just (v, xs') -> return (f1 v, xs')
parse (Concat p1 p2 f) xs = do
    (v1, xs1) <- parse p1 xs
    (v2, xs2) <- parse p2 xs1
    return (f v1 v2, xs2)
parse (Star p f) xs = let (v, xs') = eat xs in Just (f v, xs')
    where
        eat xs = case parse p xs of
            Nothing -> ([], xs)
            Just (v, xs') -> let (vs, xs'') = eat xs' in (v:vs, xs'')

extract :: Maybe (a, String) -> a
extract (Just (v, "")) = v
extract _ = error "Parse error!"

-- Consumers
cChar :: Char -> Consumer Char
cChar c (x:xs) | c == x = Just (c, xs)
cChar _ _ = Nothing

cString :: String -> Consumer String
cString "" xs = Just ("", xs)
cString (c:cs) xs = do
    (c', xs') <- cChar c xs
    (cs', xs'') <- cString cs xs'
    return (c':cs', xs'')

cWhile :: (Char -> Bool) -> Consumer String
cWhile f xs = Just (span f xs)

cWord :: Consumer String
cWord = cWhile (not . isSpace)

cSpace :: Consumer String
cSpace = cWhile isSpace

cNonneg :: Consumer Int
cNonneg xs = do
    (s, xs') <- cWhile isDigit xs
    return (read s, xs')

cInt :: Consumer Int
cInt xs = case cChar '-' xs of
    Nothing -> cNonneg xs
    Just (_, xs') -> do
        (n, xs'') <- cNonneg xs'
        return (-n, xs'')

-- Patterns

infixl 4 $>>
infixl 4 >>$

($>>) :: Pattern a -> Pattern b -> Pattern a
p1 $>> p2 = Concat p1 p2 const

(>>$) :: Pattern a -> Pattern b -> Pattern b
p1 >>$ p2 = Concat p1 p2 (\_ x -> x)

($>>$) :: Pattern a -> Pattern a -> Pattern a
p1 $>>$ p2 = OrElse p1 id p2 id

listPat :: Pattern a -> Pattern b -> Pattern [a]
listPat p sep = Concat (Star (p $>> sep) id) p (\xs x -> xs ++ [x])

strip :: Pattern a -> Pattern a
strip p = Consume cSpace >>$ p $>> Consume cSpace
