@IF_NOT_DEF(@GPU_CPU_ASM_INCLUDE_GUARD,
    @MACRO(@GPU_CPU_ASM_INCLUDE_GUARD, (), ())

    @INCLUDE("assembly/std/gpu/common.asm")

    @MACRO(@GET_GPU_STATE, (),
        push @GPU_STATE_REGISTER
        load
        swap
        pop
    )

    # (RET) STATE
    @DECL_PROC($WAIT_GPU_STATE_PROC,
        swap                                            # STATE (RET)

        $WAIT_GPU_STATE_PROC_LOOP:
            @GET_GPU_STATE                              # CUR_STATE STATE (RET)

            @JMP_EQL($WAIT_GPU_STATE_PROC_LOOP_BREAK)   # (ADRESS) (CMP) CUR_STATE STATE (RET)
            @POP3                                       # (CMP) CUR_STATE STATE (RET)
                                                        # CUR_STATE STATE (RET)
                                                        # STATE (RET)

            jmpa $WAIT_GPU_STATE_PROC_LOOP

        $WAIT_GPU_STATE_PROC_LOOP_BREAK:                # (ADRESS) (CMP) CUR_STATE STATE (RET)
            @POP4                                       # (CMP) CUR_STATE STATE (RET)
                                                        # CUR_STATE STATE (RET)
                                                        # STATE (RET)
                                                        # (RET)
    )

    @MACRO(@WAIT_GPU_STATE, (@STATE),
        push @STATE
        @CALL($WAIT_GPU_STATE_PROC)
    )
)