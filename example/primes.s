    .file "primes.s"

.START:
    load    twenty, 20            ; Upper limit
    load    num, 2                ; Start from 2

.OUTER_LOOP:
    cmp     num, twenty
    jg      .END                  ; If num > 20, stop

    load    is_prime, 1           ; Assume num is prime
    load    div, 2                ; div = 2

.INNER_LOOP:
    cmp     div, num
    jge     .CHECK_PRIME          ; If div >= num, break inner loop

                                  ; === Compute (num / div) * div ===
    div     temp1, num, div,      ; temp1 = num / div
    mul     temp2, temp1, div     ; temp2 = temp1 * div

    cmp     temp2, num
    je      .NOT_PRIME            ; if equal → divisible → not prime

    add     div, div, 1           ; div += 1
    jmp     .INNER_LOOP

.NOT_PRIME:
    load    is_prime, 0
                                  ; fallthrough

.CHECK_PRIME:
    cmp     is_prime, 1
    jne     .SKIP_PRINT

    call    num                   ; print num

.SKIP_PRINT:
    add     num, num, 1           ; num += 1
    jmp     .OUTER_LOOP

.END:


; example code in c
; int num = 2;
; int is_prime;
; int div;
; int temp1, temp2;
; 
; while (num <= 20) {
;     is_prime = 1;      // Assume num is prime
;     div = 2;
; 
;     while (div < num) {
;         temp1 = num / div;        // Integer division
;         temp2 = temp1 * div;      // Reconstruct num from quotient
; 
;         if (temp2 == num) {       // If equal, num is divisible
;             is_prime = 0;
;             break;
;         }
; 
;         div = div + 1;
;     }
; 
;     if (is_prime == 1) {
;         printf("%d\n", num);
;     }
; 
;     num = num + 1;
; }
