
a.out:
	g++ *.cpp

run: a.out
	./a.out

clean:
	rm -f ./a.out
