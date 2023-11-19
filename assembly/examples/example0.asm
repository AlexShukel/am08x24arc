# Hey we support simple comments
# comment can be wrote using '#' character
# all characters after this symbol until new line
# will be scipped during comment pass

# We support simple macros
@MACRO(@MAX16BIT, (), 0xffff)
# Note that macros can have zero arguments, like one above
# And there how they can be used:
    push @MAX16BIT


# Macros can have multiple arguments
@MACRO(@PUSH3, (@ARG1, @ARG2, @ARG3),
    push @ARG1
    push @ARG1
    push @ARG2
)
# And this is how this can be used
    @PUSH3(0xffff, 0xffff, 0xffff)

# Note that macro derictive is also a macro
# Be carefull then using macro arguments and names
# Since if macro @PUSH3(se above example) have been
# already defined, then first argument of @MACRO
# will be replaced with previos macro defenition

# There is some examples:
@MACRO(@PUSH2, (@ARG1, @ARG2),
    push @ARG1
    push @ARG2
)

@MACRO(@CODE, (@OPERATIONS), @OPERATIONS)

@CODE(
    push @MAX16BIT
    pop

    jmpa 0
)

# Also note that we have special @NOTIFY macro, that
# can be used to printin some strings doring compilation process
