#include <stdio.h>
#include <omp.h>

int main(int argc, char** argv){
    omp_set_dynamic(0);
    omp_set_num_threads(15);
    #pragma omp parallel
    {
        printf("Хеллоу Світе! То є Карпюк Ігор Вікторович з %dго процесу\n", omp_get_thread_num() );
    }
    return 0;
}