section .data
    prompt db "Enter a string: ", 0
    prompt_len equ $ - prompt
    
    palindrome_msg db "The string is a palindrome (case-insensitive)", 10, 0
    palindrome_len equ $ - palindrome_msg
    
    not_palindrome_msg db "The string is not a palindrome (case-insensitive)", 10, 0
    not_palindrome_len equ $ - not_palindrome_msg

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
    
    ; Check if string is empty (length 0 or 1 is palindrome)
    cmp eax, 1
    jle is_palindrome       ; strings of length 0 or 1 are palindromes
    
    ; Set up palindrome check
    ; esi will point to start of string
    ; edi will point to end of string
    mov esi, input_string   ; start pointer
    mov edi, input_string   ; end pointer
    add edi, eax            ; move to end of string
    dec edi                 ; point to last character (not null terminator)
    
    ; Calculate number of comparisons needed
    mov ecx, eax            ; string length
    shr ecx, 1              ; divide by 2 (we only need to check half)
    
palindrome_check_loop:
    ; Get characters from start and end
    mov al, [esi]           ; character from start
    mov bl, [edi]           ; character from end
    
    ; Convert first character to lowercase if it's uppercase
    cmp al, 'A'             ; check if >= 'A'
    jb skip_convert1        ; if below 'A', skip conversion
    cmp al, 'Z'             ; check if <= 'Z'
    ja skip_convert1        ; if above 'Z', skip conversion
    add al, 32              ; convert to lowercase (A-Z to a-z)
    
skip_convert1:
    ; Convert second character to lowercase if it's uppercase
    cmp bl, 'A'             ; check if >= 'A'
    jb skip_convert2        ; if below 'A', skip conversion
    cmp bl, 'Z'             ; check if <= 'Z'
    ja skip_convert2        ; if above 'Z', skip conversion
    add bl, 32              ; convert to lowercase (A-Z to a-z)
    
skip_convert2:
    ; Compare the (possibly converted) characters
    cmp al, bl              ; compare characters
    jne not_palindrome      ; if different, not a palindrome
    
    ; Move pointers toward center
    inc esi                 ; move start pointer right
    dec edi                 ; move end pointer left
    
    ; Continue loop
    loop palindrome_check_loop
    
is_palindrome:
    ; Print palindrome message
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, palindrome_msg ; message
    mov edx, palindrome_len ; length
    int 0x80                ; system call
    jmp exit_program
    
not_palindrome:
    ; Print not palindrome message
    mov eax, 4              ; sys_write
    mov ebx, 1              ; stdout
    mov ecx, not_palindrome_msg  ; message
    mov edx, not_palindrome_len  ; length
    int 0x80                ; system call
    
exit_program:
    ; Exit program
    mov eax, 1              ; sys_exit
    mov ebx, 0              ; exit status
    int 0x80                ; system call
