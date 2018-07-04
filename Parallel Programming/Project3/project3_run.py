#/usr/bin/env python3
#Author: Brent Doil
#Compiles and runs CS475 project3_fix1.cpp & project3_fix2.cpp 

from os import system

def main():
  fix_one()
  fix_two()  

def fix_one():
    results = "results_fix1.csv"
    with open(results, "w") as file: 
        file.write(("NUMTHREADS,PADDING,PERFORMANCE,BIGINT\n"))
    for threads in [1, 2, 4]:
        for padding in range(17):
            compile = ("g++ -DNUMTHREADS={} -DPADDING={} project3_fix1.cpp -o project3_fix1 -lm -fopenmp").format(threads,padding)
            system(compile)
            for NUMTRIES in range(1,11):
                print("Try:{} Threads:{} Padding:{}\n").format(NUMTRIES,threads,padding)
                run = "./project3_fix1 {}".format(results)
                system(run) 
def fix_two():
    results = "results_fix2.csv"
    with open(results, "w") as file: 
        file.write(("NUMTHREADS,PERFORMANCE,BIGINT\n"))
    for threads in [1, 2, 4]:
        compile = ("g++ -DNUMTHREADS={} project3_fix2.cpp -o project3_fix2 -lm -fopenmp").format(threads)
        system(compile)
        for NUMTRIES in range(1,11):
            print("Try{} Threads:{}\n").format(NUMTRIES,threads)             
            run = "./project3_fix2 {}".format(results)
            system(run) 

if __name__ == "__main__":
    main()