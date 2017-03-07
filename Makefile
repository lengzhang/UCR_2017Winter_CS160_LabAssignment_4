
test :
	gcc -o test.out -fopenmp test.c
	
p1 :
	gcc -o p1.out -fopenmp problem_1.c
	
p2 :
	gcc -o p2.out -fopenmp problem_2.c
	
p3 :
	gcc -o p3.out -fopenmp problem_3.c
	
p4 :
	gcc -o p4.out -fopenmp problem_4.c
	
p5 :
	gcc -o p5.out -fopenmp problem_5.c
	
p6 :
	gcc -o p6.out -fopenmp problem_6.c

	
.PHONY : clean
clean  :
		-rm *.out


