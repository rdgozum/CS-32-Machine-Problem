#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//-----------------STRUCTURE------------------//
typedef struct student student;
typedef struct course course;

struct course {
    char cname[5];
    course *next;
    student *down;
};

struct student {
    char sname[5];
    student *next;
};

//--Global Variables
course *cour, *tail_c, *head_c, *rover1_c, *rover2_c;
student *stud, *tail_s, *rover1_s, *rover2_s;
FILE *f;
char filename[20];
char buffer[5], buffer2[5];
int choice;

//---------------INSTRUCT FUNCTION---------------//
void instruct(FILE *f) {
    while(!feof(f)) {
    //---Linked List
        printf("\n*********DATA SET*********");
        printf("\n\n<RAW DATA TO BE PROCESSED>\n");
        int count_c=0;          //increments everytime we add a course.
        fgets(buffer, 4, f);
        int cour_num = atoi(buffer);    //number of courses indicated on the text file.
        int k=0;

        while(count_c<=cour_num) {      //while loop for courses
            cour=(course*)malloc(sizeof(course));
            if(count_c==0) {
                strcpy(cour->cname, fgets(buffer, 5, f));
                head_c=cour;
                tail_c=cour;
            } else {
                fgets(buffer, 5, f);
                strcpy(cour->cname, buffer);
                tail_c->next=cour;
                tail_c=cour;
            }
            count_c++;
            tail_c->next=NULL;
            tail_c->down=NULL;
            if(count_c<=cour_num) printf("\n%s", tail_c->cname);
            else break;

            while(!(strchr(buffer, '\n'))) {       //while loop for students
                stud=(student*)malloc(sizeof(student));
                fgets(buffer, 5, f);
                strcpy(buffer2, buffer);

                if(buffer==NULL) break;
                if(buffer[3]=='\n') {
                   buffer2[3]=' ';
                }
                strcpy(stud->sname, buffer2);
                if(tail_c->down==NULL) {
                    tail_c->down=stud;
                    tail_s=stud;
                } else {
                    tail_s->next=stud;
                    tail_s=stud;
                }
                tail_s->next=NULL;
                printf("%s", tail_s->sname);
            }
        }

        //---Adjacency Matrix
        int i=0, j=0, ret_val=0;
        int arry[cour_num][cour_num];
        rover1_c=head_c;
        rover2_c=head_c;
        printf("\n\n<ADJACENCY MATRIX>\n");
        while(rover2_c->next!=NULL) {
            rover2_s=rover2_c->down;
            while(rover1_c->next!=NULL) {
                rover1_s=rover1_c->down;
                while(rover2_s!=NULL) {
                    if(strcmp(rover1_s->sname, rover2_s->sname)==0) {
                        ret_val=1;
                        break;
                    }
                    if(rover1_s->next!=NULL) {
                        rover1_s=rover1_s->next;
                    } else {
                        rover2_s=rover2_s->next;
                        rover1_s=rover1_c->down;
                    }
                }
                if(ret_val!=1) ret_val=0;
                    arry[i][j]=ret_val;
                    ret_val=0;
                    rover1_c=rover1_c->next;
                if(rover1_c==rover2_c) {
                   rover1_c=rover1_c->next;
                   j++;
                }
                j++;
                rover2_s=rover2_c->down;
            }
            rover2_c=rover2_c->next;
            rover1_c=head_c;
            j=0;
            i++;
        }

        //--Printing the Adjacency Matrix
        printf("\n");
        printf("     ");
        for(k=1; k<=cour_num; k++) {
            if(k<10) printf("0%d   ", k);
            else printf("%d   ", k);
        }
        k=0;
        printf("\n");

        for(i=0; i<cour_num; i++) {
            while(k<=cour_num) {
                k++;
                if(k<10) printf("0%d  ", k);
                else printf("%d  ", k);
                break;
            }
            printf(" ");
            for(j=0; j<cour_num; j++) {
                    if(i==j) arry[i][j]=0;
                    printf("%d    ", arry[i][j]);
            }
            printf("\n");
        }

        //--COLORING
        int color_arry[cour_num], color=0, row_trav=0, col_trav=0, anot_flag=0;

        for(i=0; i<cour_num; i++) color_arry[i]=0;  //create an array for colors
        i=0, j=0;
        color++;

        while(i<cour_num) {
            if(color_arry[i]==0) {
                if(color_arry[i]==0) color_arry[i]=color;
                while(j<cour_num) {
                    if(i==j || arry[i][j]==1) j++;
                    else {
                        if(color_arry[j]==0) {
                            col_trav=0;
                            row_trav=j;
                            while(col_trav<cour_num) {
                                if(arry[row_trav][col_trav]==1) {
                                    if(color_arry[col_trav]==color_arry[i]) {
                                        anot_flag=1;
                                        break;
                                    }
                                }
                                col_trav++;
                            }
                            if(anot_flag==0) color_arry[j]=color_arry[i];
                        }
                        anot_flag=0;
                        j++;
                    }
                }
                color++;
            }
            j=0;
            i++;
        }

        printf("\n<SCHEDULE>\n\n");
        i=1;
        while(i<color) {
            if(i==1) printf("Monday 8:30-10:00 -- ");
            else if(i==2) printf("Monday 10:00-11:30 -- ");
            else if(i==3) printf("Tuesday 8:30-10:00 -- ");
            else if(i==4) printf("Tuesday 10:00-11:30 -- ");
            else if(i==5) printf("Wednesday 1:00-2:30 -- ");
            else if(i==6) printf("Wednesday 2:30-4:00 -- ");
            else if(i==7) printf("Thursday 8:30-10:00 -- ");
            else if(i==8) printf("Thursday 10:00-11:30 -- ");
            else if(i==9) printf("Friday 1:00-2:30 -- ");
            else if(i==10) printf("Friday 2:30-4:00 -- ");
            else if(i==11) printf("Saturday 8:30-10:00 -- ");
            else if(i==12) printf("Saturday 10:00-11:30 -- ");
            else if(i==13) printf("Saturday 1:00-2:30 -- ");
            else if(i==14) printf("Saturday 2:30-4:00 -- ");
            else if(i==15) printf("Monday 1:00-2:30 -- ");

            for(j=0; j<cour_num; j++) {
                if(color_arry[j]==i) {
                    if(j+1>9) printf("C%d ", j+1);
                    else printf("C0%d ", j+1);
                }
            }
            i++;
            printf("\n");
        }

    printf("\n");
    }   //end of while(!feof(f))
    if(choice!=1) printf("~~~~~~~~~~~END OF FILE~~~~~~~~~~~\n");
}

//---------------MAIN FUNCTION---------------//
main() {
    //Type of Input
    if(choice!=3) {
        printf("[1] Keyboard\n[2] External File\n[3] Exit\nENTER CHOICE: ");
        scanf("%d", &choice);
        if(choice!=1 && choice!=2 && choice!=3) {
            printf("\nInvalid Choice!");
            exit(1);
        }

        switch(choice) {
           case 1:
		   while(1) {
                f=fopen("temp.txt", "w");
                char keyboard[1000], character, temp_cour_num[5];
                int c, execute=0;
                c = 0;
                printf("\nNumber of courses: ");
                scanf("%s", temp_cour_num);
                printf("Input data below\n");
                do {
                        character = getchar();
                        keyboard[c] = character;
                        c++;
                        if(character == '\n') execute++;
                } while(execute<=atoi(temp_cour_num));
                c = c-1;
                keyboard[c] = '\0';
                fprintf(f, "%s%s\n", temp_cour_num, keyboard);
                fclose(f);
                f=fopen("temp.txt", "r");
                if(f==NULL) {
                    printf("\nCould not find '%s'", filename);
                    exit(1);
                }
                instruct(f);
                remove("temp.txt");
                printf("------------------");
		   }

           case 2:
            printf("Enter Filename: ");
            scanf("%s", filename);
            f=fopen(filename, "r");
            if(f==NULL) {
                printf("\nCould not find '%s'", filename);
                exit(1);
            }
            instruct(f);
            exit(1);

            case 3:
            exit(1);
        }
    }
}

