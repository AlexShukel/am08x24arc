@IF_NOT_DEF(@MEMORY_ASM_INCLUDE_GUARD,
    @MACRO(@MEMORY_ASM_INCLUDE_GUARD, (), ())

    @MACRO(@STORE_TOP_AT, (@ADRESS),
        push @ADRESS
        store
        pop
    )

    @MACRO(@LOAD_TOP_AT, (@ADRESS),
        push @ADRESS
        load
        swap
        pop
    )
)