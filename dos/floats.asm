.model small
.data

num1    dd  10.5   ; First number
num2    dd  5.5    ; Second number
result  dd  ?      ; Result
msg     db  "Result: $"

.code
start:

; Initialize data segment
mov ax, @data
mov ds, ax

; ADDITION
fld num1       ; Load num1 to ST(0)
fadd num2      ; Add num2 to ST(0)
fist result    ; Store integer part from ST(0) to 'result'
display_result

; SUBTRACTION
fld num1
fsub num2
fist result
display_result

; MULTIPLICATION
fld num1
fmul num2
fist result
display_result

; DIVISION
fld num1
fdiv num2
fist result
display_result

; Exit to DOS
mov ax, 4C00h
int 21h

display_result proc
    ; Display message
    mov ah, 09h
    lea dx, msg
    int 21h

    ; Display result (assuming result < 1000 for simplicity)
    mov ax, [result]
    call print_num
    ret
display_result endp

; A simple procedure to print a number
print_num proc
    ; ... Convert AX into string and print ...
    ; For the sake of brevity, implement this based on your needs
    ret
print_num endp

end start
