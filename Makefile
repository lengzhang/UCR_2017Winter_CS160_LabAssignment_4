
test :
	gcc -o run -fopenmp test.c
	
p1 :
	gcc -o run -fopenmp problem_1.c
	
p2 :
	gcc -o run -fopenmp problem_2.c
	
p3 :
	gcc -o run -fopenmp problem_3.c
	
p4 :
	gcc -o run -fopenmp problem_4.c
	
p5 :
	gcc -o run -fopenmp problem_5.c
	
p6 :
	gcc -o run -fopenmp problem_6.c

	
.PHONY : clean
clean  :
		-rm run *.out


