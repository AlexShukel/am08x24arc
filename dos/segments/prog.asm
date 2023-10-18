.model small
.stack 100h

.data   ; Default data segment
var1    db  'Data segment string.$'

extra_data segment
var2    db  'Extra data segment string.$'
extra_data ends

.code   ; Code segment
start:
    mov ax, @data
    mov ds, ax

    ; Print var1 from the data segment
    mov ah, 09h
    lea dx, var1
    int 21h

    ; Set DS to the segment address of extra_data
    mov ax, seg extra_data
    mov ds, ax

    ; Print var2 from the extra_data segment
    mov ah, 09h
    lea dx, var2
    int 21h

    mov     ah, 4ch                  ;DOS: terminate program
    mov     al, 0                    ;return code will be 0
    int     21h                     ;terminate the program

end start
