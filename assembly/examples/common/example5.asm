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

push 0xffff
@STORE_TOP_AT(0x0001)
pop

@LOAD_TOP_AT(0x0001)

halt
