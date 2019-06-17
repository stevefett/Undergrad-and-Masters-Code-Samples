#lang racket

#|Steven Salmons
CS135 -Linguistic Studies and Future of Programming Language
This language sits on top of a Java framework engine, with various function calls with passed tokens being parsed by the parent java engine.

|#

#|
Q1. make6 - takes two integers, and returns a 6-digit integer constructed of the leftmost 3
digits of the first input, and the rightmost 3 digits of the second input. For example,
(make6 561432 254) would return 561254. Negative signs on either input number
should be ignored - that is, (make6 561432 -254) would also return 561254. If the first
number has less than three, and/or the second number has less than three digits, your
function should return -2. Note: you may want to define some auxiliary functions.
|#

;f3 is an auxiliry function to return the first 3 digits of a number. 
(define (f3 x)
  (if (< (abs x) 999) x
      (floor (f3 (/ (abs x) 10)))))

;less3 is an auxiliry function which checks whether the int x has more than 3 digits.
(define (less3 x)
  (if (and (> x -100) (< x 100)) -1 x))

; QUESTION 1 
(define (make6 x y)
  (if (or (= (less3 (abs x)) -1) (= (less3 (abs y)) -1)) -1
    (+ (* (abs (f3 x)) 1000) (modulo (abs y) 1000)))
  )

;test
;(make6 561432 -254)


#|

Q2. concatL – takes two lists of lists of the same length and returns a list of that length
containing strings which are the concatenation of the strings at the same position in the
two list. For example, ( concatL ‘( (a b) (c d) (d e) ) ‘( (f f f) (d e s) (v v v v) ) will return ( “abfff”
“cddes” “devvvv” ). Note: you may want to define some auxiliary functions. You may
also use the built-in function “string-append” which takes two strings as arguments and
returns a string which is the concatenation of the two string arguments.

|#

;Convert a list to a string, auxiliry method taken from Stack Overflow.
;https://stackoverflow.com/questions/15543935/list-to-string-conversion-in-racket
(define (slist->string slst)
  (string-join (map symbol->string slst) ""))

; QUESTION 2
(define (concatL L1 L2)
  (map (lambda (i j) ( list(string-append (slist->string i)(slist->string j)))) L1 L2)     
)
           
;test
;(concatL '((a b) (c d) (d e)) '((f f f) (d e s) (v v v v)))


;==================================================================================================

;Q3. buildList – Takes an integer N and a Scheme expression E1 (i.e. an atome or a list ) and an
;integer M and a Scheme Expression E2 and
;returns a new list of length M+N where each element is the Expression E1 N times and E2 M
;times. For example:
;( buildList 5 ‘() 3 ‘B ) will return the list ( ( ) ( ) ( ) ( ) ( ) B B B )
;( buildList 3 ‘A 2 C) will return ( A A A C C )
;( buildList 2 ‘(a b c ) 1 Q) will return ( ( a b c ) ( a b c ) Q)

; QUESTION 3
; Auxiliry function to build a temp list.
(define (buildTemp N E)
  (if (= N 1)'()
      (cons E(buildTemp (- N 1) E)))
  (write E)
  )

(define(buildList N E1 M E2)
  (buildTemp N E1)
  (buildTemp M E2))


;test
;(buildList 5 `() 3 `B )
;(buildList 3 `A 2 `C)
;(buildList 2 `(a b c ) 1 Q) SHOULD THIS WORK WITHOUT A ` ?

;==================================================================================================

;Q4. DFA-Acceptor - Consider the following DFA which may start with zero or more 1s
;which must be followed by a 01 which may be followed by any string

; Auxiliry function determines start of DFA 0 or more 1's
(define (Q0 t)
 (cond [(eq? 0 (car t)) (Q1 (cdr t))] [(eq? 1 (car t)) (Q0 (cdr t))][else P]))

; Auxiliry function determines start of DFA 0 or more 1's
(define (Q1 t)
  (cond [(eq? 0 (car t)) (P)][(eq? 1 (car t)) (Q2)][else P]))

; Auxiliry function define Q2.
(define (Q2) #t)

; Auxiliry function define p.
(define (P) #f)

; QUESTION 4
(define ( DFA-Acceptor X S F SI)
  (cond [(eq? S Q0) (Q0 X)] [else 'invalid]) )

;test 
(DFA-Acceptor '(1 1 0 1 0) Q0 ( Q2 ) P)
(DFA-Acceptor '(1 1 1 1 0 1 0 1 0) Q0 ( Q2 ) P)
(DFA-Acceptor '(1 0 0) Q0 ( Q2 ) P)

;==================================================================================================

#|
Q5. selectN - takes as input an integer N. It then builds and returns a "select" function
based on N. The "select" function that is produced (by your lfunction selectN) would
have the property that it takes as input a list, and returns the same list with the last N
elements removed. 

At firt I solved it like this, which I don't know if I'm allowed to do?
It works though, and it's very short and nice looking, so I left it here.

(define (selectN n)
  (lambda (list)(drop-right list n)))

|#

; Here is a way of doing selectN that is probably allowed for this assignment.
(define (selectN n)
  (lambda(list)
    (define(iterator x c)
      (if (= c 0) x
         (iterator (reverse (cdr (reverse x)))(- c 1)))
      )
    (iterator list n))
  )

;test 1
;(define TS1 (selectN 5))
;(define result1 (TS1 '(4 8 2 9 -1 13)))
;(display result1)
;test 2
;(define TS2 (selectN 3))
;(define result2 (TS2 '(-2 3 -4 8 9 1 7)))
;(display result2)