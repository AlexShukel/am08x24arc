@IF_NOT_DEF(@GPU_MODE_0_INCLUDE_GUARD,
    @MACRO(@GPU_MODE_0_INCLUDE_GUARD, (), ())

    $GPU_STATE_0:
        drop

        @SET_GPU_STATE(@GPU_STATE_DATA_UPLOAD_REQUEST)

        @WAIT_GPU_STATE(@GPU_STATE_DATA_UPLOAD_DONE)

        @CONTEXT{@GPU_DATA_REGISTER,
            loada 0x0001
            loada 0x0002
            loada 0x0003
        }

        @CONTEXT{@GPU_SCREEN_REGISTER,
            storeac @NULLPTR
            storeac @NULLPTR
            storeac @NULLPTR

            store
        }

        jmpa $MAIN
)




