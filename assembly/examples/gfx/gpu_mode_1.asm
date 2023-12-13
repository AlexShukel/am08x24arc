@IF_NOT_DEF(@GPU_MODE_1_INCLUDE_GUARD,
    @MACRO(@GPU_MODE_1_INCLUDE_GUARD, (), ())

    @MACRO(@SEND_LINE, (),
        storeac @NULLPTR
        storeac @NULLPTR
        storeac @NULLPTR
        store
    )

    @MACRO(@LOAD_LINE, (@LINE, @ADR1, @ADR2),
        loada @ADR1
        loada @ADR2
        push @LINE
    )

    $GPU_STATE_1:
        drop

        @SET_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)

        @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_DONE)

        @CONTEXT{@GPU_DATA_REGISTER,
            @LOAD_LINE(0x0000, 0x003f, 0x0040)
            @LOAD_LINE(0x0001, 0x003d, 0x003e)
            @LOAD_LINE(0x0002, 0x003b, 0x003c)
            @LOAD_LINE(0x0003, 0x0039, 0x003a)
            @LOAD_LINE(0x0004, 0x0037, 0x0038)
            @LOAD_LINE(0x0005, 0x0035, 0x0036)
            @LOAD_LINE(0x0006, 0x0033, 0x0034)
            @LOAD_LINE(0x0007, 0x0031, 0x0032)
            @LOAD_LINE(0x0008, 0x002f, 0x0030)
            @LOAD_LINE(0x0009, 0x002d, 0x002e)
            @LOAD_LINE(0x000a, 0x002b, 0x002c)
            @LOAD_LINE(0x000b, 0x0029, 0x002a)
            @LOAD_LINE(0x000c, 0x0027, 0x0028)
            @LOAD_LINE(0x000d, 0x0025, 0x0026)
            @LOAD_LINE(0x000e, 0x0023, 0x0024)
            @LOAD_LINE(0x000f, 0x0021, 0x0022)
            @LOAD_LINE(0x0010, 0x001f, 0x0020)
            @LOAD_LINE(0x0011, 0x001d, 0x001e)
            @LOAD_LINE(0x0012, 0x001b, 0x001c)
            @LOAD_LINE(0x0013, 0x0019, 0x001a)
            @LOAD_LINE(0x0014, 0x0017, 0x0018)
            @LOAD_LINE(0x0015, 0x0015, 0x0016)
            @LOAD_LINE(0x0016, 0x0013, 0x0014)
            @LOAD_LINE(0x0017, 0x0011, 0x0012)
            @LOAD_LINE(0x0018, 0x000f, 0x0010)
            @LOAD_LINE(0x0019, 0x000d, 0x000e)
            @LOAD_LINE(0x001a, 0x000b, 0x000c)
            @LOAD_LINE(0x001b, 0x0009, 0x000a)
            @LOAD_LINE(0x001c, 0x0007, 0x0008)
            @LOAD_LINE(0x001d, 0x0005, 0x0006)
            @LOAD_LINE(0x001e, 0x0003, 0x0004)
            @LOAD_LINE(0x001f, 0x0001, 0x0002)
        }

        @CONTEXT{@GPU_SCREEN_REGISTER,
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
            @SEND_LINE
        }

        jmpa $MAIN
)
