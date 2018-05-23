#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <omp.h>


float Ranf(unsigned int *seedp, float low, float high);

int Ranf(unsigned int *seedp, int ilow, int ihigh);

void GrainDeer();

void Grain();

void Watcher();

void HuntingSeason(); //Hunting season starts, dropping the amount of GrainDeer a random amount during Fall.


const int HUNT_CHANCE = 50;    //Likelyhood of a hunter spawning
const float HUNT_SUCCESS = .75;  //Chance a hunter bags a GrainDeer 
const int HUNTER_GETS_DEER = 1; //Number of GrainDeer a successful hunter gets

unsigned int seed = (time(NULL));

float x = Ranf( &seed, -1.f, 1.f );

int	NowYear = 2017;		// 2017 - 2022
int	NowMonth = 0;		// 0 - 11

float	NowPrecip;		// inches of rain per month
float	NowTemp;		// temperature this month
float	NowHeight = 1.;		// grain height in inches
int	NowNumDeer = 1;		// number of deer in the current population
int NowHunters = 0;


const float GRAIN_GROWS_PER_MONTH =		10.0;
const float ONE_DEER_EATS_PER_MONTH =	0.5;

const float AVG_PRECIP_PER_MONTH =		6.0;	// average
const float AMP_PRECIP_PER_MONTH =		6.0;	// plus or minus
const float RANDOM_PRECIP =			    2.0;	// plus or minus noise

const float AVG_TEMP =				50.0;	// average
const float AMP_TEMP =				20.0;	// plus or minus
const float RANDOM_TEMP =			10.0;	// plus or minus noise

const float MIDTEMP =				40.0;
const float MIDPRECIP =				10.0;


int main(int argc, char *argv[])
{
    #ifndef _OPENMP
        fprintf(stderr, "OpenMP is not available\n");
        return 1;
    #endif

   // calculate starting temperature & precipitation
    float ang = (30.0 * (float)NowMonth + 15.0) * (M_PI /180.0);
    float temp = AVG_TEMP - AMP_TEMP * cos(ang);
    NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

    float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
    NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
    if (NowPrecip < 0.0) {
        NowPrecip = 0.0;
    }
    
    omp_set_num_threads(4);
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            GrainDeer();
        }

        #pragma omp section
        {
            Grain();
        }

        #pragma omp section
        {
            Watcher();
        }

        #pragma omp section
        {
            HuntingSeason();
        }
    }
    return 0;

}

// calculate square of a float
float sqr(float n) 
{
    return n * n;
}

void GrainDeer() 
{
  
    while (NowYear < 2023) 
    {
         int deerHere = 0;       
        if ((float)NowNumDeer < NowHeight) 
        {
            deerHere++;
        } 
        else if ((float)NowNumDeer > NowHeight) 
        {
            deerHere--;
        }
        
        if (NowHunters > 0) 
        {
            
            deerHere -= NowHunters * (HUNTER_GETS_DEER * HUNT_SUCCESS);
        }

        int newDeer = NowNumDeer + deerHere;
        if (newDeer < 0) 
        {
            newDeer = 0;
        }

        // DoneComputing barrier
        #pragma omp barrier

        NowNumDeer = newDeer;

        // DoneAssigning barrier
        #pragma omp barrier

        // DonePrinting barrier
        #pragma omp barrier
    }
}

void Grain() {

	float newHeight;
	float tempFactor;
	float precipFactor;

	while(NowYear < 2023) {

		newHeight = NowHeight;
		float tempFactor = exp(-sqr((NowTemp - MIDTEMP) / 10.0));
        float precipFactor = exp(-sqr((NowPrecip - MIDPRECIP) / 10.0));

		newHeight += tempFactor * precipFactor * GRAIN_GROWS_PER_MONTH;
		newHeight -= (float) NowNumDeer * ONE_DEER_EATS_PER_MONTH;
        if (newHeight < 0.0) 
        {
            newHeight = 0.0;
        }
		
		//done computing
		#pragma omp barrier

		NowHeight = newHeight;
		//done assigning
		#pragma omp barrier

		//done printing
		#pragma omp barrier

	}

}

void Watcher() {
    int monthNumber = 1;
    FILE *results = std::fopen("results.csv", "w");   
    std::fprintf(results, "monthNum,year,month,precip,temp,grain_height,deer,hunters\n");      
    while (NowYear < 2023) {
        // nothing

        #pragma omp barrier   // 1. DoneComputing barrier

        // nothing

        #pragma omp barrier   // 2. DoneAssigning barrier

        // print results 
        
        std::fprintf(results, "%d, %d, %d, %lf, %lf, %lf, %d, %d\n", monthNumber, NowYear, NowMonth, NowPrecip, NowTemp, NowHeight, NowNumDeer, NowHunters);

        // calculate and update new month / year
       
        NowMonth += 1;
        if (NowMonth == 12) {
            NowYear += 1;
        
        }
        NowMonth %= 12;

        // calculate new temperature and precipitation
        float ang = (30.0 * (float)NowMonth + 15.0) * (M_PI /180.0);
        float temp = AVG_TEMP - AMP_TEMP * cos(ang);
        NowTemp = temp + Ranf(&seed, -RANDOM_TEMP, RANDOM_TEMP);

        float precip = AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(ang);
        NowPrecip = precip + Ranf(&seed, -RANDOM_PRECIP, RANDOM_PRECIP);
        if (NowPrecip < 0.0) {
            NowPrecip = 0.0;
        }

        monthNumber++;

        #pragma omp barrier   // 3. DonePrinting barrier
    }
    std:fclose(results); 
}

void HuntingSeason()
{
   
        while (NowYear < 2023) {
     
        int chanceHunter = Ranf(&seed, 0, 100);

        int newHunter = 0;
        printf("%d\n",std::abs(chanceHunter));
        if (NowNumDeer > 5)
        {
            if (chanceHunter < HUNT_CHANCE) 
            {
            newHunter++;
            }
        }
        else if (NowNumDeer == 0)
        {
            NowHunters = 0;
        }
        // DoneComputing barrier:
        #pragma omp barrier
        
        NowHunters += newHunter;
        if (NowHunters < 0){NowHunters = 0;}

        // DoneAssigning barrier:
        #pragma omp barrier

        // DonePrinting barrier:
        #pragma omp barrier
    }
}

float
Ranf( unsigned int *seedp,  float low, float high )
{
        float r = (float) rand_r( seedp );              // 0 - RAND_MAX

        return(   low  +  r * ( high - low ) / (float)RAND_MAX   );
}


int
Ranf( unsigned int *seedp, int ilow, int ihigh )
{
        float low = (float)ilow;
        float high = (float)ihigh + 0.9999f;

        return (int)(  Ranf(seedp, low,high) );
}