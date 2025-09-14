section .data 

	msg1 db 'Enter first string : ' , 0 
	msg1_len equ $ - msg1 
	
	msg2 db 'Enter second string : ', 0 
	msg2_len equ $ - msg2 
	
	out1 db 'Strings are equal' , 0 
	out1_len equ $ - out1
	
	out2 db 'Strings are not equal' , 0 
	out2_len equ $ - out2
	
	newline db 10 
	
section .bss 
	str1 resb 100 
	str2 resb 100 
	len1 resb 4 
	len2 resb 4 
	
	
section .text 
	global _start 
	
_start: 

	mov eax , 4 
	mov ebx , 1
	mov ecx , msg1 
	mov edx , msg1_len 
	int 0x80 
	
	mov eax ,3
	mov ebx ,0 
	mov ecx , str1
	mov edx, 100
	int 0x80 
	
	dec eax 
	mov [len1] , eax 
	
	mov ebx ,eax 	
	mov byte [str1 + ebx ] , 0 
	
	mov eax , 4 
	mov ebx , 1
	mov ecx , msg2 
	mov edx , msg2_len 
	int 0x80 
	
	mov eax ,3
	mov ebx ,0 
	mov ecx , str2
	mov edx, 100
	int 0x80 
	
	dec eax 
	mov [len2] , eax 
	
	mov ebx ,eax 
	mov byte [str2 + ebx ] , 0
	
	
	
	
	mov esi , str1 
	mov edi , str2 
	mov ecx , [len1]
	cmp ecx , [len2] 
	jne .not_equal  	; if string len are not same 
	
	
.loop1: 
	mov  al , [esi] 
	mov bl , [edi]
	
	cmp al , bl 		; if char does not match 
	jne .not_equal 
	inc esi 		; incr index of both strings 
	inc edi 
	loop .loop1 		; decr ecx and loop until the value not equal to 0 
	
.print_result: 
	; if strings are equal 
	mov eax ,4 
	mov ebx ,1 
	mov ecx , out1
	mov edx , out1_len 
	int 0x80 
	
	
	mov eax ,4 
	mov ebx ,1 
	mov ecx , newline
	mov edx , 1 
	int 0x80 
	
	jmp .exit
	
.not_equal: 
	; if strings are not equal 
	mov eax ,4 
	mov ebx ,1 
	mov ecx , out2
	mov edx , out2_len 
	int 0x80 
	
	mov eax ,4 
	mov ebx ,1 
	mov ecx , newline
	mov edx , 1 
	int 0x80 
.exit: 

	; terminate
	mov eax ,1 
	mov ebx ,0 
	int 0x80 
	
	
	 
	
	
