build:
	cd $(FOLDER); clang++ main.cpp -lm -O2 -std=c++17
run:
	cd $(FOLDER); ./a.out
build-dbg:
	cd $(FOLDER); clang++ main.cpp -lm -O0 -g -std=c++17
run-dbg:
	cd $(FOLDER); lldb ./a.out