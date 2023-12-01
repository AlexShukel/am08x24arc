@IF_NOT_DEF(@ARITHMETIC_ASM_INCLUDE_GUARD,
    @MACRO(@ARITHMETIC_ASM_INCLUDE_GUARD, (), ())

    # Todo resolve this cringe
    # @MACRO(@ADD, (),
    #     add
    #     swap
    #     pop
    #     swap
    #     pop
    # )

    @MACRO(@SUB, (),
        sub

        swap
        pop
        swap
        pop
    )

    @MACRO(@ADD_CONST, (@VALUE),
        push @VALUE
        add
        swap
        pop
        swap
        pop
    )

    @MACRO(@INCREMENT, (),
        @ADD_CONST(1)
    )
)