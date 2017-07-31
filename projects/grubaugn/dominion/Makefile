CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g  testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)
	
testdiscardCard: unittest1.c dominion.o rngs.o
	gcc -o testdiscardCard -g  unittest1.c dominion.o rngs.o $(CFLAGS)
	
testgainCard: unittest2.c dominion.o rngs.o interface.o
	gcc -o testgainCard -g  unittest2.c dominion.o rngs.o interface.o $(CFLAGS)
	
testgetCost: unittest3.c dominion.o rngs.o interface.o
	gcc -o testgetCost -g  unittest3.c dominion.o rngs.o interface.o $(CFLAGS)
	
testisGameOver: unittest4.c dominion.o rngs.o
	gcc -o testisGameOver -g  unittest4.c dominion.o rngs.o $(CFLAGS)

cardtestsmithy: cardtest1.c dominion.o rngs.o
	gcc -o cardtestsmithy -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
	
cardtestvillage: cardtest2.c dominion.o rngs.o
	gcc -o cardtestvillage -g  cardtest2.c dominion.o rngs.o $(CFLAGS)

cardtestmine: cardtest3.c dominion.o rngs.o
	gcc -o cardtestmine -g  cardtest3.c dominion.o rngs.o $(CFLAGS)
	
cardtestadventurer: cardtest4.c dominion.o rngs.o
	gcc -o cardtestadventurer -g  cardtest4.c dominion.o rngs.o $(CFLAGS)
	
randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
	
randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -o randomtestadventurer -g  randomtestadventurer.c dominion.o rngs.o $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

unittestresults.out: testdiscardCard testgainCard testgetCost testisGameOver cardtestsmithy cardtestvillage cardtestmine cardtestadventurer dominion.o
	./testdiscardCard &> unittestresults.out
	./testgainCard >> unittestresults.out
	./testgetCost >> unittestresults.out
	./testisGameOver >> unittestresults.out
	./cardtestsmithy >> unittestresults.out
	./cardtestvillage >> unittestresults.out
	./cardtestmine >> unittestresults.out
	./cardtestadventurer >> unittestresults.out
	gcov dominion.c >> unittestresults.out
	cat dominion.c.gcov >> unittestresults.out
	
randomtestcard1.out: randomtestcard1 dominion.o
	./randomtestcard1 &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out

randomtestcard2.out: randomtestcard2 dominion.o
	./randomtestcard2 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out
	
randomtestadventurer.out: randomtestadventurer dominion.o
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
	rm -f testdiscardCard testdiscardCard.exe testgainCard testgainCard.exe testgetCost testgetCost.exe testisGameOver testisGameOver.exe
	rm -f testUpdateCoins testUpdateCoins.exe cardtestsmithy cardtestsmithy.exe cardtestvillage cardtestvillage.exe cardtestmine cardtestmine.exe
	rm -f cardtestadventurer cardtestadventurer.exe randomtestcard1 randomtestcard1.exe randomtestcard2 randomtestcard2.exe
	rm -f randomtestadventurer randomtestadventurer.exe
