SCALE:  EQU 100
NUM:    EQU 0
A:      EQU 1
A2:     EQU 2
        ;; 
        IN 0
        MULC SCALE
        ST A
        MULC SCALE
        ST NUM
LOOP:   LD A
        ST A2
        LD NUM
        DIV A2
        ADD A2
        DIVC 2
        ST A
        OUT 0
        SUB A2
        JNZ LOOP
END:    HALT
