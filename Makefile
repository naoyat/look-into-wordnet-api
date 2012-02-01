CPP = clang++
CFLAGS = -O2 -g

SEARCHSTR = ""
TESTID = 0

WORDNET_DIR = /usr/local/WordNet-3.0

TARGETS = wordnet_test

all: $(TARGETS)

happy: wordnet_test
	./wordnet_test 1 "happy"

test: wordnet_test
	./wordnet_test $(TESTID) $(SEARCHSTR)


WORDNET_ASOBI_OBJECTS = wordnet_asobi_main.o
wordnet_asobi: $(WORDNET_ASOBI_OBJECTS)
	$(CPP) $(CFLAGS) -L$(WORDNET_DIR)/lib -lWN -o $@ $(WORDNET_ASOBI_OBJECTS)

WORDNET_TEST_OBJECTS = wordnet_test_main.o wordnet_test.o wordnet_verbose.o
wordnet_test: $(WORDNET_TEST_OBJECTS)
	$(CPP) $(CFLAGS) -L$(WORDNET_DIR)/lib -lWN -o $@ $(WORDNET_TEST_OBJECTS)

wordnet_test_main.o: wordnet_test_main.cc wordnet_test.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<
wordnet_test.o: wordnet_test.cc wordnet_test.h wordnet_verbose.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $< 
wordnet_verbose.o: wordnet_verbose.cc wordnet_verbose.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $< 

clean:
	rm -f $(TARGETS) *.o *~
