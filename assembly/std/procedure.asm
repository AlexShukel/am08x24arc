@IF_NOT_DEF(@PROCEDURE_ASM_INCLUDE_GUARD,
    @MACRO(@PROCEDURE_ASM_INCLUDE_GUARD, (), ())

    @MACRO(@DECL_PROC, (@PROC_NAME, @BODY),
        @PROC_NAME:
            @BODY

            @ADD_CONST(2)
            jmpt
    )

    @MACRO(@CALL, (@PROC_NAME),
        pushpc
        jmpa @PROC_NAME
        pop
    )

    @MACRO(@JMP_EQL, (@ADRESS),
        cmp
        push @ADRESS
        jz
    )

    @MACRO(@JMP_NEQL, (@ADRESS),
        cmp
        push @ADRESS
        jnz
    )
)