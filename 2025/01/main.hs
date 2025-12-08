type Posicion = Integer
-- Invariante: todos los movimientos son positivos
data Movimiento = Izq Integer | Der Integer

total :: Integer
total = 100

main :: IO ()
main = do
        input <- readFile "input.txt"
        let movs = map parseLine $ lines input
            res = vecesEn0 movs 50
        print res

parseLine :: String -> Movimiento
parseLine ('L':n) = Izq $ read n
parseLine ('R':n) = Der $ read n
parseLine _ = error "Formato erroneo"

avanzar :: Movimiento -> Posicion -> Posicion
avanzar (Izq n) pos = (pos - n) `mod` total
avanzar (Der n) pos = (pos + n) `mod` total

-- Capaz habria que tomar dos posiciones y una direccion?
-- Hay algo de repeticion en el avanzar
-- Durisimo de leer esto. Quien me va a enseñar a programar
cruzaEl0 :: Movimiento -> Posicion -> Bool
cruzaEl0 mov lastPos =  resto /= 0 && -- Se movio y...
                    (
                    currPos == 0 -- Llego al cero o ...
                      ||
                        ( -- Cambio de "signo"
                        lastPos /= 0
                        &&
                          (
                          case mov of
                            Izq n -> currPos >= lastPos
                            Der n -> currPos <= lastPos
                          )
                        )
                    )

                   where
                    currPos = avanzar mov lastPos
                    resto   = abs $ currPos - lastPos

vueltasCompletas :: Movimiento -> Integer
vueltasCompletas mov = case mov of
                         Izq n -> vueltas n
                         Der n -> vueltas n
                        where
                          vueltas n = n `div` total

-- Retorna la cantidad de veces que el candado pasa por 0
-- dada una lista de movimientos y una posicion inicial
vecesEn0 :: [Movimiento] -> Posicion -> Integer
vecesEn0 = foldr (\mov rec pos -> let proxPos = avanzar mov pos in
                                      vueltasCompletas mov +
                                          if cruzaEl0 mov pos
                                          then 1 + rec proxPos
                                          else     rec proxPos
                                    )
                 (const 0)
