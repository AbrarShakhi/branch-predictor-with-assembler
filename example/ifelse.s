    .globl main
main:
    pushq   %rbp                
    movq    %rsp, %rbp

    movl    $4, -4(%rbp)        
    movl    $5, -8(%rbp)        

    movl    -4(%rbp), %eax      
    cmpl    $0, %eax            
    jl      .Lelse              

    movl    $0, %eax            
    jmp     .Lend

.Lelse:
    movl    $1, %eax            

.Lend:
    popq    %rbp                
    ret
