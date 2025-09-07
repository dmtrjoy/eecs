.PHONY: build

clean:
	rm -rf build

build:
	cmake -B build -S . -G Ninja -DBUILD_DOCS=ON -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON
	cmake --build build

test:
	ctest --test-dir build/tests
