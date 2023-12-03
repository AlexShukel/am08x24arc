jmpa $MAIN

@INCLUDE("assembly/std/io.asm")

@MACRO(@NULLPTR, (), 0x0000)

@MACRO(@SET_GPU_STATE, (@STATE),
    push @STATE
    storea @GPU_STATE_REGISTER
    drop
)

@MACRO(@ADD_CONST, (@VALUE),
    push @VALUE
    add
    swap
    drop
    swap
    drop
)

$WAIT_GPU_STATE_PROC:               # (@STATE0) (RET)
    $WAIT_LOOP:
        loada @GPU_STATE_REGISTER   # (@STATE1) (@STATE0) (RET)

        jea $BREAK
        drop                        # (@STATE0) (RET)

        jmpa $WAIT_LOOP

    $BREAK:
    drop                            # (@STATE0) (RET)
    drop                            # (RET)

    @ADD_CONST(3)
    jmp

@MACRO(@WAIT_GPU_STATE, (@STATE),
    pushpc
    push @STATE
    jmpa $WAIT_GPU_STATE_PROC
    drop
)

$GPU_STATE_0:
    drop
    drop

    @SET_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)

    @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_DONE)

    @CONTEXT{@GPU_DATA_REGISTER,
        loada 0x0001
        loada 0x0002
        loada 0x0003
    }

    @CONTEXT{@GPU_SCREEN_REGISTER,
        storea @NULLPTR
        drop

        storea @NULLPTR
        drop

        storea @NULLPTR
        drop

        store
    }

    jmpa $MAIN

$GPU_STATE_1:
    drop
    drop

    halt

$GPU_STATE_SWAP_BUFFERS:
    drop
    drop

    halt

$MAIN:
    @CONTEXT{@GPU_STATE_REGISTER,
        @SET_GPU_STATE(@GPU_STATE_READY)

        $LOOP:
            loada @NULLPTR

            push @GPU_STATE_MODE_0
            jea $GPU_STATE_0
            drop

            push @GPU_STATE_MODE_1
            jea $GPU_STATE_1
            drop

            push @GPU_STATE_SWAP_BUFFERS
            jea $GPU_STATE_SWAP_BUFFERS
            drop

            drop
            jmpa $LOOP

        # @WAIT_GPU_STATE(@GPU_STATE_MODE_0)
    }

    halt