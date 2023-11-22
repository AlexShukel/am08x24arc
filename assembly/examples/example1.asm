jmpa $MAIN

@MACRO(@CODE, (@OPERATIONS), @OPERATIONS)

@NOTIFY{"You can use \{ macroscopes \} like this"}
@NOTIFY("This is a, simple macro")

@CODE {
$MAIN:
    push 0xffff
    pop

    $LABEL:
        push 0xffff
        pop

        jmpa $LABEL

        halt
}
