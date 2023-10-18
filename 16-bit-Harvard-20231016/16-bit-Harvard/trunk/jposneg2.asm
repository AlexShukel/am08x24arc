        LDC 100
        JPOS NEXT
        LDC 666
        OUT 0
NEXT:   LDC 56
        JNEG BAD
        LDC 12345
        OUT 0
        JMP END
BAD:    LDC 777
        OUT 0
END:    HALT
