.model small
.data

num1    dd  10.5   ; First number
num2    dd  0.9    ; Second number
result  dd  ?      ; Result
msg     db  "Result: $"
ten     dw 10      ; Decimal 10 for division
endl    db 13, 10, '$'

.code
start:

; Initialize data segment
mov ax, @data
mov ds, ax

; ADDITION
fld num1       ; Load num1 to ST(0)
fadd num2      ; Add num2 to ST(0)
fist result    ; Store integer part from ST(0) to 'result'
call display_result

; SUBTRACTION
fld num1
fsub num2
fist result
call display_result

; MULTIPLICATION
fld num1
fmul num2
fist result
call display_result

; DIVISION
fld num1
fdiv num2
fist result
call display_result

; Exit to DOS
mov ax, 4C00h
int 21h

display_result proc
    ; Display message
    mov ah, 09h
    lea dx, msg
    int 21h

    ; Display result (assuming result < 1000 for simplicity)
    mov ax, word ptr [result]
    call print_num
    call print_endl
    ret
display_result endp

print_endl proc
    mov ah, 09h
    lea dx, endl
    int 21h
    ret
print_endl endp

print_num proc
    local buffer[6]

    ; Point BX to the end of the buffer
    lea bx, buffer[5] ; point to the last byte
    mov byte ptr [bx], '$' ; null-terminator for DOS string print

    ; Check if number is zero
    test ax, ax
    jz isZero

beginLoop:
    dec bx               ; Move buffer pointer backwards
    xor dx, dx           ; Clear any previous high word before division
    div word ptr ds:[ten] ; Divide AX by 10, result in AX, remainder in DX

    ; Convert remainder (0-9) to ASCII and store in buffer
    add dl, '0'
    mov [bx], dl

    test ax, ax          ; Test if quotient is zero
    jnz beginLoop       ; If not, continue loop

    jmp print

isZero:
    dec bx               ; Move buffer pointer backwards
    mov byte ptr [bx], '0'

print:
    ; Print number string
    mov ah, 09h
    mov dx, bx
    int 21h

    ret
print_num endp

end start
