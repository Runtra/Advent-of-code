type Posicion = Integer

total :: Integer
total = 100

main :: IO ()
main = do
        input <- readFile "input.txt"
        let movs = map parseLine $ lines input
            res = vecesEn0 movs 50
        print res 

parseLine :: String -> Integer
parseLine ('L':n) = - read n
parseLine ('R':n) =   read n
parseLine _ = error "Formato erroneo"

avanzar :: Integer -> Posicion -> Posicion
avanzar n pos = (pos + n) `mod` total

-- Retorna la cantidad de veces que el candado pasa por 0
-- dada una lista de movimientos y una posicion inicial
vecesEn0 :: [Integer] -> Posicion -> Integer
vecesEn0 = foldr (\mov rec pos -> let proxPos = avanzar mov pos in
                                      if proxPos == 0 then
                                        1 + rec proxPos
                                      else
                                        rec proxPos
                                    )
                 (\n -> if n==0 then 1 else 0)
