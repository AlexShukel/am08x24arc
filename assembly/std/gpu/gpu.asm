@IF_NOT_DEF(@GPU_ASM_INCLUDE_GUARD,
    @MACRO(@GPU_ASM_INCLUDE_GUARD, (), ())

    @INCLUDE("assembly/std/stack.asm")
    @INCLUDE("assembly/std/memory.asm")

    @MACRO(@SEND_TO_GPU, (@DATA),
        push @DATA
        @STORE_TOP_AT(0xffff)
        pop
    )

    @MACRO(@LOAD_GPU_INPUT, (),
        @LOAD_TOP_AT(0)
    )

    @MACRO(@GPU_CONTEXT, (@BODY),
        device 0
        @BODY
    )
)