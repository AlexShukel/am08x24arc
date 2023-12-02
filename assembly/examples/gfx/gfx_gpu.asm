jmpa $MAIN

@INCLUDE("assembly/std/gpu/gpu.asm")

@INCLUDE("assembly/std/arithmetic.asm")
@INCLUDE("assembly/std/procedure.asm")

@MACRO(@CONTEXT, (@DEVICE, @BODY),
    device @DEVICE

    @BODY
)

@DECL_PROC($WAIT_STATE_PROC,
    swap

    $WAIT_STATE_PROC_LOOP:
        dup

        load # Get state

        @JMP_EQL($WAIT_STATE_PROC_LOOP_BREAK)
        pop

        jmpa $WAIT_STATE_PROC_LOOP

    $WAIT_STATE_PROC_LOOP_BREAK:
        pop

    swap
)

@MACRO(@WAIT_STATE, (@STATE),
    push @STATE
    @CALL($WAIT_STATE_PROC)
    pop
)

$GPU_STATE_0:
    @POP2 # Popping adress, mode value

    # Lets get value 1
    @CONTEXT{@GPU_STATE_REGISTER,
        @MARK_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)
        @WAIT_STATE(@GPU_STATE_DATA_UPLOAD_DONE)
    }

    @CONTEXT{@GPU_DATA_REGISTER,
        load
    }

    # Lets get value 2
    @CONTEXT{@GPU_STATE_REGISTER,
        @MARK_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)
        @WAIT_STATE(@GPU_STATE_DATA_UPLOAD_DONE)
    }

    @CONTEXT{@GPU_DATA_REGISTER,
        load
    }

    # Lets get adress
    @CONTEXT{@GPU_STATE_REGISTER,
        @MARK_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)
        @WAIT_STATE(@GPU_STATE_DATA_UPLOAD_DONE)

        @MARK_GPU_STATE(@GPU_STATE_BUSY)
    }

    @CONTEXT{@GPU_DATA_REGISTER,
        load
    }

    @CONTEXT{@GPU_SCREEN_REGISTER,
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

    push 0x0020
    halt

    jmpa $MAIN

$GPU_STATE_SWAP_BUFFERS:
    @POP2

    push 0x0030
    halt

    jmpa $MAIN

@MACRO(@MARK_GPU_STATE, (@STATE),
    @STORE(@STATE, @NULLPTR)
)

$MAIN:
    @CONTEXT{@GPU_STATE_REGISTER,
        @MARK_GPU_STATE(@GPU_STATE_READY)
    }

    $LOOP:
        @CONTEXT{@GPU_STATE_REGISTER,
            load
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

        pop
        jmpa $LOOP

    halt