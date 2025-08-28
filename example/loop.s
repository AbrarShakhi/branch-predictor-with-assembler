	.file   "loop.s"
.START:
    load    n, 10      ; Initialize n = 10
    load    i, 0       ; Initialize i = 0

.LOOP:
    cmp     i, n       ; Compare i < n
    jge     .END       ; If i >= n, exit loop

    call    i          ; Print value of i

    add     i, i, 1    ; t = t + 1 (AC = t + 1)
    jmp     .LOOP      ; Repeat loop

.END:


; n = 10
; i = 0
; while i < n:
;     call i  # print i
;     i += 1
; 