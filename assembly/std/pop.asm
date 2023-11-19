@IF_NOT_DEF(@POP_ASM_INCLUDE_GUARD,
    @MACRO(@POP_ASM_INCLUDE_GUARD, (), ())

    @MACRO(@POP1, (),
        pop
    )

    @MACRO(@POP2, (),
        pop
        pop
    )

    @MACRO(@POP3, (),
        pop
        pop
        pop
    )

    @MACRO(@POP4, (),
        pop
        pop
        pop
        pop
    )

    @MACRO(@POP5, (),
        pop
        pop
        pop
        pop
        pop
    )
)