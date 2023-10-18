SYS_EXIT equ 4c00h
SYS_WRITE_TO_FILE_WITH_HANDLE equ 4000h

.model small
.stack 100h

.data
    endl db 13, 10, '$'
    buff db 255, ?, 255 dup(?)

.code

BUFFERED_KEYBOARD_INPUT MACRO buff:REQ
    mov ax, 0a00h
    mov dx, offset buff
    int 21h
ENDM

PRINT_STRING MACRO buff:REQ
    mov ax, 0900h
    mov dx, offset buff
    int 21h
ENDM

WRITE_TO_FILE_WITH_HANDLE MACRO p_file_handle:REQ, p_bytes_length:REQ
    mov ax, SYS_WRITE_TO_FILE_WITH_HANDLE
    mov bx, p_file_handle
    mov cl, p_bytes_length
    xor ch, ch
    int 21h
ENDM

start:
    push @data
    pop ds

    BUFFERED_KEYBOARD_INPUT buff

    PRINT_STRING endl

    mov dx, offset buff + 2
    mov cl, [buff + 1]
    WRITE_TO_FILE_WITH_HANDLE 1, cl

    mov ax, SYS_EXIT
    int 21h

end start
