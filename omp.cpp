#include <iostream>
#include <omp.h>

using namespace std;

int main(void){
  #pragma omp parallel{
    cout << "Hello World!\n";
  }

  return 0;
}
