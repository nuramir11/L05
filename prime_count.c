#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int isPrime(int number) {
    if (number < 2) return 0;
    for (int i = 2; i * i <= number; i++) {
        if (number % i == 0) return 0;
    }
    return 1;
}

int countPrimes(int start, int stop) {
    int count = 0;
    for (int i = start; i <= stop; i++) {
        count += isPrime(i);
    }
    return count;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 0;

    int range = atoi(argv[1]);
    int num_subranges = atoi(argv[2]);
    int subrange_size = range * 2 / num_subranges;
    int total_primes = 0;

    for (int i = 0; i < num_subranges; i++) {
        int start = i * subrange_size + 1;
        int stop = (i + 1) * subrange_size;

        int pid = fork();
        if (pid == 0) {
            int result = countPrimes(start, stop);
            exit(result);
        }
    }

    for (int i = 0; i < num_subranges; i++) {
        int status;
        wait(&status);
        if (WIFEXITED(status)) {
            total_primes += WEXITSTATUS(status);
        }
    }

    printf("Total prime numbers: %d\n", total_primes);
    return 0;
}
