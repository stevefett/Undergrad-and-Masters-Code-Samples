/*
;Steven Salmons
;CS136
;Assignment 3
;
;
;
;Problem 1
*/
append([],L,L).
append([H | L1],L2,[H | L3]) :- append(L1,L2,L3).
countdown(0,X) :- write(X).
countdown(0,X) :- X is 0.
countdown(X,L) :- not(L=[]), Y is X - 1, append(L,[X],Z), countdown(Y,Z).
countdown(X,[L]) :- L=[], Y is X - 1, countdown(Y,[X]).
/*
;Problem 2
*/
dupList([],[]).
dupList([X],[X,X]).
dupList([X|Y],[X,X|Z]) :- dupList(Y,Z). 
/*
;Problem 3
*/
oddSize([X]).
oddSize ([X,Y|A]) :- oddSize(A).
/*
;
;
;
;
;Problem 4
;Consider the following predicate:
*/
append([ ],B,B).
append([Head|TailA],B,[Head|TailC]) :- append(TailA,B,TailC).
/*
;Using the method discussed in class show how Prolog will search the answer to the following query:
;?-append(X, Y, [ 1, 2 ] )
;
;
;Answer:
;
?-append(X, Y, [ 1, 2 ] ) is the query written as:
	:- append(X, Y, [1, 2])
	& append([], B, B).
	{ unify: X = [], Y = B, B = [1, 2] }
	giving: 
	X = [], Y = [1, 2].
A "trace." command in Prolog can prove this path:
1 ?- trace.
true.

[trace] 1 ?- append(X, Y, [1,2]).
   Call: (6) append(_G520, _G521, [1, 2]) ? creep
   Exit: (6) append([], [1, 2], [1, 2]) ? creep
X = [],
Y = [1, 2] .
*/