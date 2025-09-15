section .data 
	msg1 db 'Enter the string: ', 0 
	msg1_len equ $ - msg1 
	
	msg2 db 'Count', 10, 0
	newline db 10 
	colon db ' : ' , 0
	
	
section .bss 
	str1 resb 256 
	str1_len resb 4
	count resb 1 
	
section .text
	global _start 

_start: 

	mov eax , 4 
	mov ebx , 1 
	mov ecx , msg1 
	mov edx , msg1_len 
	INT 0x80 
	
	
	    ; Read string
    mov eax, 3 
    mov ebx, 0 		;stdin (read) 
    mov ecx, str1
    mov edx, 256
    int 0x80 
    
    dec eax		;remove the \n character 
    mov byte [str1 + eax], 0	; insert \0 character to the end of the string 
    
	mov edi , str1  ; main pointer 

	
	
.loop1: 
	mov esi , str1  ;  reset index pointer 
	mov dl , [edi] 
	mov ecx , 0 	; initialize/ reset the count with 0 
	
	
	cmp dl , 0 	; read the complete string 
	je .exit 
	
.loop2: 
	mov al , [esi]  	
	cmp al ,  0 		; check for null terminator 
	je .print_result 
	
	cmp al , dl 	; check both the pointers
	jne .skip	; skip to the next character 
	inc ecx		; increment counter

	
.skip: 
	inc esi		
	jmp .loop2 
	
	

	
.print_result: 
	
	add cl , '0' 		; convert the count value to ASCII 
	
	mov [count] , cl 	; store the value in the count variable 
	
	; print the current char
	mov eax , 4 
	mov ebx , 1 
	mov ecx ,edi
	mov edx , 1 
	int 0x80 
	
	; print colon
	mov eax , 4 
	mov ebx , 1 
	mov ecx ,colon
	mov edx , 3
	int 0x80 
	
	;print count 
	mov eax , 4 
	mov ebx ,1 
	mov ecx , count
	mov edx , 1
	int 0x80 
	
	; print newline 
	mov eax , 4 
	mov ebx ,1 
	mov ecx , newline
	mov edx , 1
	int 0x80 
	
	
	; repeat the same process for every char in the string 
	inc edi
	jmp .loop1 
	
.exit: 
	; terminate 
	mov eax , 1
	mov ebx ,0 
	int 0x80 

	
