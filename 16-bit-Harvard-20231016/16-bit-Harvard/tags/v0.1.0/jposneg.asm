        LDC -3
        JNEG NEXT
        LDC 666
        OUT 0
NEXT:   LDC 0
        JPOS BAD
        LDC 12345
        OUT 0
        JMP END
BAD:    LDC 777
        OUT 0
END:    HALT
