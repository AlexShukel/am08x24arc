@IF_NOT_DEF(@STAK_ASM_INCLUDE_GUARD,
    @MACRO(@STAK_ASM_INCLUDE_GUARD, (), ())

    @INCLUDE("assembly/std/push.asm")
    @INCLUDE("assembly/std/pop.asm")
)