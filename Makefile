object = && ./run

test :
	gcc -o run -fopenmp test.c $(object)
	
p1 :
	gcc -o run -fopenmp problem_1.c $(object)
	
p2 :
	gcc -o run -fopenmp problem_2.c $(object)
	
p3 :
	gcc -o run -fopenmp matmul.c $(object)
	
p4 :
	gcc -o run -fopenmp problem_4.c $(object)
	
p5 :
	gcc -o run -fopenmp problem_5.c $(object)
	
p6 :
	gcc -o run -fopenmp problem_6.c $(object)
	
.PHONY : clean
clean  :
		-rm run


