#--*- Makefile -*--

#*
# Assemble .asm files to the .hex files suitable for the Logisim
# circuit ROM upload.
#**

ASM_FILES ?= $(wildcard *.asm)
HEX_FILES ?= ${ASM_FILES:%.asm=%.hex}

.PHONY: all clean distclean mostlyclean cleanAll

all: ${HEX_FILES}

%.hex: %.asm
	( echo v2.0 raw; ./hrasm $< ) > $@

clean:
	rm -f ${HEX_FILES}

mostlyclean: clean

distclean clenanAll: mostlyclean
