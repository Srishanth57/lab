global _start

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

    ; Convert first number
    mov esi,num1
    call stoi
    mov [n1int],eax

    ; Convert second number
    mov esi,num2
    call stoi
    mov [n2int],eax

    ; SUM
    mov eax,[n1int]
    add eax,[n2int]
    push eax

    mov eax,4
    mov ebx,1
    mov ecx,out_sum
    mov edx,osumlen
    int 0x80

    pop eax
    mov edi,sumstr
    call itoa

    mov esi,sumstr
    call print_str

    ; Print newline
    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

    ; DIFFERENCE
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
    call print_str

    ; Print newline
    mov eax,4
    mov ebx,1
    mov ecx,newline
    mov edx,1
    int 0x80

    ; Exit
    mov eax,1
    xor ebx,ebx
    int 0x80

;---------------------------------------
; stoi: convert string number in ESI → EAX
;---------------------------------------
stoi:
    xor eax,eax
    xor ebx,ebx
.next_char:
    mov bl,[esi]
    cmp bl,0
    je .done
    sub bl,'0'
    imul eax,10
    add eax,ebx
    inc esi
    jmp .next_char
.done:
    ret

;---------------------------------------
; itoa: convert integer in EAX → string in EDI
;---------------------------------------
itoa:
    push eax
    push ebx
    push ecx
    push edx
    push edi

    mov ecx,0           ; digit count
    mov ebx,10
    cmp eax,0
    jne .convert
    mov byte [edi],'0'
    inc edi
    mov byte [edi],0
    jmp .done

.convert:
    xor edx,edx
    div ebx
    push edx
    inc ecx
    test eax,eax
    jnz .convert

.write_digits:
    cmp ecx,0
    je .finish
    pop edx
    add dl,'0'
    mov [edi],dl
    inc edi
    dec ecx
    jmp .write_digits

.finish:
    mov byte [edi],0

.done:
    pop edi
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret

;---------------------------------------
; print_str: print null-terminated string at ESI
;---------------------------------------
print_str:
    push eax
    push ebx
    push ecx
    push edx

    mov ecx,esi
    xor edx,edx
.count:
    cmp byte [ecx+edx],0
    je .print
    inc edx
    jmp .count
.print:
    mov eax,4
    mov ebx,1
    int 0x80

    pop edx
    pop ecx
    pop ebx
    pop eax
    ret

