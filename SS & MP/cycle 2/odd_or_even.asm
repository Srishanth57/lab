section .data
    msg1    db 'Enter the number : ', 0
    msg1_len equ $ - msg1

    even    db 'Even', 10, 0
    even_len equ $ - even

    odd     db 'Odd', 10, 0
    odd_len equ $ - odd

section .bss
    str1    resb 20      ; Buffer for input string

section .text
    global _start

_start:
    ; Print prompt
    mov eax, 4
    mov ebx, 1
    mov ecx, msg1
    mov edx, msg1_len
    int 0x80

    ; Read input string from user
    mov eax, 3
    mov ebx, 0
    mov ecx, str1
    mov edx, 20
    int 0x80

    ; Null terminate input string (assuming input length in eax - 1)
    dec eax
    mov byte [str1 + eax], 0

    ; Convert input string to integer (eax)
    mov esi, str1
    call stoi

    ; Check if even or odd using test (least significant bit)
    test eax, 1
    jz print_even

print_odd:
    mov eax, 4
    mov ebx, 1
    mov ecx, odd
    mov edx, odd_len
    int 0x80
    jmp exit

print_even:
    mov eax, 4
    mov ebx, 1
    mov ecx, even
    mov edx, even_len
    int 0x80

exit:
    mov eax, 1
    mov ebx, 0
    int 0x80

; Simple stoi: convert string at esi to integer in eax 
; No error checks, assumes valid numeric input
stoi:
    xor eax, eax        ; Clear eax (result)
.next_char:
    mov bl, [esi]
    cmp bl, 0
    je .done
    sub bl, '0'         ; Convert char to number
    imul eax, eax, 10
    add eax, ebx
    inc esi
    jmp .next_char
.done:kk
    ret

