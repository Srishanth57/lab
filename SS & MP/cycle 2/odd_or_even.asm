; Even/Odd Number Checker - Linux x86 Assembly

section .data
    msg1 db 'Enter the number : ', 0
    msg1_len equ $ - msg1
    
    even db 'Even' , 0 
    even_len equ $ - even 
    
    odd db 'Odd' , 0 
    odd_len equ $ - odd 
    
    newline db 10

section .bss
    str1 resb 100
    str1_len resb 4 
    number resb 4
       
section .text
    global _start

_start:
    ; Display prompt message
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, msg1_len
    int 0x80
    
    ; Read input from user
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80
    
    ; Null-terminate the input string
    dec eax
    mov [str1_len], eax
    mov ebx, eax
    mov byte [str1 + ebx], 0
    
    ; Convert string to integer
    call stoi
    cmp eax, -1
    je exit
    
    ; Check if number is even or odd
    mov [number], eax 
    test eax, 1
    jz is_even
    
is_odd: 
    mov eax, 4 
    mov ebx, 1 
    mov ecx, odd 
    mov edx, odd_len 
    int 0x80 
    
    mov eax, 4
    mov ebx, 1 
    mov ecx, newline 
    mov edx, 1 
    int 0x80 
    jmp exit 
    
is_even: 
    mov eax, 4 
    mov ebx, 1 
    mov ecx, even 
    mov edx, even_len 
    int 0x80 
    
    mov eax, 4
    mov ebx, 1 
    mov ecx, newline 
    mov edx, 1 
    int 0x80 
    jmp exit 
    
; String to Integer conversion function
stoi: 
    push esi 
    push ebx 
    push ecx 
    push edx 
    
    mov esi, str1 
    xor eax, eax 
    xor ecx, ecx 
    mov ecx, 10
    
    jmp convert_loop 
    
convert_loop: 
    mov bl, [esi]
    cmp bl, 0 
    je .conversion_done
    
    ; Validate digit
    cmp bl, '0'
    jb .invalid_input 
    cmp bl, '9'
    ja .invalid_input 
    
    sub bl, '0'
    mul ecx     
    add eax, ebx 
    
    inc esi 
    jmp convert_loop
    
.conversion_done: 
    jmp stoi_exit
    
.invalid_input:
    mov eax, -1
    
stoi_exit: 
    pop edx 
    pop ecx 
    pop ebx 
    pop esi 
    ret
    
exit:
    mov eax, 1
    mov ebx, 0
    int 0x80
