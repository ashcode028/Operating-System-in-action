# Printing 'Hello World' and the contents of CR0 in a bootloader
How to run the bootloader in qemu
    ```nasm boot.asm -f bin -o boot.bin```
    ```qemu-system-x86_64 -fda boot.bin```

## Description of code and implementation details
### Overview of Bootloader
    1. Start the bootloader in the 16 bit Real mode. 
    2. Enable Protected Mode
    3. Switch to the 32 bit mode
    4. Enable GDT for 32 bit mode
    5. Then print to VGA
### Logical and Implementation Details
    A. Entering Real Mode - 
        a. Start with 16 Bits of the Real Mode
        b. 'org' command tells the program where (location) to load the boot file to
        c. Disable all the interrupts in order to prevent race condition using interrupt handler
        d. Load the pointer to the GDT Table. (Here,gdt_pointer belongs to the 32 Bit GDT Table)
        e. Make the first bit of CR0 as 1 (The first bit represents the Protected Mode Bit)
        f. Jump to the code segment of 32 Bits
    B. Inside the Protected 32 Bit Mode
        a. Enable the 32 Bit GDT Table
        b. Set the Code and the Data segment addresses
        c. Set the Segment registers in 32 bit 
    C. Print hello world
        a.point esi to memory location of hello world
        b.load current byte to al ans increment esi using load string byte instruction
        c.if al==0
            - jump to next label to print cr0 contents
        d. else print the current byte to vga 
    D. Print contents of CR0 register-in binary-32 bits
        a. setting offset to vga buffer 
        b. mov cr0 to data register 
        c. set ecx (as counter) to 32 
        d. set the screen to blue on black
        e. left shift the edx to get top byte to carry flag
        f. AL="0" or AL="1"-add with carry
        g. print to current vga buffer location
        h. change offset -increase it by 2 bytes
        i. decrease value of counter
        j. continue till its zero 
    E.halt
        clear interuppt flag and halt execution
## sources-
https://dev.to/frosnerd/writing-my-own-boot-loader-3mld
https://blog.ghaiklor.com/2017/10/21/how-to-implement-your-own-hello-world-boot-loader/
https://www.codeproject.com/Articles/45788/The-Real-Protected-Long-mode-assembly-tutorial-for
https://stackoverflow.com/questions/36968829/how-to-switch-from-real-mode-to-protected-mode-after-bootloader
http://3zanders.co.uk/2017/10/16/writing-a-bootloader2/
https://stackoverflow.com/questions/40381594/printing-characters-to-screen-asm-in-protected-mode
https://medium.com/@g33konaut/writing-an-x86-hello-world-boot-loader-with-assembly-3e4c5bdd96cf
http://mikeos.sourceforge.net/write-your-own-os.html
