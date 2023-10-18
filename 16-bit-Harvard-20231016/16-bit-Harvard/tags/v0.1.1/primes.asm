        ;; First 500 prime numbers
J:      EQU 0          ; Index of the currently checked prime
N:      EQU 1          ; Currently conisdered prime candidate
I:      EQU 2          ; Current prime/array index
MAX:    EQU 500        ; Number of primes to compute
PRIMES: EQU 100        ; Address of the prime number array, MAX length
        ;;
        ;; Initialise indices:
        LDC  1
        ST   I
        ;; 2 is the first prime number:
        LDC  2
        LDXC PRIMES
        STI
        OUT  0                  ; Display it
        LDC  1                  ; next prime candidate to check is 1+2=3
        ST   N
        ;; The I index points to the next free location in the array PRIMES.
        ;; The J index should traverse the PRIMES array from 1 (the second element)
        ;; to I-1, to check for prime division reminders.
LOOP:   LD   N
        ;; Advance to the next prime candidate:
        ADDC 2
        ST   N
        ;; Set J to the beginning of the odd prime array:
        LDC  1
        ST   J
        ;; Jump to check if we have still primes to go:
        JMP  CHECK
        ;; Test all known primes until sqrt(N):
TEST:   LDC  PRIMES
        ADD  J
        ATOX
        LD   N
        REMX
        JNZ  OK
        JMP  LOOP          ; Since the current candidate was not prime, try next
        ;; Check of there are still primes to devide by:
OK:     LD   J
        ADDC 1
        ST   J        ; J ++
CHECK:  SUB  I        ; A = J - I
        JNEG TEST     ; if J - I < 0 GOTO TEST, i.e. when J < I
        ;; Finish the primality test for N:
FINISH: LDC  PRIMES
        ADD  I        ; Index the prime array
        ATOX
        LD   N
        STI           ; Store the new prime into the array
        OUT  0        ; Display the new prime
        ;; Advance the I counter for the next prime:
        LD   I
        ADDC 1
        ST   I
        SUBC MAX
        JNZ  LOOP
END:    HALT
