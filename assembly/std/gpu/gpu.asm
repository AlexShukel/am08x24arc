@IF_NOT_DEF(@GPU_GPU_ASM_INCLUDE_GUARD,
    @MACRO(@GPU_GPU_ASM_INCLUDE_GUARD, (), ())

    @INCLUDE("assembly/std/gpu/common.asm")

    @MACRO(@SEND_TO_GPU, (@DATA),
        push @DATA
        @STORE_TOP_AT(0xffff)
        pop
    )

    @MACRO(@LOAD_GPU_INPUT, (),
        @LOAD_TOP_AT(0)
    )

    @MACRO(@MARK_GPU_STATE, (@STATE),
        @STORE(@STATE, 0xffff)
    )
)