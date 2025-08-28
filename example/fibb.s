.START:
    LOAD a, 0            ; a = 0
    LOAD b, 1            ; b = 1
    LOAD count, 0        ; count = 0
    LOAD limit, 20       ; limit = 20

.LOOP:
    CMP count, limit
    JGE .END             ; if count >= limit, exit loop

    CALL a               ; print current Fibonacci number (a)

    ADD temp, a, b       ; temp = a + b
    LOAD a, b            ; a = b
    LOAD b, temp         ; b = temp

    ADD count, count, 1  ; count++

    JMP .LOOP            ; repeat loop

.END:

; 	int n = 20;
; 	int a = 0;
; 	int b = 1;
; 	int temp;
; 	int count = 0;
; 
; 	while (count < n) {
; 		printf("%d\n", a);
; 		temp = a + b;
; 		a = b;
; 		b = temp;
; 		count = count + 1;
; 	}
; 	return 0;