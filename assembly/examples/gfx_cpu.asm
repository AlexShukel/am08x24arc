jmpa $MAIN

@INCLUDE("assembly/std/stack.asm")
@INCLUDE("assembly/std/memory.asm")

@MACRO(@SEND_TO_GPU, (@DATA),
    push @DATA

    @STORE_TOP_AT(0xffff)

    pop
)

$MAIN:
    device 4

    @SEND_TO_GPU(0xffff)

    halt