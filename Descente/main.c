#include "descente.h"

int main(){
    float xmin = 0.0,
          xmax = 0.0,
          alpha = 0.0,
          x0 = 0.0;
    int choice = 0;


    getData(&x0, &alpha, &xmin, &xmax);

    choice = menu();

    // gplot(x0, alpha, xmin, xmax );
    while(choice){
        choice = whatToDo(choice, &x0, &alpha, xmin, xmax);
        choice = menu();
    }

}