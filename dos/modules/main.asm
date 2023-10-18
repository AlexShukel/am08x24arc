.model small
.stack 100h

.data

.code
start:
    call myProcedure

    mov     ah, 4ch
    mov     al, 0
    int     21h
end start