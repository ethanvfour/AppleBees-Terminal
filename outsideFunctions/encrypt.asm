section .text



;FOLLOWING LCC

; rdi will be the string addy
; rsi is int length

; void function, string will be passed by ref

;This function will take in a string and use the ror implication in assembly to decrypt each byte
;String is passed by ref

;just do 4
global encryptString
encryptString:
    push rbx
    push r12
        
        mov r12, 0 ; counter
        goingThroughString:
            mov bl, byte[rdi + r12]
            ror bl, 4
            mov byte[rdi + r12], bl 
            inc r12
            cmp r12, rsi
            jb goingThroughString
        
    pop r12
    pop rbx
ret



; rdi will be the string addy
; rsi is int length

; void function, string will be passed by ref

;This function will take in a string and use the rol implication in assembly to decrypt each byte
;String is passed by ref

;just do 4
global decryptString
decryptString:
    push rbx
    push r12
    
        mov r12, 0 ; counter
        goingThroughStringAgain:
            mov bl, byte[rdi + r12]
            rol bl, 4
            mov byte[rdi + r12], bl 
            inc r12
            cmp r12, rsi
            jb goingThroughStringAgain

    pop r12
    pop rbx
ret

