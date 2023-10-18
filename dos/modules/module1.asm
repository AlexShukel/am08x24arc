; module1.asm

.model small

.data
    msg db "Hello, world!$"

.code

myProcedure proc
    mov ah, 09h
    mov dx, offset msg
    int 21h
ret
myProcedure endp

end
