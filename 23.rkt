#lang racket
(define (sum lst) (foldl + 0 lst))
(define (factors n)
  (let* ([smalls
         (for/list ([i (in-range 1 (add1 (truncate (sqrt n))))]
                    #:when (zero? (modulo n i)))
           i)]
        [bigs
         (for/list ([i (reverse (cdr smalls))]
                    #:when (not (= i (/ n i))))
           (/ n i))])
    (append smalls bigs)))

(define (abundant? n) 
  (> (sum (factors n)) n))

(define abundola
  (for/hasheqv ([i (in-range 1 28125)]
             #:when (abundant? i))
    (values i i)))

(define (sum-of-2-abundant? n)
  (for/or ([x (in-hash-keys abundola)]
           #:when (< x n))
    (hash-has-key? abundola (- n x))))

(define (get-answer) 
  (for/sum ([x (in-range 1 28125)] #:when (not (sum-of-2-abundant? x))) x))