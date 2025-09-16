section .data
    msg1 db 'Enter the string : ', 0
    msg1_len equ $ - msg1
    
   
    toggled db 'Toggled String: ', 0
    toggled_len equ $ - toggled
    
  

    newline db 10

section .bss
    str1  resb 100
       str1_len resb 4 
       
  
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
      mov [str1_len] , eax 
      
    mov ebx, eax
    mov byte [str1 + ebx], 0

    mov esi, str1
    
.toggle_loop: 

    mov al , [esi]
    cmp al , 0 
    je .completed
    
    cmp al , 'A'
    jb .check_lowercase
    
    cmp al , 'Z'
    ja .check_lowercase 
    
    add al , 32 
    mov [esi] , al 
    
    jmp .next_char
    

.check_lowercase: 
    cmp al , 'a'
    jb .next_char
    cmp al , 'z'
    ja .next_char 
    
    sub al , 32 
    mov [esi] , al 
    
    jmp .next_char
    
    
.next_char: 

    inc esi 
    jmp .toggle_loop
    
.completed: 
    mov eax, 4
    mov ebx, 1
    mov ecx, toggled
    mov edx, toggled_len
    int 0x80
    
    mov eax, 4
    mov ebx, 1
    mov ecx, str1
    mov edx, str1_len
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

 
