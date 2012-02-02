CPP = clang++
CFLAGS = -O2 -g

TESTID = 0
TEXT = ""

WORDNET_DIR = /usr/local/WordNet-3.0

TARGETS = wordnet_test

all: $(TARGETS)

happy: wordnet_test
	./wordnet_test 1 "happy"

test: wordnet_test
	./wordnet_test $(TESTID) "$(TEXT)"

a: asobi
	./asobi $(TEXT)


WORDNET_ASOBI_OBJECTS = asobi_main.o wutil.o Lemma.o
asobi: $(WORDNET_ASOBI_OBJECTS)
	$(CPP) $(CFLAGS) -L$(WORDNET_DIR)/lib -lWN -o $@ $(WORDNET_ASOBI_OBJECTS)

asobi_main.o: asobi_main.cc
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<
wutil.o: wutil.cc wutil.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<
Lemma.o: Lemma.cc Lemma.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<


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
