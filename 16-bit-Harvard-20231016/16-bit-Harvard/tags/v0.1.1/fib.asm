        ;; Fibonacci numbers
N1:     EQU 0
N2:     EQU 1
CNT:    EQU 2
MAX:    EQU 10
        ;;
        LDC 1
        ST N1
        ST N2
        LDC 0
        ST CNT
LOOP:   LD N2
        ADD N1
        OUT 0
        ST N2
        SUB N1
        ST N1
        LD CNT
        ADDC 1
        ST CNT
        SUBC MAX
        JNEG LOOP
END:    HALT
