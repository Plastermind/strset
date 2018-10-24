CXXFLAGS = -Wall -Wextra -O2 -std=c++17 -g
CFLAGS = -Wall -Wextra -O2 -std=c11 -g

make:
	g++ ${CXXFLAGS} -c strset.cc -o strset.o
	g++ ${CXXFLAGS} -c strsetconst.cc -o strsetconst.o
	g++ ${CXXFLAGS} -c strset_test2a.cc -o strset_test2a.o
	g++ ${CXXFLAGS} -c strset_test2b.cc -o strset_test2b.o	
	g++ strset_test2a.o strsetconst.o strset.o -o strset2a
	g++ strset_test2b.o strsetconst.o strset.o -o strset2b
	
a: 
	gcc -Wall -Wextra -O2 -std=c11 -c strset_test1.c -o strset_test1.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strset.cc -o strset.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strsetconst.cc -o strsetconst.o
	g++ strset_test1.o strsetconst.o strset.o -o strset1

b:
	gcc -Wall -Wextra -O2 -std=c11 -c strset_test1.c -o strset_test1.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strset.cc -o strset.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strsetconst.cc -o strsetconst.o
	g++ strset_test1.o strsetconst.o strset.o -o strset1
	g++ -Wall -Wextra -O2 -std=c++17 -c strset_test2a.cc -o strset_test2a.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strset_test2b.cc -o strset_test2b.o
	g++ strset_test2a.o strsetconst.o strset.o -o strset2a
	g++ strset_test2b.o strsetconst.o strset.o -o strset2b 
