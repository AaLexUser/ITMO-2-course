%include "lib.inc"
%include "dict.inc"
%include "colon.inc"
%include "words.inc"

%define BUFFER_SIZE 256

section .bss
buffer: resb BUFFER_SIZE


section .rodata
buffer_overflow: db "The maximum string length is 255 characters", 0
dict_not_found: db "There is no such element in the dictionary", 0

section .text
global _start
_start:
	mov 	rdi, buffer
	mov		rsi, BUFFER_SIZE
	
	call	read_string
	mov 	rdi, rax
	test 	rax, rax
	jz		.overflow

	mov 	rsi, NEXT
	call	find_word
	test	rax, rax
	je		.not_found
	
	mov		rdi, rax
	add		rdi, 8
	call	string_length
	lea		rdi, [rdi + rax + 1]
	call	print_string
	call	print_newline
	jmp		.exit
	
.overflow:
	mov	rdi, buffer_overflow
	jmp	.print_error
.not_found:
	mov	rdi, dict_not_found
.print_error:
	call 	print_err
	call 	print_newline
.exit:	
	call	exit
		

