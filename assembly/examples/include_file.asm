# Hacked in basic include support
# does not support comments in included files
# but yes

jmpa $MAIN

@INCLUDE("assembly/std/stack.asm")

$MAIN:
    @PUSH5(0x0001, 0x0002, 0x0003, 0x0004, 0x0005)

    @POP5

    halt