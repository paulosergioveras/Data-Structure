#include <stdio.h>
#include <stdlib.h>

//seria tipo uma "lista" dos estudantes:

typedef struct students_list{
    int note;
    int index;
}students_list;

//fila com a lista de estudantes:

typedef struct queue_students{
    students_list *students;
    int size;
}queue_students;


//func para criar uma fila de estudantes:

queue_students create_queue_students(int size){
    queue_students queue_students;
    queue_students.students = (students_list*)malloc(sizeof(students_list) * size); //alocando fila de estudantes
    queue_students.size = size; //atribui o tamanho da fila
    return queue_students;
}

//func para adicioinar/enfileirar os alunos dentro da fila:

void enqueue(int note, int index, queue_students *queue_students){
    students_list student;
    student.note = note; //atribui nota ao aluno
    student.index = index; //atribui uma posição ao aluno
    queue_students->students[index - 1] = student; //adiciona corretamente os alunos na fila
    //return queue_students;
}

//func para fazer a reodenação da fila de estudantes:

void sort_queue_students(queue_students *queue_students){
    for(int i = 1; i < queue_students->size; i++){
        students_list current_student = queue_students->students[i];
        
        int j = i - 1;

        while(j>=0 && queue_students->students[j].note < current_student.note){
            queue_students->students[j + 1] = queue_students->students[j];
            j = j - 1;
        }
        queue_students->students[j + 1] = current_student;
    }
}

//func para liberar a memoria da fila:

void free_queue_students(queue_students *queue_students){
    free(queue_students->students);
}

//func para contar quantos alunos mudaram de posição:

/*int recurrence(queue_students *queue_students){
    int count = 0;

    for(int i = 0; i < queue_students->size; i++){
        if(queue_students->students[i].index == i + 1){
            count++;
        }
    }
    return count;*/


int main(){
    int n; //numero de casos
    scanf("%d", &n);


    for(int i = 0; i < n; i++){
        int num_std; //numero de alunos
        scanf("%d", &num_std);

        queue_students queue = create_queue_students(num_std);
       

        for(int j = 0; j < num_std; j++){
            int note;
            scanf("%d", &note);
            enqueue(note, j+1, &queue);
        }

        sort_queue_students(&queue);

        int count = 0;
        for(int t = 0; t < queue.size; t++){
            if(queue.students[t].index == t + 1){
                count++;
            }
        }
        printf("%d\n", count);
        free_queue_students(&queue);
    }

    return 0;
}
