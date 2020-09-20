SECTION .text
	global _long_add32
       
_long_add32: 	
	push ebp
	mov ebp,esp
	mov edx,[ebp+8]
	mov eax,[ebp+12]
	add eax,edx
	mov edx,[ebp+16]
	add eax,edx
	mov edx,[ebp+20]
	add eax,edx
	mov esp,ebp
	pop ebp
	ret
