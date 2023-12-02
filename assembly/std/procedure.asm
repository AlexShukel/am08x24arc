@IF_NOT_DEF(@PROCEDURE_ASM_INCLUDE_GUARD,
    @MACRO(@PROCEDURE_ASM_INCLUDE_GUARD, (), ())

    @MACRO(@DECL_PROC, (@PROC_NAME, @BODY),
        @PROC_NAME:
            @BODY

            @ADD_CONST(2)
            jmpt
    )

    @MACRO(@CALL, (@PROC_NAME),
        pushpc
        jmpa @PROC_NAME
        pop
    )

    # Usage exmple:
    #
    # @DECL_PROC($TEST_PROCEDURE,
    #     # Do something, note that at proc begginng top value is return ptr
    #     # And we expect that at the end of procedure top value still will be return ptr
    # )
    #
    # @CALL($TEST_PROCEDURE)
    #

    $JMP_EQL_PROC: # FAIL_ADRS COMP ADRESS
        swap # COMP FAIL_ADRS ADRESS

        push $JMP_EQL_PROC_SUCC # SUC_LABEL COMP FAIL_ADRS ADRESS
        jz

        $JMP_EQL_PROC_FAIL:
            pop             # COMP FAIL_ADRS ADRESS
            pop             # FAIL_ADRS ADRESS
            swap            # ADRESS FAIL_ADRS
            pop             # FAIL_ADRS

            @ADD_CONST(2)

            jmpt

        $JMP_EQL_PROC_SUCC:
            pop             # COMP FAIL_ADRS ADRESS
            pop             # FAIL_ADRS ADRESS
            pop             # ADRESS

            jmpt

    # Jump eql anyway consumes value
    # note that it always leaves adress
    # to be returned on top of the stack
    #
    # Do not forget to pop it

    @MACRO(@JMP_EQL, (@ADRESS),
        @SUB

        push @ADRESS        # ADRESS COMP
        swap                # COMP ADRESS

        pushpc              # FAIL_ADRS COMP ADRESS

        jmpa $JMP_EQL_PROC
    )

    $JMP_NEQL_PROC: # FAIL_ADRS COMP ADRESS
        swap # COMP FAIL_ADRS ADRESS

        push $JMP_NEQL_PROC_SUCC # SUC_LABEL COMP FAIL_ADRS ADRESS
        jnz

        $JMP_NEQL_PROC_FAIL:
            pop             # COMP FAIL_ADRS ADRESS
            pop             # FAIL_ADRS ADRESS
            swap            # ADRESS FAIL_ADRS
            pop             # FAIL_ADRS

            @ADD_CONST(2)

            jmpt

        $JMP_NEQL_PROC_SUCC:
            pop             # COMP FAIL_ADRS ADRESS
            pop             # FAIL_ADRS ADRESS
            pop             # ADRESS

            jmpt

    @MACRO(@JMP_NEQL, (@ADRESS),
        @SUB

        push @ADRESS        # ADRESS COMP
        swap                # COMP ADRESS

        pushpc              # FAIL_ADRS COMP ADRESS

        jmpa $JMP_NEQL_PROC
    )
)