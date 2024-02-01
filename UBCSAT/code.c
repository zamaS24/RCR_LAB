#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *fich_base = NULL;
    FILE *fich_temp = NULL;

    int nbr_propositions, nbr_variables, nbr_clauses, i, but[20], non_but[20];
    char nom_base[20], c;

    printf("Enter CNF file name : ");
    gets(nom_base);
    strcat(nom_base, ".cnf");
    fich_base = fopen(nom_base, "r+");

    if (fich_base == NULL) {
        printf("Cannot open the file :(");
    } else {
        fich_temp = fopen("zoo.cnf", "rw+");
        if (fich_temp == NULL) {
        printf("Cannot transfer the file's content :/");
        } else {
            fscanf(fich_base, "p cnf %d %d", &nbr_variables, &nbr_clauses);
            nbr_clauses += 1;
            fprintf(fich_temp, "p cnf %d %d\n", nbr_variables, nbr_clauses);
        }
        c = fgetc(fich_base);
        while (c != EOF) {
            c = fgetc(fich_base);
            if (c != EOF) {
                fputc(c, fich_temp);
            }
        }

        printf("BC variables:\n");
        printf("1: Louta ;\t\t2: Loutb;\t\t3: Loutc;\n4: mamia;\t5: mamib:\t6: mamic;\n7: pela;\t8:pelb;\t9: pelc;\n10: anima ;\t11: animb;\t12: animc;\n\n");
        printf("Enter number of literals : ");
        scanf("%d", &nbr_propositions);

        for (i = 1; i < nbr_propositions + 1; i++) {

            printf("\nEnter literal number %d : ", i);
            scanf("%d", &but[i]);

            if (but[i] > -13 && but[i] < 13) {
                non_but[i] = but[i] * (-1);
            } else {
                puts("ERROR, invalid code");
            }
        }

        fprintf(fich_temp, "\n");

        for (i = 1; i < nbr_propositions + 1; i++) {
            fprintf(fich_temp, "%d ", non_but[i]);
        }

        fprintf(fich_temp, "0");
        system("ubcsat -alg saps -i zoo.cnf -solve > results.txt");
        fclose(fich_temp);
        int termine = 0;

        FILE *fich = fopen("results.txt", "r+");

        if (fich == NULL) {
            printf("Cannot access results :(\n");
        } else {
            char texte[1000];
            while (fgets(texte, 1000, fich) && !termine) {
                if (strstr(texte, "# Solution found for -target 0")) {

                    printf("\nBC U {Non GOAL} is satisfied. BC infer the GOAL.\nSolution is:\n");
                    fscanf(fich, "\n");
                    while (!strstr(fgets(texte, 1000, fich), "Variables")) {
                        printf("%s", texte);
                    }
                    termine = 1;
                }
            }
            if (termine == 0) {
                printf("\nBC U {Non GOAL} is not satisfied. BC does not infer the GOAL.\n");
                int j;
                for (j = 1; j < nbr_propositions + 1; j++) {
                    printf("%d ", (-1) * but[j]);
                }
                if (j > 2) {
                    printf("Cannot be achieved\n");
                } else {
                    printf("Cannot be achieved\n");
                }
            }
        }
        fclose(fich_temp);
    }

    return 0;
}




// The program appends a new clause to the temporary file. This clause contains the negation of the literals entered by the user.


// The program executes an external solver (ubcsat) using the system command. The solver attempts to find a satisfying assignment for the CNF formula with the additional clause.
// The output of the solver is redirected to a file named results.txt.

// The program opens results.txt and searches for a specific string indicating whether a solution was found.
// If the string is found, the program prints a success message, indicating that the BC U {Non GOAL} is satisfied, and it displays the solution.
// If the string is not found, the program prints a failure message, indicating that the BC U {Non GOAL} is not satisfied.


// Purpose : 
// The program is essentially trying to reason about whether a specific set of goals (specified literals) can be inferred based on a CNF formula representing background knowledge (BC).

// It uses an external solver (ubcsat) to search for a satisfying assignment to the modified CNF formula, where the specified literals are negated.

// If the solver finds a satisfying assignment, it implies that the BC U {Non GOAL} is satisfied, and the program infers the specified goals.

// If the solver doesn't find a satisfying assignment, the program concludes that the specified goals cannot be achieved based on the given background knowledge.

// The purpose is to demonstrate a basic form of automated reasoning using a CNF formula and an external solver to determine whether specific goals can be logically inferred.