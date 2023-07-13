% Expert system shell based on Luger
% Rules made by: Aaron Dichoso, Austin Natividad, Luis Razon, Christian Tordillo
% To run, solve(appraise(X),CF)
% solve(+,?)
solve(Goal,CF) :-
    print_instructions,
    retractall(known(_,_)),
    solve(Goal,CF,[],20).
print_instructions :-
    nl, write('You will be asked a series of queries.'), nl,
    write('Your response must be either:'),
    nl, write('a. A number between -100 and 100 representing'), nl,
    write(' your confidence in the truth of the query'), nl,
    write('b. why'),
    nl, write('c. how(X), where X is a goal'),nl.

    % solve(+,?,+,+)
solve(Goal,CF,_,Threshold):-
    known(Goal,CF),!,
    above_threshold(CF,Threshold).
solve(not(Goal),CF,Rules,Threshold) :- !,
    invert_threshold(Threshold,New_threshold),
    solve(Goal,CF_goal,Rules,New_threshold),
    negate_cf(CF_goal,CF).
solve((Goal1,Goal2),CF,Rules,Threshold) :- !,
    solve(Goal1,CF1,Rules,Threshold),
    above_threshold(CF1,Threshold),
    solve(Goal2,CF2,Rules,Threshold),
    above_threshold(CF2,Threshold),
    and_cf(CF1,CF2,CF).
solve(Goal,CF,Rules,Threshold) :-
    rule((Goal:-(Premise)),CF_rule),
    solve(Premise,CF_premise,[rule((Goal:-Premise),CF_rule)|Rules],Threshold),
    rule_cf(CF_rule,CF_premise,CF),
    above_threshold(CF,Threshold).
solve(Goal,CF,_,Threshold) :-
    rule(Goal,CF),
    above_threshold(CF,Threshold).
solve(Goal,CF,Rules,Threshold):-
    askable(Goal),
    askuser(Goal,CF,Rules),!,
    assert(known(Goal,CF)),
    above_threshold(CF,Threshold).

above_threshold(CF,T) :- T>=0, CF>=T. above_threshold(CF,T)
:- T<0, CF=<T.

invert_threshold(Threshold,New_threshold):- New_threshold is
-1 * Threshold.

negate_cf(CF,Negated_CF):-
    Negated_CF is -1 * CF.
and_cf(A,B,A) :- A =< B.
and_cf(A,B,B) :- B < A.
rule_cf(CF_rule,CF_premise,CF):-
    CF is (CF_rule * CF_premise / 100).

% askuser(+,?,+)
askuser(Goal,CF,Rules):-
    nl,write('Query : '),
    write(Goal), write(' ? '),
    read(Ans),
    respond(Ans,Goal,CF,Rules).
% respond(+,+,?,+)
respond(CF,_,CF,_) :-
    number(CF), CF=<100, CF>= -100. % no response issued because user enters a valid CF
respond(why,Goal,CF,[Rule|Rules]) :-
    nl, write_rule(Rule),
    askuser(Goal,CF,Rules).
respond(why,Goal,CF,[]) :-
    nl, write('Back to top of rule stack.'), nl, askuser(Goal,CF,[]).
respond(how(X),Goal,CF,Rules):-
    build_proof(X,CF_X,Proof), !,
    nl, write('The goal '), write(X),
    write(' was concluded with certainty '), write(CF_X), write('.'), nl, nl, write('The proof of this is:'), nl,
    write_proof(Proof,0),nl,
    askuser(Goal,CF,Rules).
respond(how(X),Goal,CF,Rules) :-
    write('The truth of '), write(X), nl,
    write('is not yet known.'), nl,
    askuser(Goal,CF,Rules).
respond(_,Goal,CF,Rules):- write_rule('Unrecognized
response.'), nl, askuser(Goal,CF,Rules).

% build_proof(+,?,?)
build_proof(Goal,CF,(Goal,CF:-given)):-
    known(Goal,CF), !.
build_proof(not Goal,CF,not Proof) :- !,
    build_proof(Goal,CF_goal,Proof), negate_cf(CF_goal,CF).
build_proof((Goal1,Goal2),CF,(Proof1,Proof2)):-
    build_proof(Goal1,CF1,Proof1),
    build_proof(Goal2,CF2,Proof2), and_cf(CF1,CF2,CF).
build_proof(Goal,CF,(Goal,CF:-Proof)):-
    rule((Goal:-Premise),CF_rule),
    build_proof(Premise,CF_premise,Proof),
    rule_cf(CF_rule,CF_premise,CF).
build_proof(Goal,CF,(Goal,CF:-fact)):- rule(Goal,CF).
write_rule(rule((Goal:-(Premise)),CF)) :-
    write('I am trying to prove the following rule:'), nl, write(Goal),
    write(':-'), nl,
    write_premise(Premise),
    write('CF = '), write(CF), nl.
write_rule(rule(Goal,CF)) :-
    write('I am trying to prove the following goal:'), nl, write(Goal),
    write('CF = '), write(CF), nl.
write_premise((Premise1,Premise2)) :- !,
    write_premise(Premise1),
    write_premise(Premise2).
write_premise(not Premise) :- !,
    write(' '),
    write(not),
    write(' '),
    write(Premise),
    nl.
write_premise(Premise) :- !,
    write(' '), write(Premise), nl.
% write_proof(+,+)
write_proof((Goal,CF:-given),Level):-
    indent(Level),
    write(Goal),
    write(' CF='),
    write(CF),
    write(' was given by the user'), nl, !.
write_proof((Goal,CF:-fact),Level) :-
    indent(Level), write(Goal), write(' CF='), write(CF), write(' was a fact in the KB'), nl, !.
write_proof((Goal,CF:-Proof),Level) :-
    indent(Level), write(Goal), write(' CF='), write(CF), write(':-'), nl, New_level is Level + 1,
    write_proof(Proof,New_level),!.
write_proof(not Proof,Level) :-
    indent(Level), write((not)), nl,
    New_level is Level + 1,
    write_proof(Proof,New_level),!.
write_proof((Proof1,Proof2),Level):-
    write_proof(Proof1,Level), write_proof(Proof2,Level), !.

indent(0).
indent(X):-
    write(' '), X_new is X - 1, indent(X_new).

rule((appraise(Status) :- 
    (determine(X), appraise(X, Status))), 100).

/*
Very High Value Lots:
1. IF the government is interested in the property THEN the value of that lot is very high.

2. IF the lot has good opening AND the lot is very ideal AND the lot type is commercial THEN the value of that lot is very high. 
*/
rule((determine(very_high) :- government_interest), 90).
rule((determine(very_high) :- good(opening), very_ideal_lot, lot_type(commercial)), 90).

/*
High Value Lots:
1. IF the lot has a good opening AND the lot is a very ideal lot AND the lot type is residential 
AND the lot is near commercial establishments THEN the value of that lot is high.

2. IF the lot has a good opening AND the lot is a very ideal lot AND the lot type is residential 
AND the lot is NOT near commercial establishments THEN the value of that lot is high.

3. IF the lot has a good opening AND the lot is an ideal lot AND the lot type is residential 
AND the lot is near commercial establishments THEN  the value of that lot is high.

4. IF the lot has a good opening AND the lot is an ideal lot AND the lot type is residential 
AND the lot is NOT near commercial establishments THEN the value of that lot is high.

5. IF the lot has a good opening AND the lot is an ideal lot AND the lot type is commercial THEN the value of that lot is high.

6. IF the lot has a good opening AND the lot is a semi-ideal lot AND the lot type is commercial THEN the value of that lot is high.
*/
rule((determine(high) :- good(opening), very_ideal_lot, lot_type(residential), near(commercial_establishments)), 90).
rule((determine(high) :- good(opening), very_ideal_lot, lot_type(residential), not(near(commercial_establishments))), 80).

rule((determine(high) :- good(opening), ideal_lot, lot_type(residential), near(commercial_establishments)), 90).
rule((determine(high) :- good(opening), ideal_lot, lot_type(residential), not(near(commercial_establishments))), 80).

rule((determine(high) :- good(opening), ideal_lot, lot_type(commercial)), 90).
rule((determine(high) :- good(opening), semi_ideal_lot, lot_type(commercial)), 80).

/*
Low Value Lots:
1.IF the lot has a good opening AND the lot type is agricultural 
AND it is near commercial establishments THEN the value of that lot is low.

2. IF the lot has a good opening AND the lot type is agricultural 
AND it is NOT near commercial establishments THEN the value of that lot is low.

3. IF the lot has a good opening AND the lot is a semi-ideal lot 
AND the lot type is residential AND it is near commercial establishments THEN the value of that lot is low.

4. IF the lot has a good opening AND the lot is a semi-ideal lot 
AND the lot type is residential AND it is NOT near commercial establishments THEN the value of that lot is low.

5. IF the lot does not have a good opening AND the lot is a very ideal lot 
AND the lot type is agricultural AND it is near commercial establishments THEN the value of that lot is low.

6. IF the lot does not have a good opening AND the lot is a very ideal lot 
AND the lot type is agricultural AND it is NOT near commercial establishments THEN the value of that lot is low.

7. IF the lot does not have a good opening AND the lot is a very ideal lot 
AND the lot type is residential AND it is near commercial establishments THEN the value of that lot is low.

8. IF the lot does not have a good opening AND the lot is a very ideal lot 
AND the lot type is residential AND it is NOT near commercial establishments THEN the value of that lot is low.

9. IF the lot does not have a good opening AND the lot is a very ideal lot 
AND the lot type is commercial THEN the value of that lot is low.

10. IF the lot does not have a good opening AND the lot is an ideal lot 
AND the lot type is agricultural AND it is near commercial establishments THEN the value of that lot is low.

11. IF the lot does not have a good opening AND the lot is an ideal lot 
AND the lot type is agricultural AND it is NOT near commercial establishments THEN the value of that lot is low.

12. IF the lot does not have a good opening AND the lot is an ideal lot 
AND the lot type is residential AND it is near commercial establishments THEN the value of that lot is low.

13. IF the lot does not have a good opening AND the lot is an ideal lot 
AND the lot type is residential AND it is NOT near commercial establishments THEN the value of that lot is low.

14. IF the lot does not have a good opening AND the lot is an ideal lot 
AND the lot type is commercial THEN the value of that lot is low.

15. IF the lot does not have a good opening AND the lot is a semi-ideal lot 
AND the lot type is commercial THEN the value of that lot is low.

16. IF the lot has a good opening AND the lot is not an ideal lot 
AND the lot type is commercial THEN the value of that lot is low.
*/

%not commercial and not residential, assume to be agricultural; agricultural = low value
rule((determine(low) :- good(opening), lot_type(agricultural), near(commercial_establishments)), 70).
rule((determine(low) :- good(opening), lot_type(agricultural), not(near(commercial_establishments))), 80).

rule((determine(low) :- good(opening), semi_ideal_lot, lot_type(residential), near(commercial_establishments)), 80).
rule((determine(low) :- good(opening), semi_ideal_lot, lot_type(residential), not(near(commercial_establishments))), 80).

rule((determine(low) :- not(good(opening)), very_ideal_lot, lot_type(agricultural), near(commercial_establishments)), 90).
rule((determine(low) :- not(good(opening)), very_ideal_lot, lot_type(agricultural), not(near(commercial_establishments))), 90).

rule((determine(low) :- not(good(opening)), very_ideal_lot, lot_type(residential), near(commercial_establishments)), 80).
rule((determine(low) :- not(good(opening)), very_ideal_lot, lot_type(residential), not(near(commercial_establishments))), 90).

rule((determine(low) :- not(good(opening)), very_ideal_lot, lot_type(commercial)), 70).

rule((determine(low) :- not(good(opening)), ideal_lot, lot_type(agricultural), near(commercial_establishments)), 70).
rule((determine(low) :- not(good(opening)), ideal_lot, lot_type(agricultural), not(near(commercial_establishments))), 70).

rule((determine(low) :- not(good(opening)), ideal_lot, lot_type(residential), near(commercial_establishments)), 70).
rule((determine(low) :- not(good(opening)), ideal_lot, lot_type(residential), not(near(commercial_establishments))), 80).

rule((determine(low) :- not(good(opening)), ideal_lot, lot_type(commercial)), 70).

rule((determine(low) :- not(good(opening)), semi_ideal_lot, lot_type(commercial)), 80).
rule((determine(low) :- good(opening), not_ideal_lot, lot_type(commercial)), 50).

/*
Very Low Value Lots:
1. IF the lot does not have a good opening AND is a semi-ideal lot 
AND is an agricultural lot AND is near commercial establishments THEN it is a very low-value lot.

2. IF the lot does not have a good opening AND is a semi-ideal lot 
AND is an agricultural lot AND is NOT near commercial establishments THEN it is a very low-value lot.

3. IF the lot does not have a good opening AND is a semi-ideal lot 
AND is a residential lot AND near commercial establishments THEN it is a very low-value lot.

4. IF the lot does not have a good opening AND is a semi-ideal lot 
AND is a residential lot AND is NOT near commercial establishments THEN it is a very low-value lot.

5. IF the lot has a good opening AND is a not ideal lot 
AND is an agricultural lot AND near commercial establishments THEN it is a very low-value lot.

6. IF the lot has a good opening AND is a not ideal lot 
AND is an agricultural lot AND is NOT near commercial establishments THEN it is a very low-value lot.

7. IF the lot has a good opening AND is a not ideal lot 
AND is a residential lot AND near commercial establishments THEN it is a very low-value lot.

8. IF the lot has a good opening AND is a not ideal lot 
AND is a residential lot AND is NOT near commercial establishments THEN it is a very low-value lot.

9. IF the lot does not have a good opening AND is a not ideal lot 
AND is an agricultural lot AND near commercial establishments THEN it is a very low-value lot.

10. IF the lot does not have a good opening AND is a not ideal lot 
AND is an agricultural lot AND is NOT near commercial establishments THEN it is a very low-value lot.

11. IF the lot does not have a good opening AND is a not ideal lot 
AND is a residential lot AND near commercial establishments THEN it is a very low-value lot.

12. IF the lot does not have a good opening AND is a not ideal lot 
AND is a residential lot AND is NOT near commercial establishments THEN it is a very low-value lot.

13. IF the lot does not have a good opening AND is a not ideal lot 
AND is a commercial lot THEN it is a very low-value lot.
*/
rule((determine(very_low) :- not(good(opening)), semi_ideal_lot, lot_type(agricultural), near(commercial_establishments)), 80).
rule((determine(very_low) :- not(good(opening)), semi_ideal_lot, lot_type(agricultural), not(near(commercial_establishments))), 90).

rule((determine(very_low) :- not(good(opening)), semi_ideal_lot, lot_type(residential), near(commercial_establishments)), 70). 
rule((determine(very_low) :- not(good(opening)), semi_ideal_lot, lot_type(residential), not(near(commercial_establishments))), 90).

rule((determine(very_low) :- good(opening), not_ideal_lot, lot_type(agricultural), near(commercial_establishments)), 80).
rule((determine(very_low) :- good(opening), not_ideal_lot, lot_type(agricultural), not(near(commercial_establishments))), 90).

rule((determine(very_low) :- good(opening), not_ideal_lot, lot_type(residential), near(commercial_establishments)), 70).
rule((determine(very_low) :- good(opening), not_ideal_lot, lot_type(residential), not(near(commercial_establishments))), 90).

rule((determine(very_low) :- not(good(opening)), not_ideal_lot, lot_type(agricultural), near(commercial_establishments)), 80).
rule((determine(very_low) :- not(good(opening)), not_ideal_lot, lot_type(agricultural), not(near(commercial_establishments))), 90).

rule((determine(very_low) :- not(good(opening)), not_ideal_lot, lot_type(residential), near(commercial_establishments)), 80).
rule((determine(very_low) :- not(good(opening)), not_ideal_lot, lot_type(residential), not(near(commercial_establishments))), 90).

rule((determine(very_low) :- not(good(opening)), not_ideal_lot, lot_type(commercial)), 80).


/*
Error handling: Lot type is unsupported if
1. Lot type is not commercial AND
2. Lot type is not residential AND
3. Lot type is not agricultural
*/
rule((determine(unsupported_lot_type) :- not(lot_type(commercial)), not(lot_type(residential)), not(lot_type(commercial))), 100).




%Very ideal lot if all factors are TRUE
rule((very_ideal_lot :- shape(square), above(road_level), good(drainage)), 90).

/*
Ideal Lots: If the lot has at most 1 quality that is NOT satisfied.
*/
rule((ideal_lot :- not(shape(square)), above(road_level), good(drainage)), 90).
rule((ideal_lot :- shape(square), not(above(road_level)), good(drainage)), 80).
rule((ideal_lot :- shape(square), above(road_level), not(good(drainage))), 80).

/*
Semi-ideal Lots: If at least one quality is satisfied.
*/
rule((semi_ideal_lot :- shape(square), not(above(road_level)), not(good(drainage))), 80).
rule((semi_ideal_lot :- not(shape(square)), above(road_level), not(good(drainage))), 80).
rule((semi_ideal_lot :- not(shape(square)), not(above(road_level)), good(drainage)), 90).

rule((not_ideal_lot :- not(shape(square)), not(above(road_level)), not(good(drainage))), 90).

%IMPORTANT: IF DEFINE RULE, ALSO DEFINE CONCLUSION
rule(appraise(very_high, 'The lot is of very high value'), 100).
rule(appraise(high, 'The lot is of high value'), 100).
rule(appraise(low, 'The lot is of low value'), 100).
rule(appraise(very_low, 'The lot is of very low value'), 100).
rule(appraise(unsupported_lot_type, 'The lot type HAS to be one of the three types given (Commercial, Residential, Agricultural)'), 100).

askable(government_interest).
askable(lot_type(_)).
askable(near(_)).
askable(prone(_)).
askable(shape(_)).
askable(good(_)).
askable(above(_)).