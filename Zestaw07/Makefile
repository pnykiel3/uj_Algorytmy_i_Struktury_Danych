DIR = `basename $(CURDIR)`
########################################
LIB1 = mystack
EXEC1 = main
EXEC2 = rpn
########################################
EXECS = $(EXEC1) $(EXEC2)
########################################
OBJS1 = $(EXEC1).o
OBJS2 = $(EXEC2).o
########################################
LIBS1 = $(LIB1).h
########################################
COFLAGS = -Wall -O -std=c++11
LDFLAGS = -Wall -O
CO = g++
LD = $(CO)
########################################
%.o: %.cpp
	$(CO) $(COFLAGS) -c $<
########################################
.PHONY: all
all: $(EXECS)
########################################
$(EXEC1): $(OBJS1) $(LIBS1)
	$(LD) -o $@ $(LDFLAGS) $^

$(EXEC2): $(OBJS2) $(LIBS1)
	$(LD) -o $@ $(LDFLAGS) $^
########################################
.PHONY: run
run: $(EXEC1)
	./$(EXEC1)

.PHONY: rpn-run
rpn-run: $(EXEC2)
	./$(EXEC2)
########################################
.PHONY: clean
clean:
	rm -f *.o  *~ $(EXECS)
########################################
.PHONY: tar
tar: clean
	(cd ../; tar -cvzf "$(DIR)".tar.gz  "$(DIR)" )
########################################
