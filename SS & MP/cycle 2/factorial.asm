global _start

section .data
	prompt1 db 'Enter the num: ' , 0
	prompt1_len equ $ - prompt1 
	factorial db 'Factorial is: ', 0
	factorial_len equ $ - factorial 

	newline db 10

section .bss 
	num resb 12
	num_value resb 12
	num_int resd 1
	result resb 12 
	result_int resd 1
	
	
section .text 

_start: 
	mov eax , 4 
	mov ebx , 1
	mov ecx , prompt1 
	mov edx , prompt1_len 
	int 0x80 
	
	
	mov  eax ,3 
	mov ebx , 0 
	mov ecx , num 
	mov edx ,12
	int 0x80 
	
	dec eax 
	
	
	mov ebx , eax 
	mov byte[ num + ebx] , 0
	
	mov esi , num 
	call stoi
	mov [num_int ] , eax 
	mov ecx , [num_int]
	mov eax , 1 
	
.fact: 
	cmp ecx,  0 
	je .print 
	imul eax, ecx 
	dec ecx 
	jmp .fact 
	
.print: 	
	
	mov edi , num_value
	call itoa 
	push edi 
	mov eax , 4 
	mov ebx , 1 
	mov ecx , factorial 
	mov edx , factorial_len
	int 0x80
	
	pop edi 
	mov eax , 4 
	mov ebx , 1 
	mov ecx , edi 
	mov edx , 12
	int 0x80
	
	mov eax , 4 
	mov ebx ,1 
	mov ecx , newline
	mov edx , 1
	int 0x80

.exit: 
	mov eax ,1 
	xor ebx , ebx 
	int 0x80
	
stoi: 
	xor eax , eax 
	xor ebx , ebx 

.push_loop : 
	mov bl , [esi]
	cmp bl, 0
	je .stoidone
	sub bl , '0' 
	imul eax , 10
	movzx ebx , bl
	add eax , ebx 
	inc esi 
	jmp .push_loop
	
.stoidone : 
	ret
	
	
itoa: 
	
	push edi 
	mov ebx , 10
	mov ecx , 0
.check_loop: 
	xor edx , edx 
	div ebx 	
	push edx 
	inc ecx 
	test eax , eax 
	jnz .check_loop

.write_digits: 
	cmp ecx , 0 
	je .done 
	pop edx 
	add dl , '0' 
	mov [edi] , dl 
	inc edi 
	dec ecx 
	jmp .write_digits

.done: 
	mov byte [edi], 0
	pop edi 
	ret
	
	
	
