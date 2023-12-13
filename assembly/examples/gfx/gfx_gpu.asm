jmpa $MAIN

@INCLUDE("assembly/std/io.asm")

@INCLUDE("assembly/examples/gfx/gpu_mode_0.asm")
@INCLUDE("assembly/examples/gfx/gpu_mode_1.asm")

@MACRO(@NULLPTR, (), 0x0000)

@MACRO(@SET_GPU_STATE, (@STATE),
    push @STATE
    storeac @GPU_STATE_REGISTER
)

$WAIT_GPU_STATE_PROC:
    $WAIT_LOOP:
        loada @GPU_STATE_REGISTER
        jeac $BREAK
        jmpa $WAIT_LOOP

    $BREAK:
    drop

    addat 3
    jmp

@MACRO(@WAIT_GPU_STATE, (@STATE),
    pushpc
    push @STATE
    jmpa $WAIT_GPU_STATE_PROC
    drop
)

$GPU_STATE_SWAP_BUFFERS:
    drop

    halt

$MAIN:
    @CONTEXT{@GPU_STATE_REGISTER,
        @SET_GPU_STATE(@GPU_STATE_READY)

        $LOOP:
            loada @NULLPTR

            push @GPU_STATE_MODE_0
            jeac $GPU_STATE_0

            push @GPU_STATE_MODE_1
            jeac $GPU_STATE_1

            push @GPU_STATE_SWAP_BUFFERS
            jeac $GPU_STATE_SWAP_BUFFERS

            drop
            jmpa $LOOP
    }

    halt