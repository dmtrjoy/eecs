.PHONY: build

clean:
	rm -rf build

build:
	cmake -B build -S . -G Ninja
	cmake --build build

test:
	ctest --test-dir build/tests
