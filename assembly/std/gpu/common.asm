@IF_NOT_DEF(@GPU_COMMON_ASM_INCLUDE_GUARD,
    @MACRO(@GPU_COMMON_ASM_INCLUDE_GUARD, (), ())

    @INCLUDE("assembly/std/stack.asm")
    @INCLUDE("assembly/std/memory.asm")

    @MACRO(@GPU_STATE_READY, (), 0x0000)
    @MACRO(@GPU_STATE_BUSY, (), 0x0001)

    @MACRO(@GPU_STATE_MODE_0, (), 0x0002)
    @MACRO(@GPU_STATE_MODE_1, (), 0x0003)
    @MACRO(@GPU_STATE_SWAP_BUFFERS, (), 0xfff0)

    @MACRO(@GPU_DUMMY_ADRESS, (), 0xffff)
    @MACRO(@GPU_NULLPTR, (), @GPU_DUMMY_ADRESS)
)

