#/usr/bin/env python3
#Author: Brent Doil
#Compiles and runs CS475 project2.cpp using 1,2,4 threads, static and dynamic schedule, coarse and fine grain 

from os import system
import multiprocessing



def main():
    results = "results.csv"
    proc = multiprocessing.cpu_count()
    with open(results, "a") as file:
        
        file.write(("NUMTHREADS,PADDING,RUNTIME,BIGINT\n"))
    for threads in [1, 2, 4]:
        for schedule in ["static","dynamic"]:
            for x in range(0,10):
                compile = ("g++ -DNUMTHREADS={} -DPADDING={} project3_fix1.cpp -o project3_fix1 -lm -fopenmp").format(threads,schedule)
                system(compile)
                run = "./project2 {}".format(results)
                system(run)  
if __name__ == "__main__":
    main()