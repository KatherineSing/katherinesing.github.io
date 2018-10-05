CXX = g++
CPPFLAGS = -g -Wall -std=c++11

all: twitter

hash_test: hash.h hash.cpp hash_test.cpp
	$(CXX) $(CPPFLAGS) $^ -o $@

splaytest: splaytest.cpp splay_tree.h
	$(CXX) $(CPPFLAGS) $^ -o $@ 

heaptest: heaptest.cpp heap.h
	$(CXX) $(CPPFLAGS) $^ -o $@ 

hash.o: hash.cpp hash.h
	$(CXX) $(CPPFLAGS) -c $< -o $@

datetime.o: datetime.cpp datetime.h
	$(CXX) $(CPPFLAGS) -c datetime.cpp -o $@ 

tweet.o: tweet.cpp tweet.h datetime.h
	$(CXX) $(CPPFLAGS) -c tweet.cpp -o $@ 

user.o: user.cpp user.h tweet.h 
	$(CXX) $(CPPFLAGS) -c user.cpp -o $@ 

twiteng.o: twiteng.cpp twiteng.h user.h tweet.h datetime.h
	$(CXX) $(CPPFLAGS) -c twiteng.cpp -o $@ 

handler.o: handler.cpp twiteng.h
	$(CXX) $(CPPFLAGS) -c handler.cpp -o $@

cmdhandler.o: cmdhandler.cpp handler.h util.h twiteng.h
	$(CXX) $(CPPFLAGS) -c cmdhandler.cpp -o $@

twitter: twitter.cpp datetime.o user.o tweet.o handler.o cmdhandler.o \
util.o twiteng.o hash.o msort.h
	$(CXX) $(CPPFLAGS) $^ -o $@ 


.PHONY: clean
	
clean: 
	rm -f datetime.o tweet.o user.o twiteng.o handler.o \
	cmdhandler.o twitter *.feed *.mentions heaptest hash_test