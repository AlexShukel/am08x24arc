@IF_NOT_DEF(@PUSH_ASM_INCLUDE_GUARD,
    @MACRO(@PUSH_ASM_INCLUDE_GUARD, (), ())

    @MACRO(@PUSH1, (@ARG1),
        push @ARG1
    )

    @MACRO(@PUSH2, (@ARG1, @ARG2),
        push @ARG1
        push @ARG2
    )

    @MACRO(@PUSH3, (@ARG1, @ARG2, @ARG3),
        push @ARG1
        push @ARG2
        push @ARG3
    )

    @MACRO(@PUSH4, (@ARG1, @ARG2, @ARG3, @ARG4),
        push @ARG1
        push @ARG2
        push @ARG3
        push @ARG4
    )

    @MACRO(@PUSH5, (@ARG1, @ARG2, @ARG3, @ARG4, @ARG5),
        push @ARG1
        push @ARG2
        push @ARG3
        push @ARG4
        push @ARG5
    )
)