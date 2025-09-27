app.out: main.o libsorts.a
	g++ -o $@ $^

main.o: main.cpp
	g++ -c -MMD -o $@ $<

libsorts.a: sorts.o
	ar rcs $@ $^

sorts.o: sorts.cpp
	g++ -c -MMD -o $@ $<

run:
	./app.out

clean:
	rm -f *.out *.o *.d *.a