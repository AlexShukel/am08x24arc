jmpa $MAIN

@MACRO(@CODE, (@OPERATIONS), @OPERATIONS)

@INCLUDE("std.asm")

@NOTIFY{"You can use \{ macroscopes \} like this"}
@NOTIFY("This is a, simple macro")

@CODE{
$MAIN:
    push 0xfff
    pop

    $LABEL:
        push 0xffff
        pop

        jmpa $LABEL

        halt
}
