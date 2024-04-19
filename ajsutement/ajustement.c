#include "ajustement.h"

void linLastSq(float *xd, float *yd, int dim, float *a){
    float xdm = 0,
          ydm = 0;
    float s = 0,
          num = 0,
          denom = 0;
    for(int i=0; i<dim; i++)
        s += xd[i];
    xdm = s/dim;
    s = 0;
    for(int i=0; i<dim; i++)
        s += yd[i];
    ydm = s/dim;
    s = 0;
    for(int i=0; i<dim; i++)
        num += (xd[i] - xdm) * (yd[i] - ydm);
    for(int i=0; i<dim; i++)
        denom += (xd[i] - xdm) * (xd[i] - xdm);
    a[1] = num / denom;
    a[0] = ydm - a[1]*xdm;

    printf("\nMethode des moindres carres statistique :\n");
    printf("a = %f\n", a[1]);
    printf("b = %f\n", a[0]);
}

void leastSquare(float *xd, float *yd, int dim, float *a){
    float sxk = 0,
          syk = 0,
          sxk2 = 0,
          sxkyk = 0;

    for(int k=0; k<dim; k++)
        sxk += xd[k];
    for(int k=0; k<dim; k++)
        syk += yd[k];
    for(int k=0; k<dim; k++)
        sxk2 += xd[k]*xd[k];
    for(int k=0; k<dim; k++)
        sxkyk += xd[k]*yd[k];

    float D = 0,
          Da0 = 0,
          Da1 = 0;
    D = dim*sxk2 - sxk*sxk;
    Da0 = dim*sxkyk - sxkyk*sxk;
    Da1 = dim*sxkyk - sxk*syk;

    a[0] = Da0 / D;
    a[1] = Da1 / D;
}

void gplot(float ymin, float ymax, float *als){
    FILE *gp = popen("gnuplot -persist","w");

    if(gp){    // if gnplotPipe is found
    /// Paramètrage de gnuplot
        // fprintf(gp, "set term wxt size 800,600\n");
        fprintf(gp, "set title 'Traceur gnuplot'\n");
        fprintf(gp, "set xlabel 'x'\n");
        fprintf(gp, "set ylabel 'y'\n");
        //fprintf(gp, "set yrange [%f:%f]\n",ymin,ymax);
        fprintf(gp,"set xzeroaxis\n");
        fprintf(gp,"set yzeroaxis\n");
        // fprintf(gp,"set pointsize 1\n");
        fprintf(gp, "set key top left\n");
        // fprintf("set loadpath \"/home/tahina/prog/ProgMrRobinson\"\n");
    /// Tracé de courbes avec gnuplot et modification du style
        fprintf(gp,"f(x)=%g*x+%g\n",als[1],als[0]);
        //fprintf(gp, "plot [x=-1:8] [y=-2:2] \"curve.txt\" using 1:2 with linespoints pt 7 ps 1,sin(x) w l lc 'blue' lw 3, cos(x) w l lc 'red' lw 3\n");
        fprintf(gp,"plot 'data.txt' using 1:2 with points pt 7 ps 1, f(x) w l lw 3 lc 'red'\n");
        //fprintf(gp,"plot sin(x)")
        fflush(gp);
        pclose(gp);
    }
    else 
        printf("gnuplot not found ...");
}

void getData(char *filename, float *xmin, float *xmax, float *ymin, float *ymax, int *dim, float **xd, float **yd){
    FILE *pf = NULL;
    float xt = 0,
          yt = 0,
          *xdt = NULL,
          *ydt = NULL;

    pf = fopen(filename, "r");

    if(pf != NULL){
        fscanf(pf,"%d",dim);
    /// Allocation et lecture des données
        xdt = newVect(*dim);
        ydt = newVect(*dim);
        *ymin = 1e8;
        *ymax = -1e8;

        for(int i=0; i<*dim; i++){
            fscanf(pf, "%f, %f",&xt, &yt);
            xdt[i] = xt;
            ydt[i] = yt;
            if(ydt[i] < *ymin)
                *ymin = ydt[i];
            if(ydt[i] > *ymax)
                *ymax = ydt[i];
        }
        fclose(pf);
        *xd = xdt;
        *yd = ydt;
    }
    else
        error("Impossible d'ouvrir d'ouvrir le fichier\n");
}

float *newVect(int dim){
    float *v = NULL;
    v = (float*)malloc(dim*sizeof(float));
    if(v == NULL) 
        error("Impossible de cree le vecteur\n");
    return v;
}

void error(const char *message){
    printf("%s\n", message);
}