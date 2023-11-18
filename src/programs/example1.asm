@NOTIFY{"You can use \{ macroscopes \} like this"}

jmpa $MAIN

@MACRO(@CODE, (@OPERATIONS), @OPERATIONS)

@INCLUDE("std.asm")

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
