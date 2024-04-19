#include "descente.h"

float f(float x){
	return (x*x*cos(x)-x)/10;
}

double derive(double x){
    double result = 0;
    result = ( (2*x*cos(x) - x*x*sin(x) ) - 1) / 10;
    return result;
}

void getData(float *x0, float *alpha, float *xmin, float *xmax){
    *x0 = 6.0;
    *alpha = 0.02;
    *xmin = -6;
    *xmax = 8;
} 

void gplot(float x0, float alpha, float xmin, float xmax){
    FILE *gp = popen("gnuplot -persist","w");

    if(gp){    // if gnplotPipe is found
    /// Paramètrage de gnuplot
        // fprintf(gp, "set term wxt size 800,600\n");
        fprintf(gp, "set title 'Titre'\n");
        fprintf(gp, "set xlabel 'Temps (s)'\n");
        fprintf(gp, "set ylabel 'Valeurs'\n");
        fprintf(gp, "set xrange [%g:%g]\n",xmin,xmax);
        fprintf(gp,"set xzeroaxis\n");
        fprintf(gp,"set yzeroaxis\n");
        fprintf(gp,"set pointsize 1\n");
        
        //fprintf("set loadpath \"/home/tahina/prog/ProgMrRobinson\"\n");
    /// Tracé de courbes avec gnuplot et modification du style
        // fprintf(gp, "plot (x*x*cos(x)-x)/10 w l lc 'violet' lw 3\n");
        // fprintf(gp,"set object circle at 0,0 size 0.2 fillcolor 'red'\n");
        descente(x0, alpha);
        fprintf(gp,"plot (x*x*cos(x)-x)/10 w l lc 'violet' lw 3,'descente.txt' using 1:2 with linespoints pt 7 ps 1 lc 'blue' lw 3\n");
        // descente(x0,alpha);
        fflush(gp);
        pclose(gp);
    }
}

void descente(float x0, float alpha){
    FILE *pf = fopen("descente.txt","w");
	if(pf == NULL){
        printf("Erreur lor de l'ouverture\n\n");
        exit(1);
    }
	float a = x0;
	int count = 1;
	float a1=0;
	
	a1 = a - alpha*derive(a);
	
	while(fabs(a-a1)>1e-7){
		a = a1;
		fprintf(pf,"%g, %g\n",a,f(a));
		a1 = a - alpha*derive(a);
		count++;
	}
	
	x0 = a;
	
	fclose(pf);
}

int whatToDo(int choice, float *x0, float *alpha, float xmin, float xmax){
	system("clear");
	switch(choice){
		case 1 : 
			break;
		case 2 : 
				printf("Entrez la valeur de x0 : "); 
				scanf("%f",x0);
				choice = 1;
			break;
		case 3 : 
				printf("Entrez la pas alpha : "); 
				scanf("%f",alpha);
				choice = 1;
			break;
		case 0:
			break;
		default:
			choice = 1;
			break;
	}
    gplot(*x0, *alpha, xmin, xmax );
	if(choice == 1)
		return 0;
	return choice;
}

int menu(){
	printf("veuillez choisir le chose que vous vouler faire\n");
	printf("\t[1] - Tracer le courbe \n");
	printf("\t[2] - Entrer le valeur initiale\n");
	printf("\t[3] - Changer le pas\n");
	printf("\t[0] - Pour quitter le programme\n");
    int a = getChoice();
	return a;
}

int getChoice(){
	int choice = 0;
	printf("entrer votre choix : ");
	scanf("%d",&choice);
	return choice;
}