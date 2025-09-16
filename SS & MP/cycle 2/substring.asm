section .data
    msg1 db 'Enter the string : ', 0
    msg1_len equ $ - msg1
    
    msg2 db 'Enter the sub string : ', 0
    msg2_len equ $ - msg2
    
    equal db 'Found', 0
    equal_len equ $ - equal
    
    not_equal db 'Not found', 0
    not_equal_len equ $ - not_equal

    newline db 10

section .bss
    str1  resb 100
    str2  resb 100
  
section .text
    global _start

_start:
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, msg1_len
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 100
    int 0x80
    
    dec eax
  
    mov ebx, eax
    mov byte [str1 + ebx], 0

    mov eax, 4
    mov ebx, 1
    mov ecx, msg2
    mov edx, msg2_len
    int 0x80

    mov eax, 3
    mov ebx, 0
    mov ecx, str2
    mov edx, 100
    int 0x80
    
    dec eax

    mov ebx, eax
    mov byte [str2 + ebx], 0

    mov esi, str1
    
.outer_loop: 

    mov edi  ,str2 
    
.inner_loop: 
    mov al , [esi]
    mov bl , [edi]
    
    cmp al , 0 
    je .not_substring 
    
    cmp bl , 0 
    je .substring
    
    cmp al , bl 
    je .match
    
    jmp .next_char 
    
.match: 
    inc edi 
    inc esi 
    jmp .inner_loop 
    
.next_char:
     inc esi 
     jmp .outer_loop
        
    
.substring:
    mov eax, 4
    mov ebx, 1
    mov ecx, equal
    mov edx, equal_len
    int 0x80
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80
    
    jmp .exit

.not_substring:
    mov eax, 4
    mov ebx, 1
    mov ecx, not_equal
    mov edx, not_equal_len
    int 0x80
    
    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

.exit:
    mov eax, 1
    mov ebx, 0
    int 0x80

 

 
