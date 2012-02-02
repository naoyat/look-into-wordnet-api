CPP = clang++
CFLAGS = -O2 -g

TESTID = 0
TEXT = ""

WORDNET_DIR = /usr/local/WordNet-3.0

TARGETS = wordnet_apitest wordnet_lemmatest

all: $(TARGETS)

happy: wordnet_apitest
	./wordnet_apitest 1 "happy"

apitest: wordnet_apitest
	./wordnet_apitest $(TESTID) "$(TEXT)"

lemmatest: wordnet_lemmatest
	./wordnet_lemmatest $(TEXT)


WORDNET_LEMMATEST_OBJECTS = wordnet_lemmatest_main.o wutil.o Lemma.o
wordnet_lemmatest: $(WORDNET_LEMMATEST_OBJECTS)
	$(CPP) $(CFLAGS) -L$(WORDNET_DIR)/lib -lWN -o $@ $(WORDNET_LEMMATEST_OBJECTS)

wordnet_lemmatest_main.o: wordnet_lemmatest_main.cc
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<
wutil.o: wutil.cc wutil.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<
Lemma.o: Lemma.cc Lemma.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<


WORDNET_APITEST_OBJECTS = wordnet_apitest_main.o wordnet_apitest.o wordnet_verbose.o
wordnet_apitest: $(WORDNET_APITEST_OBJECTS)
	$(CPP) $(CFLAGS) -L$(WORDNET_DIR)/lib -lWN -o $@ $(WORDNET_APITEST_OBJECTS)

wordnet_apitest_main.o: wordnet_apitest_main.cc wordnet_apitest.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $<
wordnet_apitest.o: wordnet_apitest.cc wordnet_apitest.h wordnet_verbose.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $< 
wordnet_verbose.o: wordnet_verbose.cc wordnet_verbose.h
	$(CPP) $(CFLAGS) -c -I$(WORDNET_DIR)/include -o $@ $< 

clean:
	rm -f $(TARGETS) *.o *~
