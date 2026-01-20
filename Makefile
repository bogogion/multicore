CC                  = gcc
CODE_DEPENDENCIES   = src/*.h src/*.c
PROCESSOR_SOURCE    = processor.c
TEST_SOURCE         = test.c
TARGET              = processor 
TEST_TARGET         = test

all:
	$(CC) $(CODE_DEPENDENCIES) $(PROCESSOR_SOURCE) -o $(TARGET)
test:
	$(CC) $(CODE_DEPENDENCIES) $(TEST_SOURCE) -o $(TEST_TARGET)
clean:
	rm $(TARGET) && rm $(TEST_TARGET)
