warningFLAGS=-Wall -Wextra -Wconversion -Wformat -Wformat=2 -Wimplicit-fallthrough -Wvla

utilityCFlAGS+=$(warningFLAGS)
utilityCFLAGS=-std=c17 -O2 -march=native -flto



data1000:       measurements1000.txt        output1000.txt
data1000000:    measurements1000000.txt    output1000000.txt
data1000000000: measurements1000000000.txt output1000000000.txt

bin/:
	mkdir -p bin/
	
bin/generateInput : generateInput.c
	gcc $(utilityCFLAGS) $^ -lm -o $@
	
bin/generateGoodOutput : generateGoodOutput.c
	gcc $(utilityCFLAGS) $^ -lm -o $@
	
measurements%.txt: bin/generateInput
	@number=$(subst measurements,,$(basename $(notdir $@))); \
	echo "Generating file with $$number measurements"; \
	./bin/generateInput $@ $$number
	
output%.txt: bin/generateGoodOutput
	@number=$(subst output,,$(basename $(notdir $@))); \
	file="measurements$$number.txt"; \
	echo "Generating output for $$file."; \
	./bin/generateGoodOutput $$file 1> $@
	

