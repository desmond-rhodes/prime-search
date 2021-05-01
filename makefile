OUT := prime

CXX := g++
CXXFLAGS := -std=c++17

$(OUT):

.PHONY: clean
clean:
	rm -f $(OUT)
