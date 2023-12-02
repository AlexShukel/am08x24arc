@IF_NOT_DEF(@MEMORY_ASM_INCLUDE_GUARD,
    @MACRO(@MEMORY_ASM_INCLUDE_GUARD, (), ())

    @MACRO(@DUMMY_ADRESS, (), 0x0000)
    @MACRO(@NULLPTR, (), @DUMMY_ADRESS)

    @MACRO(@STORE, (@VAL1, @ADR),
        push @VAL1
        push @ADR
        store
        pop
        pop
    )

    @MACRO(@TOP_STORE, (@ADRESS),
        push @ADRESS
        store
        pop
    )

    @MACRO(@LOAD, (@ADRESS),
        push @ADRESS
        load
        swap
        pop
    )

    @MACRO(@LOAD_TOP_AT, (@ADRESS),
        @LOAD(@ADRESS)
        push @ADRESS
    )
)