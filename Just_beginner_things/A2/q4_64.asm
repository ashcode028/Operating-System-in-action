SECTION .text
	global _long_add64
       
_extended_add:
	sub rsp,16
	mov rdx,[rbp+16]
	mov rax,[rbp+24]
	add rax,rdx
	mov rdx,[rbp+32]
	add rax,rdx
	mov rdx,[rbp+40]
	add rax,rdx
	;mov rsp,rbp
	add rsp,16
	ret

_long_add64:
	mov rax,rdi
	add rax,rsi
	add rax,rcx
	add rax,rdx
	ret 
