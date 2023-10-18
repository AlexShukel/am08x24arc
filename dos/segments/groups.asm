.model small
.stack 100h

.data1 segment
    var1 db 'Hello from data1 segment.$'
.data1 ends

.data2 segment
    var2 db 'Hello from data2 segment.$'
.data2 ends

DGROUP group .data1, .data2

.code   ; Code segment
start:
    mov ax, DGROUP
    mov ds, ax

    ; Print var1 from the data segment
    mov ah, 09h
    lea dx, var1
    int 21h

    ; Print var2 from the extra_data segment
    mov ah, 09h
    lea dx, var2
    int 21h

    mov     ah, 4ch                  ;DOS: terminate program
    mov     al, 0                    ;return code will be 0
    int     21h                     ;terminate the program

end start
