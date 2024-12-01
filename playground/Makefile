A	:= Do you $(C)
B	= Do you $(C)
C	= understand
C	= wow

clean:
	@echo hi

all:
	$(info $(A))
	$(info $(B))

# Make checks individually each file required. If not there or out of date, looks for a way to get it
/build/program: main.o lib.o utils.o
	cc $^ -o $@

# Pattern Rule. Runs for each .o file required
%.o: %.c
	cc -c $< -o $@

# differentiates between files and pseudo targets
.PHONY: clean fclean

# make -p -f/dev/null