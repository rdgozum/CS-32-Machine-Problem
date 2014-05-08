#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node node;
struct node {
    char name;
    int tag;
    node *lson;
    node *rson;
};

//Global Variables
FILE *f;
node *head, *pointer_a, *pointer_b, *queue[500];
node *t, *a, *b, *s;
int ltag[50], rtag[50];
int i, j, counter, front, rear, choice, flag;
char data[50], buffer[2], filename[20];


//--------BINARY TREE FUNCTION--------//
void binarytree() {
    front=0, rear=0, flag=0, j=-1;

    if(ltag[counter-2]==1 ||rtag[counter-2]==1) {
        flag=1;
        return;
    }
    do {
        j++;
        pointer_a=(node*)malloc(sizeof(node));
        pointer_a->tag=0;
        pointer_a->rson=NULL;
        pointer_a->lson=NULL;
        pointer_a->name=data[j];
        if(head==NULL) head=pointer_a;
        if(j!=0) {
            if(rear==front) {
                flag=2;
                return;
            }
            pointer_b=queue[rear];
            pointer_b->lson=pointer_a;
            rear=(rear+1)%500;
            //if(rear>front)
        }
        if(ltag[j]==1) {
            queue[front]=pointer_a;
            front=(front+1)%500;
        }
        while(rtag[j]==1) {
            j++;
            pointer_b=malloc(sizeof(node));
            pointer_b->tag=0;
            pointer_b->rson=NULL;
            pointer_b->lson=NULL;
            pointer_b->name=data[j];
            pointer_a->rson=pointer_b;
            pointer_a=pointer_b;
            if(ltag[j]==1) {
                queue[front]=pointer_a;
                front=(front+1)%500;
            }
        }
    } while(j<counter-2);
    if(front!=rear) flag=3;
}   //End of fnx

//--------PREORDER FUNCTION--------//
void preorder() {
    s=NULL;
    a=NULL;
    t=head;
    if(t==NULL) return;
    b=t;

    //Visit current node
    x: printf("%c ", b->name);

    //Descend Left
    s=b->lson;
    if(s!=NULL) {
        b->lson=a;
        a=b;
        b=s;
        goto x;
    }

    //Descend Right
    y: {
        s=b->rson;
        if(s!=NULL) {
            b->rson=a;
            b->tag=1;
            a=b;
            b=s;
            goto x;
        }
    }

    //Ascend
    z: {
        if(a==NULL) return;
        else if(a->tag==0) {
            s=a->lson;
            a->lson=b;
            b=a;
            a=s;
            goto y;
        } else {
            s=a->rson;
            a->rson=b;
            a->tag=0;
            b=a;
            a=s;
            goto z;
        }
    }
}

//--------POSTORDER FUNCTION--------//
void postorder() {
    s=NULL;
    a=NULL;
    t=head;
    if(t==NULL) return;
    b=t;

    //Descend Left
    w: s=b->lson;
    if(s!=NULL) {
        b->lson=a;
        a=b;
        b=s;
        goto w;
    }

    //Descend Right
    y: printf("%c ", b->name);
    s=b->rson;
    if(s!=NULL) {
        b->rson=a;
        b->tag=1;
        a=b;
        b=s;
        goto w;
    }

    //Ascend
    z: {
        if(a==NULL) return;
        else if(a->tag==0) {
            s=a->lson;
            a->lson=b;
            b=a;
            a=s;
            goto y;
        } else {
            s=a->rson;
            a->rson=b;
            a->tag=0;
            b=a;
            a=s;
            goto z;
        }
    }
}

//--------INSTRUCT FUNCTION--------//
instruct(FILE *f) {
    while(!feof(f)) {
        printf("\n\n********DATA SET********\n");
        i=0, counter=0;
        do {
            fgets(buffer, 2, f);
            ltag[i]=atoi(buffer);
            i++;
            counter++;
        } while(!(strchr(buffer, '\n')));

        i=0;
        do {
            if(i==counter-2) fgets(buffer, 3, f);
            else fgets(buffer, 2, f);
            data[i]=buffer[0];
            i++;
        } while(!(strchr(buffer, '\n')));

        i=0;
        do {
            fgets(buffer, 2, f);
            rtag[i]=atoi(buffer);
            i++;
        } while(!(strchr(buffer, '\n')));
        fgets(buffer, 2, f);

        binarytree();

        printf("\nRAW DATA TO BE PROCESSED:\n");
        printf("LSON ");
        for(i=0; i<counter-1; i++) printf("%d", ltag[i]);
        printf("\nDATA ");
        for(i=0; i<counter-1; i++) printf("%c", data[i]);
        printf("\nRSON ");
        for(i=0; i<counter-1; i++) printf("%d", rtag[i]);

        if(flag==1) {
            printf("\n\nINVALID SEQUENCES!\nA leaf node has no right or left son.");
        } else if(flag==2) {
            printf("\n\nINVALID SEQUENCES!\nThere's no node which contains a left son.");
        } else if(flag==3) {
            printf("\n\nINVALID SEQUENCES!\nThe ltag of a tree is 1 even if its SON does not exist.");
        } else {
            printf("\n\nPREORDER SEQUENCE: ");
            preorder();
            printf("\nPOSTORDER SEQUENCE: ");
            postorder();
        }
        printf("\n");

        //Reinitialize
        head=NULL;
        pointer_a=NULL;
        pointer_b=NULL;

    }   //end of while(!feof(f))
    if(choice==2) printf("\n---END OF FILE---");
}   //end of instruct()

//---------------MAIN FUNCTION---------------//
main() {
    if(choice!=3) {
        printf("[1] Keyboard\n[2] External File\n[3] Exit\nENTER CHOICE: ");
        scanf("%d", &choice);
        if(choice!=1 && choice!=2 && choice!=3) {
            printf("\nInvalid Choice!");
            exit(1);
        }

        switch(choice) {
           case 1:
           getchar();
		   while(1) {
                f=fopen("temporary.txt", "w");
                char keyboard[1000], character;
                int c, execute=0;
                c = 0;
                printf("\nStart typing...\n");
                do {
                        character = getchar();
                        keyboard[c] = character;
                        c++;
                        if(character == '\n') execute++;
                } while(execute<3);
                c = c-1;
                keyboard[c] = '\0';
                //keyboard[0] = '\b';
                fprintf(f, "%s\n", keyboard);
                fclose(f);
                f=fopen("temporary.txt", "r");
                if(f==NULL) {
                    printf("\nCould not find '%s'", filename);
                    exit(1);
                }
                instruct(f);
                //remove("temp.txt");
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

