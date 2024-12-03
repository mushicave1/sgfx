build: clean
	@echo "Building project..."	
	mkdir -p build
	cd build && cmake -S ../ -B. && make 

tests:
	@echo "Running tests..."
	./build/test/sgfx_test

example:
	@echo "Running examples..."
	./build/examples/sgfx_examples

clean:
	@echo "Removing build..."
	rm -rf build