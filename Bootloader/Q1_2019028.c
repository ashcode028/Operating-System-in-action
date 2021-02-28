bits 16			; Start with 16 Bits of the Real Mode
org 0x7c00			; org tells the program where (location) to load the boot file to

boot:
	mov ax, 0x2401		;
	int 0x15		;enable A20 bit
	mov ax, 0x3		;
	int 0x10		;set vga text mode
	cli			;clear interupts
	lgdt [gdt_pointer]	;load gdt table
	mov eax, cr0		;
	or eax,0x1		;set the protected mode bit on special CPU reg cr0
	mov cr0, eax		;set last bit to cr0 bit -enables protected mode 
	jmp CODE_SEG:boot2	;jump to the code segment

; gdt_start and gdt_end labels are used to compute size	
gdt_start:			; null segment descriptor
	dq 0x0
gdt_code:			; code segment descriptor
	dw 0xFFFF		; segment length, bits 0-15
	dw 0x0			; segment base, bits 0-15
	db 0x0			; segment base, bits 16-23
	db 10011010b		; flags 8 bits
	db 11001111b		; flags 4 bits + segment length, bits 16-19
	db 0x0			; segment base, bits 24-31
gdt_data:			; data segment descriptor
	dw 0xFFFF		; segment length, bits 0-15
	dw 0x0			; segment base, bits 0-15
	db 0x0			; segment base, bits 16-23
	db 10010010b		; flags (8 bits)
	db 11001111b		; flags (4 bits) + segment length, bits 16-19
	db 0x0			; segment base, bits 24-31
gdt_end:
gdt_pointer:			; GDT descriptor
	dw gdt_end - gdt_start ; size (16 bit)
	dd gdt_start		; address (32 bit)

CODE_SEG equ gdt_code - gdt_start	; Address of the code segment is address of code wrt address of start
DATA_SEG equ gdt_data - gdt_start	; Address of the data segment is address of data wrt address of start

bits 32
boot2:
	mov ax, DATA_SEG	;point all segment registers to data segment
	mov ds, ax		
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	
	mov esi,hello		;point esi to memory location of hello world
    	mov ebx,0xb8000	;vga buffer
.loop:
    	lodsb			;load string byte instruction which loads byte at address ds:si into al
    	or al,al             ; is al == 0 ?
    	jz boot3		; if (al == 0) jump to next label
    	or eax,0x0100		; runs BIOS interrupt 0x10 - Video Services
    	mov word [ebx], ax
    	add ebx,2
    	jmp .loop

boot3:
	mov ebx, 0xb8000 + 26		; Setting the VGA Buffer after the length of the buffer
	mov edx,cr0			;load the register to be printed 
	mov ecx,32			;binary counter
.loop:
	mov eax, 0x00130	; BlueOnBlack "0"
    	shl edx, 1             ; Top bit to the carry flag-left shift
    	adc eax, 0             ; AL="0" or AL="1"-add with carry
    	mov [ebx], ax		;printing to vga buffer
    	add ebx, 2		;changing offset
    	dec ecx		;decrease the value of counter
    	jnz .loop		;continue till ecx isnt negative
    	
halt:
	cli			; clear interrupt flag
	hlt			; halt execution
hello: db "Hello World!",0



times 510 - ($-$$) db 0	; pad remaining bytes with zeroes
dw 0xaa55			;marks this 512 byte sector bootable
    
