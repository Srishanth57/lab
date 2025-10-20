section .data
    prompt1     db 'Enter first number: ', 0
    plen1       equ $-prompt1
    prompt2     db 'Enter second number: ', 0
    plen2       equ $-prompt2
    out_sum     db 'Sum: ',0
    osumlen     equ $-out_sum
    out_diff    db 'Difference: ',0
    odifflen    equ $-out_diff
    newline     db 10

section .bss
    num1        resb 12
    num2        resb 12
    sumstr      resb 12
    diffstr     resb 12
    n1int       resd 1
    n2int       resd 1

section .text
    global _start
_start:
    ; Prompt and read first number
    mov eax,4
    mov ebx,1
    mov ecx,prompt1
    mov edx,plen1
    int 0x80
    mov eax,3
    mov ebx,0
    mov ecx,num1
    mov edx,12
    int 0x80
    mov [num1+eax-1],byte 0

    ; Prompt and read second number
    mov eax,4
    mov ebx,1
    mov ecx,prompt2
    mov edx,plen2
    int 0x80
    mov eax,3
    mov ebx,0
    mov ecx,num2
    mov edx,12
    int 0x80
    mov [num2+eax-1],byte 0

    ; Convert first number to int
    mov esi,num1
    call stoi
    mov [n1int],eax

    ; Convert second number to int
    mov esi,num2
    call stoi
    mov [n2int],eax

    ; Sum calculation and print label
    mov eax,[n1int]
    add eax,[n2int]
    push eax
    mov eax,4
    mov ebx,1
    mov ecx,out_sum
    mov edx,osumlen-1
    int 0x80
    pop eax
    mov edi,sumstr
    call itoa
    mov esi,sumstr
    push esi
    mov ecx,0

.get_len:
    cmp byte [esi+ ecx ],0
    je .print_sum
    inc ecx 
    jmp  .get_len

.print_sum:
    mov edx , ecx 
    mov eax,4
    mov ebx,1
    mov ecx,sumstr
    
    int 0x80
    pop esi

    ; Print newline
    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

    ; Difference calculation and print label
    mov eax,[n1int]
    sub eax,[n2int]
    push eax
    mov eax,4
    mov ebx,1
    mov ecx,out_diff
    mov edx,odifflen
    int 0x80
    pop eax
    mov edi,diffstr
    call itoa
    mov esi,diffstr
    push esi
    mov ecx,0

.get_len2:
    cmp byte [esi+ ecx ],0
    je .print_diff
    inc ecx
   
    jmp .get_len2

.print_diff:
    mov edx , ecx 
    mov eax,4
    mov ebx,1
    mov ecx,diffstr
    int 0x80
    pop esi

    ; Print newline
    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

    ; Exit program
    mov eax,1
    xor ebx,ebx
    int 0x80

; stoi implementation
stoi:
    push ebx
    push eax
    push ecx
    push edx
    push esi

    xor eax,eax
    xor ebx,ebx

.next_char:
    mov bl,[esi]
    cmp bl,0
    je .done
    sub bl,'0'
    movzx ecx,bl
    mov edx,10
    imul eax,eax,edx
    add eax,ecx
    inc esi
    jmp .next_char
.done:
    pop esi
    pop edx
    pop ecx
    pop eax
    pop ebx
    ret

; itoa implementation
itoa:
    push eax
    push ebx
    push ecx
    push edx
    push edi

    mov ecx,0

    cmp eax,0
    jne .check1

    mov byte [edi],'0'
    inc edi
    mov byte [edi],0
    jmp .itoa_done

.check1:
    cmp eax,0
    je .reverse_ascii
    mov ebx,10
    xor edx,edx

    div ebx
    push edx
    inc ecx
    jmp .check1

.reverse_ascii:
    cmp ecx,0
    je .itoa_done
    pop edx
    add dl,'0'
    mov [edi],dl
    inc edi
    dec ecx
    jmp .reverse_ascii

.itoa_done:
    mov byte [edi],0
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret

