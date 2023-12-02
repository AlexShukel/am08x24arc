@IF_NOT_DEF(@GPU_CPU_ASM_INCLUDE_GUARD,
    @MACRO(@GPU_CPU_ASM_INCLUDE_GUARD, (), ())

    @INCLUDE("assembly/std/gpu/common.asm")

    @MACRO(@GET_GPU_STATE, (),
        push @GPU_STATE_REGISTER
        load
        swap
        pop
    )

    @DECL_PROC($WAIT_GPU_STATE_PROC,
        swap

        $WAIT_GPU_STATE_PROC_LOOP:
            dup

            @GET_GPU_STATE

            @JMP_EQL($WAIT_GPU_STATE_PROC_LOOP_BREAK)
            pop

            jmpa $WAIT_GPU_STATE_PROC_LOOP

        $WAIT_GPU_STATE_PROC_LOOP_BREAK:
            pop

        swap
    )

    @MACRO(@WAIT_GPU_STATE, (@STATE),
        push @STATE
        @CALL($WAIT_GPU_STATE_PROC)
        pop
    )
)