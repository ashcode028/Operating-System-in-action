SECTION .data
	msg1: db "1",1
	msg2: db "0",1

SECTION .text
	global _checkGreater


%macro checkGreater 2		;macro definition name and no of parameters
	mov rax,%1		;load 1st parameter to rax
	cmp rax,%2		;compare with second parameter
	jg  _print1		;if greater jump to label print1
        jmp _print0		;else jump to label print2
%endmacro  			;end of macro

_start: 
	mov rdi,43
	mov rsi,13
       call _checkGreater	;call checkGreater 
       ret			 
              
_exit:      
       mov rax,60		;syscall to exit
       mov rdi,0
       syscall
       ret 

_checkGreater: 
	mov rax,rdi		;load 1st parameter to rax
	cmp rax,rsi		;compare with second parameter
	jg  _print1		;if greater jump to label print1
        jmp _print0		;else jump to label print2
        
_print1:			;label to print 1 if x>y
	mov rax,1		;write syscall
	mov rdi,0
	mov rsi,msg1
	mov rdx,1
	syscall
	call _exit		;exit syscall to avoid segmentation fault
	ret 
	
_print0:			;label to print 0 x<y
	mov rax, 1		;syscall to write 0
    	mov rdi, 0
    	mov rsi, msg2
    	mov rdx, 1
    	syscall
    	call _exit		;exit syscall to avoid segmentation fault
    	ret
