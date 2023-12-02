jmpa $MAIN

@MACRO(@ROM_DEVICE, (), 0x0000)
@MACRO(@RAM_DEVICE, (), 0x0001)
@MACRO(@GPU_DEVICE, (), 0x0005)

@INCLUDE("assembly/std/arithmetic.asm")
@INCLUDE("assembly/std/procedure.asm")

@INCLUDE("assembly/std/gpu/cpu.asm")

@MACRO(@CONTEXT, (@DEVICE, @BODY),
    device @DEVICE

    @BODY
)

# 0x0001 0x0000
@MACRO(@DDUP, (),
    @CONTEXT{@RAM_DEVICE,
        @TOP_STORE(0x0000)
        pop
        @TOP_STORE(0x0001)
        pop

        @LOAD(0x0001)
        @LOAD(0x0000)
        @LOAD(0x0001)
        @LOAD(0x0000)
    }
)

@MACRO(@SET_GPU_STATE, (@STATE),
    @STORE(@STATE, @GPU_STATE_REGISTER)
)

$MAIN:
    push 0x0000 # ROW
    push 0x0000 # (RAM ADRESS)

    $LOOP:
    @DDUP

    @CONTEXT{@ROM_DEVICE,
        load # (VALUE1) (RAM ADRESS) ROW (RAM ADRESS) ROW
        swap # (RAM ADRESS) (VALUE1)  ROW (RAM ADRESS) ROW
        @ADD_CONST(1) # (RAM ADRESS + 1) (VALUE1)  ROW (RAM ADRESS) ROW
        load # (VALUE2) (RAM ADRESS + 1) (VALUE1)  ROW (RAM ADRESS) ROW
        swap # (RAM ADRESS + 1) (VALUE2) (VALUE1)  ROW (RAM ADRESS) ROW
        pop # (VALUE2) (VALUE1)  ROW (RAM ADRESS) ROW
    }

    @CONTEXT{@GPU_DEVICE,
        @WAIT_GPU_STATE(@GPU_STATE_READY)
    }

    @CONTEXT{@GPU_DEVICE,
        @STORE(@GPU_STATE_MODE_0, @GPU_STATE_REGISTER)

        @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)
        @TOP_STORE(@GPU_DATA_REGISTER)
        pop
        @STORE(@GPU_STATE_DATA_UPLOAD_DONE, @GPU_STATE_REGISTER)

        @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)
        @TOP_STORE(@GPU_DATA_REGISTER)
        pop
        @STORE(@GPU_STATE_DATA_UPLOAD_DONE, @GPU_STATE_REGISTER)

        @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)
        @TOP_STORE(@GPU_DATA_REGISTER)
        pop
        @STORE(@GPU_STATE_DATA_UPLOAD_DONE, @GPU_STATE_REGISTER)
    }

    @CONTEXT{@GPU_DEVICE,
        @WAIT_GPU_STATE(@GPU_STATE_READY)
    }

    @ADD_CONST(2)
    swap
    @ADD_CONST(1)
    swap

        jmpa $LOOP

    halt