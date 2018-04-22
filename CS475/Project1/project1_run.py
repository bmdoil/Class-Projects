#/usr/bin/env python3
#Author: Brent Doil
#Compiles and runs CS475 project1.cpp using 1,2,4,8 threads and several nodenums. Writes results to csv

from os import system

def main():
    results = "results.csv"
    with open(results, "w") as file:   
        file.write(("Threads, Nodes, Volume, Max MCalcs, Avg MCalcs\n"))
    for threads in [1, 2, 4, 8, 16]:
        for nodes in [100, 250, 500, 1000, 2000, 3000, 4000, 5000]:
            compile = ("g++ -DNUMTHREADS={} -DNUMNODES={} project1.cpp -o project1 -lm -fopenmp").format(threads,nodes)
            system(compile)
            run = "./project1 {}".format(results)
            system(run)  
if __name__ == "__main__":
    main()