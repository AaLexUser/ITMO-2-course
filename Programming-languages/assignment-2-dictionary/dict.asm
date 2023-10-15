%include "lib.inc"
global find_word
section .text
; Принимает: 
; rdi - Указатель на нуль-терминированную строку.
; rsi - Указатель на начало словаря.
; Проходит по всему словарю в поисках подходящего ключа. 
; Если подходящее вхождение найдено, вернёт адрес начала вхождения в
; словарь (не значения), иначе вернёт 0.
find_word:
	mov	rcx, rsi
.loop:
	lea	rsi, [rcx + 8]
	push	rcx
	call	string_equals
	pop	rcx
	cmp	rax, 1
	je 	.end
	cmp	qword[rcx], 0
	je	.err
	mov	rcx, [rcx]
	jmp	.loop	
.end:
	mov	rax, rcx
	ret
.err:
	ret			; rax is already zero
