jmpa $MAIN

@INCLUDE("assembly/std/stack.asm")

@MACRO(@ADD, (),
    add
    swap
    drop
    swap
    drop
)

@MACRO(@ROTATE_TOP, (),
    device 1

    storeac 0xfff0
    storeac 0xfff1
    storeac 0xfff2

    loada 0xfff1
    loada 0xfff2
    loada 0xfff0
)

$MAIN:
    push 0
    push 1

    $LOOP:
        dupt
        @ROTATE_TOP
        @ADD

        device 3
        dupt
        storeac 0x0000

       jmpa 3

    halt