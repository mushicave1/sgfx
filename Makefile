build:
	@echo "Building project..."
	mkdir -p build
	cd build && cmake -S ../ -B . && make 

tests:
	@echo "Running tests..."
	./build/test/sgfx_test

clean:
	@echo "Removing build..."
	rm -rf build