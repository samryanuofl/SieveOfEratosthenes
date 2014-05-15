/*
Description:
When launched, the program instructs the user to enter a number greater than
1. No type checking is done on the user's input. The Sieve of Eratosthenes
algorithm is used to print all prime numbers less than the number entered.
the program then exits.

Background:
The Sieve of Eratosthenes is an algorithm for finding prime numbers
discovered by a Greek mathematician named Eratosthenes who was born c. 276
BC. It is more efficient than the 'naive' method of simply checking each number
for primality.
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

//Used to mark numbers in array as prime or not
enum NumberTypes
{
    Prime = 0,
    MultipleOfPrime = 1
};

/*
Description:
Takes in two arrays, one is used for scratch work and the other to store

Parameters:
uint32_t NumberList[] - Array with number of elements equal to the largest prime being searched for.
                        This array will be modified by the function.
uint32_t OutPrimesList[] - Array that will be used to store the prime numbers found by the Sieve. Must have
                        enough room to store the primes found by the Sieve. The safest way to ensure this
                        is to make it the same size as the NumberList[] array.
size_t ArraySizeBytes - The size in bytes of the NumberList[] array.

Returns:
The number of prime numbers found.
*/
uint32_t Sieve(uint32_t PrimeCeiling, uint32_t OutPrimesList[], size_t ArraySizeBytes);

/*
Description:
Takes in an array of numbers and a prime. At each element of the array it writes
MultipleOfPrime(enum) if that element number is a multiple of the given prime. Used
by the sieve function to mark off numbers which numbers are not prime.

Parameters:
uint32_t arr[] - Array to mark off as not being prime
size_t size_elements - The number of elements in the arr[] array
uint32_t Prime - Mark off the multiples of this number
*/
uint32_t MarkMultiples(uint32_t arr[], size_t size_elements, uint32_t Prime);

/*
Description:
Print an array of integers of a given size.

Parameters:
uint32_t arr[] - Array of integers to print
size_t size_elements - The number of elements in the array
*/
void PrintIntArray(uint32_t arr[], size_t size_elements);

/*
Description:
Takes in an array where the multiples of primes have been marked off by the
MarkMultiples function and returns the smallest number that  has not yet been
marked as not being prime.

Parameters:
uint32_t arr[] - The array in which the non-prime numbers have been marked as such by
                 MarkMultiples function
size_t size_elements - The Number of elements in arr[]
*/
uint32_t FindNextPrime(uint32_t arr[], size_t size_elements);

int main()
{
    uint32_t PrimeCeiling;
    printf("                  ---Instructions---\n\n");
    printf("The Sieve of a Eratosthenes is an algorithm for finding\nprime numbers that is over 2,000 years old. Enter an\ninteger greater than 2 and press enter to return\na list of prime numbers smaller than the one you typed.\n\n");
    printf("Give me a number: ");
    scanf("%u", &PrimeCeiling);

    while(1)
    {
        if(PrimeCeiling < 3)
        {
            printf("Number must be 2 greater than 2!\n");
            printf("Give me a number: ");
            scanf("%u", &PrimeCeiling);
        }
        else
        {
            uint32_t *PrimesList = malloc(PrimeCeiling * sizeof(uint32_t));

            if(PrimesList == NULL)
            {
                printf("Memory error!\n");
                break;
            }

            uint32_t PrimeCount = Sieve(PrimeCeiling, PrimesList, PrimeCeiling * sizeof(uint32_t));

            PrintIntArray(PrimesList, PrimeCount);
            printf("\nNumber of primes found was %u.\n", PrimeCount);
            float PercentPrimes = ((float)PrimeCount / (float)PrimeCeiling) * 100;
            printf("%.2f%% of numbers between 0 and %u are prime.\n", PercentPrimes, PrimeCeiling);
            break;
        }
    }

    return 0;
}

uint32_t Sieve(uint32_t PrimeCeiling, uint32_t OutPrimesList[], size_t ArraySizeBytes)
{
    uint32_t NextPrime = 2;
    uint32_t PrimeCount = 0;
    const size_t ArrayElements = ArraySizeBytes / sizeof(uint32_t);
    uint32_t *NumberList = malloc(PrimeCeiling * sizeof(uint32_t));

    if(NumberList == NULL)
    {
        printf("Memory error!\n");
        return 0;
    }

    memset(OutPrimesList,0,ArraySizeBytes);
    memset(NumberList,0,ArraySizeBytes);

    do
    {
        OutPrimesList[PrimeCount] = NextPrime;
        MarkMultiples(NumberList, ArrayElements, NextPrime);
        NextPrime = FindNextPrime(NumberList, ArrayElements);
        PrimeCount++;
    }while(NextPrime > 0);

    free(NumberList);

    return PrimeCount;
}

uint32_t FindNextPrime(uint32_t arr[], size_t size_elements)
{
    size_t i;
    for(i=2;i<size_elements;i++)
    {
        if(arr[i] == Prime) return i;
    }

    //No primes left in list
    return 0;
}

uint32_t MarkMultiples(uint32_t arr[], size_t size_elements, uint32_t Prime)
{
    size_t i;
    for(i=1;i*Prime<size_elements;i++)
    {
        arr[i * Prime] = MultipleOfPrime;
    }

    return 1;
}

void PrintIntArray(uint32_t arr[], size_t size_elements)
{
    size_t i;
    for(i=0;i<size_elements;i++)
    {
        printf("Element - %u Value - %u\n", i, arr[i]);
    }
}
