	.file   "loop.s"
.START:
    load    a, 5           ; Load the value 5 into variable/register 'a'
    load    b, 10          ; Load the value 10 into variable/register 'b'
    cmp     a, b            ; Compare the values of 'a' and 'b'
    jge     .ELSE           ; Jump to ELSE label if 'a' is Greater or Equal to 'b'
    load    a              ; Load 'a' into the accumulator (AC) for the IF condition (a < b)
    add     b               ; Add 'b' to the AC (AC = a + b)
    stor    result         ; Store the sum into 'result'
    jmp     .END            ; Jump to END to skip the ELSE block
.ELSE:
    load    a              ; Load 'a' into the AC for the ELSE block (a >= b)
    sub     b               ; Subtract 'b' from AC (AC = a - b)
    stor    result         ; Store the difference into 'result'
.END:
    call    result         ; Print the top value of the stack 

; a = 5
; b = 10
; if (a < b) {
;    result = a + b;
; } else {
;    result = a - b;
; }