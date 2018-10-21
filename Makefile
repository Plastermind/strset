make:
	g++ -Wall -Wextra -O2 -std=c++17 -c strset.cc -o strset.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strsetconst.cc -o strsetconst.o
	g++ -Wall -Wextra -O2 -std=c++17 -c strset_test2a.cc -o strset_test2a.o
	g++ strset_test2a.o strsetconst.o strset.o -o strset2a
