jmpa $MAIN

@INCLUDE("assembly/std/stack.asm")

@MACRO(@STORE_TOP_AT, (@ADRESS),
    push @ADRESS
    store
    pop
)

@MACRO(@LOAD_TOP_AT, (@ADRESS),
    push @ADRESS
    load
    swap
    pop
)

@MACRO(@ADD, (),
    add
    swap
    pop
    swap
    pop
)

@MACRO(@ROTATE_TOP, (),
    @STORE_TOP_AT(0xfff0)
    pop

    @STORE_TOP_AT(0xfff1)
    pop

    @STORE_TOP_AT(0xfff2)
    pop

    @LOAD_TOP_AT(0xfff1)
    @LOAD_TOP_AT(0xfff2)
    @LOAD_TOP_AT(0xfff0)
)

$MAIN:
    @PUSH2(0, 1)

    $LOOP:
        dup
        @ROTATE_TOP
        @ADD

       jmpa 3

    halt