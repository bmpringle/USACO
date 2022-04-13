build:
	cd $(FOLDER); clang++ main.cpp -lm -O2 -g -std=c++17
run:
	cd $(FOLDER); ./a.out
build-dbg:
	cd $(FOLDER); clang++ main.cpp -lm -O0 -g -std=c++17
run-dbg:
	cd $(FOLDER); lldb ./a.out
run-profiler: #macos only w/ xcode 13
	cd $(FOLDER); xcrun xctrace record --template 'Time Profiler' --target-stdout - --launch -- a.out
clean-traces:
	cd $(FOLDER); rm -rf *.trace