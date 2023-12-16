@MACRO(@JMP_IN_RANGE, (@ARG1,@ARG2,@ARG3,@LABEL),
    cmp @ARG1\, @ARG2
    jl  not_in_range_@LABEL
    cmp @ARG1\, @ARG3
    jg  not_in_range_@LABEL
    jmp @LABEL

    not_in_range_@LABEL:
)

@JMP_IN_RANGE(ax, 5, 15,poggers)