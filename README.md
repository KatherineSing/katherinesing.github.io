To compile and run twitter, type:

make
./twitter <data_file>

To compile and run heaptest.cpp, type:
make heaptest

To compile and run hash_test.cpp, type:
make hash_test

To compile and run splaytest.cpp, type:
splaytest

To clean the created files that you
don't want to keep, type:

make clean


**** SPECIFIC COMPILER COMMANDS ****

In the following commands,
CXX = g++
CPPFLAGS = -g -Wall -std=c++11
holds.

To compile hash_test, type: make hash_test
The compiler does this:
$(CXX) $(CPPFLAGS) $^ -o $@
using files  hash.h hash.cpp hash_test.cpp

To compile splaytest, type: make splaytest
The compiler does this:
$(CXX) $(CPPFLAGS) $^ -o $@ 
using files splaytest: splaytest.cpp splay_tree.h

To compile datetime.o, type: make datetime.o
The the compiler does this:
$(CXX) $(CPPFLAGS) -c datetime.cpp -o $@ 
using files datetime.cpp datetime.h

To compile tweet.o, type: make tweet.o
The compiler does this:
$(CXX) $(CPPFLAGS) -c tweet.cpp -o $@ 
using files tweet.cpp tweet.h datetime.h

To compile user.o, type: make user.o
The compiler does this:
$(CXX) $(CPPFLAGS) -c user.cpp -o $@ 
using files user.cpp user.h tweet.h 

To compile twiteng.o, type: make twiteng.o
The compiler does this:
$(CXX) $(CPPFLAGS) -c twiteng.cpp -o $@ 
using files twiteng.cpp twiteng.h user.h 
tweet.h datetime.h

To compile handler.o, type: make handler.o
The compiler does this:
$(CXX) $(CPPFLAGS) -c handler.cpp -o $@
using files handler.cpp twiteng.h

To compile cmdhandler.o, type: make cmdhandler.o
The compiler does this:
$(CXX) $(CPPFLAGS) -c cmdhandler.cpp -o $@
using files cmdhandler.cpp handler.h util.h

To compiler twitter, type: make twitter
The compiler does this:
$(CXX) $(CPPFLAGS) $^ -o $@ 
Where $^ refers to 
twitter.cpp datetime.o user.o 
tweet.o handler.o cmdhandler.o 
util.o twiteng.o hash.o msort.h

But to compile everything at once such that
twitter is immediately ready to run, type: make
This will compile every file that was not already compiled
and also compile twitter.

Then you can run twitter using ./twitter <data_file>
for example, ./twitter twitter.dat

To compiler twitter, type: make heaptest
The compiler does this:
$(CXX) $(CPPFLAGS) $^ -o $@
Where $^ refers to heaptest.cpp heap.h


	
