section .data 
    prompt1 db 'Enter a string: ', 0
    prompt1_len equ $ - prompt1 	; $ => current address , prompt1 => starting address of the prompt1 string 
    
    prompt2 db 'Enter the character to count: ', 0
    prompt2_len equ $ - prompt2
    
    result_msg db 'The count is: ', 0
    result_msg_len equ $ - result_msg
    
    count db 0
    newline db 10	; 10 defines the newline character 

section .bss 
    input_str resb 256
    input_char resb 2   

section .text 
    global _start 

_start: 
    ; Print prompt for string
    mov eax, 4 	
    mov ebx, 1 		;stdout (write)
    mov ecx, prompt1
    mov edx, prompt1_len 
    int 0x80 	; pass the program to the kernal for performing system calls with the values loaded the the corresponding registers 
    
    ; Read string
    mov eax, 3 
    mov ebx, 0 		;stdin (read) 
    mov ecx, input_str
    mov edx, 256
    int 0x80 
    
    dec eax		;remove the \n character 
    mov byte [input_str + eax], 0	; insert \0 character to the end of the string 
    
    ; Print prompt for character
    mov eax, 4 
    mov ebx, 1 
    mov ecx, prompt2
    mov edx, prompt2_len 
    int 0x80 
    
    ; Read character
    mov eax, 3 
    mov ebx, 0 
    mov ecx, input_char
    mov edx, 2
    int 0x80 
    
    mov esi, input_str    	; esi points to the address of the input str
    mov bl, [input_char]  	; stores the value to bl 

count_loop:
    mov al, [esi]          
    cmp al, 0              
    je print_result        

    cmp al, bl             
    jne next_char          

    inc byte [count]       

next_char:
    inc esi                
    jmp count_loop         

print_result:
    mov eax, 4
    mov ebx, 1
    mov ecx, result_msg
    mov edx, result_msg_len
    int 0x80

    add byte [count], '0'

    mov eax, 4
    mov ebx, 1
    mov ecx, count
    mov edx, 1
    int 0x80

    mov eax, 4
    mov ebx, 1
    mov ecx, newline
    mov edx, 1
    int 0x80

exit_program: 
    mov eax, 1
    mov ebx, 0
    int 0x80

