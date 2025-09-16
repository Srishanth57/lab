section .data
    prompt db "Enter a string: ", 0
    prompt_len equ $ - prompt
    
    result_msg db "Reversed string: ", 0
    result_len equ $ - result_msg
    
    newline db 10, 0

section .bss
    input_string resb 256    ; buffer for input string
    string_len resb 4        ; to store string length

section .text
    global _start

_start:
    ; Print prompt
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, prompt         ; message
    mov edx, prompt_len     ; length
    int 0x80                ; system call
    
    ; Read string from user
    mov eax, 3              ; sys_read
    mov ebx, 0              ; stdin
    mov ecx, input_string   ; buffer
    mov edx, 256            ; max bytes to read
    int 0x80                ; system call
    
    ; Store string length (subtract 1 for newline)
    dec eax                 ; remove newline from count
    mov [string_len], eax   ; store actual string length
    
    ; Remove newline character from input
    mov ebx, eax            ; length in ebx
    mov byte [input_string + ebx], 0  ; null terminate
    
    ; Check if string is empty or has only one character
    cmp eax, 1
    jle print_result        ; strings of length 0 or 1 don't need reversal
    
    ; Set up for string reversal using two pointers
    ; esi will point to start of string
    ; edi will point to end of string
    mov esi, input_string   ; start pointer
    mov edi, input_string   ; end pointer
    add edi, eax            ; move to end of string
    dec edi                 ; point to last character
    
    ; Calculate number of swaps needed (length / 2)
    mov ecx, eax            ; string length
    shr ecx, 1              ; divide by 2
    
reverse_loop:
    ; Swap characters at start and end positions
    mov al, [esi]           ; get character from start
    mov bl, [edi]           ; get character from end
    mov [esi], bl           ; put end character at start
    mov [edi], al           ; put start character at end
    
    ; Move pointers toward center
    inc esi                 ; move start pointer right
    dec edi                 ; move end pointer left
    
    ; Continue loop
    loop reverse_loop
    
print_result:
    ; Print result message
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, result_msg     ; message
    mov edx, result_len     ; length
    int 0x80                ; system call
    
    ; Print the reversed string
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, input_string   ; reversed string
    mov edx, [string_len]   ; length of string
    int 0x80                ; system call
    
    ; Print newline
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, newline        ; newline character
    mov edx, 1              ; length
    int 0x80                ; system call
    
exit_program:
    ; Exit program
    mov eax, 1              ; sys_exit
    mov ebx, 0              ; exit status
    int 0x80                ; system call
