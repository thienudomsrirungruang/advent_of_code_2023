
-- import Parser
-- import Data.Char

-- type Op = Int -> Int -> Int
-- type Node = ([Int], Op, Int, Int, Int) -- (starting items, op, test, true, false)

-- patNum :: Pattern (Either Int ())
-- patNum = OrElse (strip $ Consume cNonneg) Left (strip $ Consume (cString "old")) Right
