SYS_PRINT_STRING equ 09h
SYS_EXIT equ 4ch

.model small
.stack 100h

.data
    msg db "Hello, world!$"
.code

start:
    push @data
    pop ds

    mov ah, SYS_PRINT_STRING
    mov dx, offset msg
    int 21h

    mov ah, SYS_EXIT
    mov al, 0
    int 21h
end start
