@IF_NOT_DEF(@GUARD,
    @MACRO(@GUARD, (), ())

    @MACRO(@PUSH2, (@ARG1, @ARG2),
        push @ARG1
        push @ARG2
    )

    @MACRO(@PUSH3, (@ARG1, @ARG2, @ARG3),
        push @ARG1
        push @ARG2
        push @ARG3
    )

    @PUSH2(0xffff, 0xffff)
    @PUSH3(0xffff, 0xffff, 0xffff)
)

@IF_NOT_DEF(@GUARD,
    @MACRO(@GUARD, (), ())

    push 0xffff
    push 0xffff
)

@IF_NOT_DEF(@GUARD,
    @MACRO(@GUARD, (), ())

    push 0xffff
    push 0xffff
)