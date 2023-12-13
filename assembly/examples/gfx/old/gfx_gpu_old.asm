jmpa $MAIN

@INCLUDE("assembly/std/gpu/gpu.asm")

@INCLUDE("assembly/std/arithmetic.asm")
@INCLUDE("assembly/std/procedure.asm")

@MACRO(@GPU_INPUT_DEVICE, (), 0x0000)
@MACRO(@GPU_SCREEN_DEVICE, (), 0x0007)

@DECL_PROC($READ_GPU_INPUT,
    $READ_LOOP:
        push 0x000a
        load
        swap
        pop

        push $STOP_LOOP
        jnz

        pop
        pop

        jmpa $READ_LOOP

    $STOP_LOOP:
        pop

    swap
)

@MACRO(@CONTEXT, (@DEVICE, @BODY),
    device @DEVICE

    @BODY
)

$GPU_STATE_SWAP_BUFFERS:
    @POP2

    @CONTEXT{@GPU_INPUT_DEVICE,
        @MARK_GPU_STATE(@GPU_STATE_BUSY)
    }

    @CONTEXT{@GPU_SCREEN_DEVICE,
        @STORE(0xffff, @NULLPTR)
        @STORE(0xffff, @NULLPTR)
        @STORE(0xffff, @NULLPTR)

        store
    }

    @CONTEXT{@GPU_INPUT_DEVICE,
        @MARK_GPU_STATE(@GPU_STATE_READY)
    }

    jmpa $MAIN

$GPU_STATE_0:
    @POP2 # Popping adress, mode value

    @CONTEXT{@GPU_INPUT_DEVICE,
        @MARK_GPU_STATE(@GPU_STATE_READY)
        @CALL($READ_GPU_INPUT)

        @MARK_GPU_STATE(@GPU_STATE_READY)
        @CALL($READ_GPU_INPUT)

        @MARK_GPU_STATE(@GPU_STATE_READY)
        @CALL($READ_GPU_INPUT)

        @MARK_GPU_STATE(@GPU_STATE_BUSY)
    }

    @CONTEXT{@GPU_SCREEN_DEVICE,
        @TOP_STORE(@NULLPTR)
        pop

        @TOP_STORE(@NULLPTR)
        pop

        @TOP_STORE(@NULLPTR)
        pop

        store
    }

    jmpa $MAIN

$GPU_STATE_1:
    @POP2 # Popping adress, mode value

    @CONTEXT{@GPU_INPUT_DEVICE,
        @MARK_GPU_STATE(@GPU_STATE_READY)
    }

    jmpa $MAIN



$MAIN:
    @CONTEXT{@GPU_INPUT_DEVICE,
        @MARK_GPU_STATE(@GPU_STATE_READY)

        @CALL($READ_GPU_INPUT)

        @MARK_GPU_STATE(@GPU_STATE_BUSY)
    }

    dup
    push @GPU_STATE_MODE_0
    @JMP_EQL($GPU_STATE_0)
    pop

    dup
    push @GPU_STATE_MODE_1
    @JMP_EQL($GPU_STATE_1)
    pop

    dup
    push @GPU_STATE_SWAP_BUFFERS
    @JMP_EQL($GPU_STATE_SWAP_BUFFERS)
    pop

    halt