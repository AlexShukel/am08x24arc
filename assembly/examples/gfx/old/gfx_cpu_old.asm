jmpa $MAIN

@MACRO(@ROM_DEVICE, (), 0x0000)
@MACRO(@RAM_DEVICE, (), 0x0001)
@MACRO(@GPU_DEVICE, (), 0x0005)

@INCLUDE("assembly/std/arithmetic.asm")
@INCLUDE("assembly/std/procedure.asm")

@INCLUDE("assembly/std/gpu/cpu.asm")

@MACRO(@SEND_GPU_DATA, (@DATA),
    @STORE(@DATA, @NULLPTR)
    @WAIT_GPU_STATE(@GPU_STATE_READY)
)

@MACRO(@SEND_TOP_GPU_DATA, (),
    @TOP_STORE(@NULLPTR)
    @WAIT_GPU_STATE(@GPU_STATE_READY)
)

@MACRO(@GPU_SWAP_BUFFERS, (),
    @SEND_GPU_DATA(@GPU_STATE_SWAP_BUFFERS)
)

@MACRO(@CONTEXT, (@DEVICE, @BODY),
    device @DEVICE

    @BODY
)

# 0x0001 0x0000
@MACRO(@DDUP, (),
    @CONTEXT{@RAM_DEVICE,
        @TOP_STORE(0x0000)
        @TOP_STORE(0x0001)

        @LOAD(0x0000)
        @LOAD(0x0001)
    }
)

@MACRO(@SEND_RAM_ADRESS_ROW, (@ADRESS, @ROW),
    push @ROW               # ROW
    push @ADRESS            # ADRESS ROW

    @CONTEXT{@ROM_DEVICE,
        load                # VALUE ADRESS ROW

        swap                # ADRESS VALUE ROW
        @INCREMENT          # (ADRESS+1) VALUE ROW

        load                # VALUE2 (ADRESS+1) VALUE1 ROW
        swap                # (ADRESS+1) VALUE2 VALUE1 ROW
        pop                 # VALUE2 VALUE1 ROW
    }

    @CONTEXT{@GPU_DEVICE,
        @SEND_GPU_DATA(@GPU_STATE_MODE_0)

        @SEND_TOP_GPU_DATA
        pop

        @SEND_TOP_GPU_DATA
        pop

        @SEND_TOP_GPU_DATA
        pop
    }
)

$MAIN:
     @CONTEXT{@GPU_DEVICE,
     @SEND_GPU_DATA(@GPU_STATE_MODE_0)

    }

    halt