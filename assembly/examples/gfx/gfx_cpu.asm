jmpa $MAIN

@INCLUDE("assembly/std/io.asm")

@MACRO(@ROM_DEVICE, (), 0x0000)
@MACRO(@RAM_DEVICE, (), 0x000d)
@MACRO(@GPU_DEVICE, (), 0x000e)

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

@MACRO(@SEND_GPU_DATA, (@ADRESS, @DATA),
    push @DATA
    storeac @ADRESS
)

@MACRO(@DDUP, (),
    dupn
    dupn
)

@MACRO(@LOAD_WORD, (),
    load
    swap
    addat 1
)

$MAIN:
    push @ROM_DEVICE
    push 0x0000

    $LOOP:
        dupn
        devicet
        drop

        dupt
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD
            @LOAD_WORD

            drop # (VALUE2) (VALUE1)  ROW (RAM ADRESS) ROW

        @CONTEXT{@GPU_DEVICE,
            @WAIT_GPU_STATE(@GPU_STATE_READY)

            @SEND_GPU_DATA(@GPU_STATE_REGISTER, @GPU_STATE_MODE_1)

            @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)

            storeac 0x0001
            storeac 0x0002
            storeac 0x0003
            storeac 0x0004
            storeac 0x0005
            storeac 0x0006
            storeac 0x0007
            storeac 0x0008
            storeac 0x0009
            storeac 0x000a
            storeac 0x000b
            storeac 0x000c
            storeac 0x000d
            storeac 0x000e
            storeac 0x000f
            storeac 0x0010
            storeac 0x0011
            storeac 0x0012
            storeac 0x0013
            storeac 0x0014
            storeac 0x0015
            storeac 0x0016
            storeac 0x0017
            storeac 0x0018
            storeac 0x0019
            storeac 0x001a
            storeac 0x001b
            storeac 0x001c
            storeac 0x001d
            storeac 0x001e
            storeac 0x001f
            storeac 0x0020
            storeac 0x0021
            storeac 0x0022
            storeac 0x0023
            storeac 0x0024
            storeac 0x0025
            storeac 0x0026
            storeac 0x0027
            storeac 0x0028
            storeac 0x0029
            storeac 0x002a
            storeac 0x002b
            storeac 0x002c
            storeac 0x002d
            storeac 0x002e
            storeac 0x002f
            storeac 0x0030
            storeac 0x0031
            storeac 0x0032
            storeac 0x0033
            storeac 0x0034
            storeac 0x0035
            storeac 0x0036
            storeac 0x0037
            storeac 0x0038
            storeac 0x0039
            storeac 0x003a
            storeac 0x003b
            storeac 0x003c
            storeac 0x003d
            storeac 0x003e
            storeac 0x003f
            storeac 0x0040

            @SEND_GPU_DATA(@GPU_STATE_REGISTER, @GPU_STATE_DATA_UPLOAD_DONE)

            addat 64

            push 64000
            jeac $INC_DEVICE

            jmpa $LOOP
        }

        $INC_DEVICE:
            addan 1
            drop
            push 0x0000

            jmpa $LOOP

    halt