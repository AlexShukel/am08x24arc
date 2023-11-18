jmpa $MAIN

@MACRO(@CODE, (@OPERATIONS), @OPERATIONS)

@CODE(
$MAIN:
    push 0xfff
    pop

    $LABEL:
        push 0xffff
        pop

        jmpa $LABEL

        halt
)
