jmpa $MAIN

@INCLUDE("assembly/std/gpu/gpu.asm")

@MACRO(@READ_GPU_INPUT, (@SUCCESS_LABEL),
    push 0x000a
    load
    swap
    pop

    push @SUCCESS_LABEL
    jnz

    pop
    pop
)

$MAIN:
     device 0

    $READ_LOOP:
        @READ_GPU_INPUT($STOP_LOOP)

        jmpa $READ_LOOP

    $STOP_LOOP:
        # Top value now contains adress
        pop

        halt

    halt