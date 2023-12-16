jmpa $MAIN

@INCLUDE("assembly/std/io.asm")

@MACRO(@ROM_DEVICE, (), 0x0000)
@MACRO(@RAM_DEVICE, (), 0x0001)
@MACRO(@GPU_DEVICE, (), 0x0002)

@MACRO(@ADD_CONST, (@VALUE),
    push @VALUE
    add
    swap
    drop
    swap
    drop
)

$WAIT_GPU_STATE_PROC:
    $WAIT_LOOP:
        loada @GPU_STATE_REGISTER

        jea $BREAK
        drop

        jmpa $WAIT_LOOP

    $BREAK:
    drop
    drop

    @ADD_CONST(3)
    jmp

@MACRO(@WAIT_GPU_STATE, (@STATE),
    pushpc
    push @STATE
    jmpa $WAIT_GPU_STATE_PROC
    drop
)

@MACRO(@SEND_GPU_DATA, (@ADRESS, @DATA),
    push @DATA
    storea @ADRESS
    drop
)

@MACRO(@DDUP, (),
    dupn
    dupn
)

$MAIN:
    push 0x0000
    push 0x0000

    $LOOP:
        @DDUP

        @CONTEXT{@ROM_DEVICE,
            @LOAD_WORD
        }

        @CONTEXT{@GPU_DEVICE,
            @WAIT_GPU_STATE(@GPU_STATE_READY)

            @SEND_GPU_DATA(@GPU_STATE_REGISTER, @GPU_STATE_MODE_1)

            @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)

            storeac 0x0001
            storeac 0x0002
            storeac 0x0003

            @SEND_GPU_DATA(@GPU_STATE_REGISTER, @GPU_STATE_DATA_UPLOAD_DONE)

            addat 2
            addan 1

            jmpa $LOOP
        }

    halt