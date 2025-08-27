.START:
    LOAD a 5            ; Load the value 5 into variable/register 'a'
    LOAD b 10           ; Load the value 10 into variable/register 'b'
    CMP a b             ; Compare the values of 'a' and 'b'
    JGE ELSE            ; Jump to ELSE label if 'a' is Greater or Equal to 'b'
    LOAD a              ; Load 'a' into the accumulator (AC) for the IF condition (a < b)
    ADD b               ; Add 'b' to the AC (AC = a + b)
    STOR result         ; Store the sum into 'result'
    JMP END             ; Jump to END to skip the ELSE block
.ELSE:
    LOAD a              ; Load 'a' into the AC for the ELSE block (a >= b)
    SUB b               ; Subtract 'b' from AC (AC = a - b)
    STOR result         ; Store the difference into 'result'
.END:
    PUSH result         ; Push 'result' value onto the stack (preparing for output)
    CALL STK            ; Print the top value of the stack 

; a = 5, b = 10
; if (a < b) {
;    result = a + b; // 5 + 10 = 15
; } else {
;    result = a - b;
; }