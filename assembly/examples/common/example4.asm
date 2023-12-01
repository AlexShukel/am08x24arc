jmpa $MAIN

@INCLUDE("assembly/std/stack.asm")

@MACRO(@PRINT_C, (@CHARACTER),
    push @CHARACTER
    push 0
    store
    @POP2
)

@MACRO(@CLEAR_DISPLAY, (),
    push 0xffff
    push 0
    store
    @POP2
)

@MACRO(@DISPLAY_LINE, (@LINE, @PIXELS),
    push @PIXELS
    push @LINE
    store
    @POP2
)

$MAIN:

device 2

@PRINT_C('h')
@PRINT_C('e')
@PRINT_C('l')
@PRINT_C('l')
@PRINT_C('o')
@PRINT_C('_')
@PRINT_C('w')
@PRINT_C('o')
@PRINT_C('r')
@PRINT_C('l')
@PRINT_C('d')
@PRINT_C('!')

@PRINT_C('I')
@PRINT_C('d')
@PRINT_C('i')
@PRINT_C('_')
@PRINT_C('n')
@PRINT_C('a')
@PRINT_C('h')
@PRINT_C('u')
@PRINT_C('j')

@CLEAR_DISPLAY

jmpa $MAIN

halt