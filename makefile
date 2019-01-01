ring:rq.hpp ring.cc
	g++ -o $@ $^ -pthread -g
.PHONY:clean
clean:
	rm -f ring
