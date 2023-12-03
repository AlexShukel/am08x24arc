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
            load # (VALUE1) (RAM ADRESS) ROW (RAM ADRESS) ROW
            swap # (RAM ADRESS) (VALUE1)  ROW (RAM ADRESS) ROW
            @ADD_CONST(1) # (RAM ADRESS + 1) (VALUE1)  ROW (RAM ADRESS) ROW
            load # (VALUE2) (RAM ADRESS + 1) (VALUE1)  ROW (RAM ADRESS) ROW
            swap # (RAM ADRESS + 1) (VALUE2) (VALUE1)  ROW (RAM ADRESS) ROW
            drop # (VALUE2) (VALUE1)  ROW (RAM ADRESS) ROW
        }

        @CONTEXT{@GPU_DEVICE,
            @WAIT_GPU_STATE(@GPU_STATE_READY)

            @SEND_GPU_DATA(@GPU_STATE_REGISTER, @GPU_STATE_MODE_0)

            @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)

            storea 0x0001
            drop
            storea 0x0002
            drop
            storea 0x0003
            drop

            @SEND_GPU_DATA(@GPU_STATE_REGISTER, @GPU_STATE_DATA_UPLOAD_DONE)

            @ADD_CONST(2)
            swap
            @ADD_CONST(1)
            swap

            jmpa $LOOP
        }

    halt