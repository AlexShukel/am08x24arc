@MACRO(@CODE, (@OPERATIONS), @OPERATIONS)

@CODE(
    push 0xfff
    pop

    $LABEL:
        push 0xffff
        pop

        jmpa $LABEL
)
