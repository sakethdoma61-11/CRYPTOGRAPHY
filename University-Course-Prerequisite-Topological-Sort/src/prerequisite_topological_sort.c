#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COURSES 20
#define MAX_NAME 50

typedef struct {
    char name[MAX_NAME];
} Course;

Course courses[MAX_COURSES];
int graph[MAX_COURSES][MAX_COURSES];
int indegree[MAX_COURSES];
int courseCount = 0;

/* Find the index of a course */
int findCourse(char name[]) {
    for (int i = 0; i < courseCount; i++) {
        if (strcmp(courses[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/* Add a new course */
void addCourse(char name[]) {
    if (courseCount >= MAX_COURSES) {
        printf("Maximum number of courses reached.\n");
        return;
    }

    if (findCourse(name) != -1) {
        printf("Course already exists.\n");
        return;
    }

    strcpy(courses[courseCount].name, name);
    courseCount++;

    printf("Course '%s' added successfully.\n", name);
}

/* Add prerequisite relationship */
void addPrerequisite(char prerequisite[], char course[]) {
    int pre = findCourse(prerequisite);
    int current = findCourse(course);

    if (pre == -1 || current == -1) {
        printf("One or both courses do not exist.\n");
        return;
    }

    if (graph[pre][current] == 1) {
        printf("Prerequisite relationship already exists.\n");
        return;
    }

    graph[pre][current] = 1;
    indegree[current]++;

    printf("%s -> %s prerequisite relationship added.\n",
           prerequisite, course);
}

/* Display all courses */
void displayCourses() {
    printf("\nCourses:\n");

    for (int i = 0; i < courseCount; i++) {
        printf("%d. %s\n", i + 1, courses[i].name);
    }
}

/* Display prerequisite relationships */
void displayGraph() {
    printf("\nPrerequisite Relationships:\n");

    int found = 0;

    for (int i = 0; i < courseCount; i++) {
        for (int j = 0; j < courseCount; j++) {
            if (graph[i][j] == 1) {
                printf("%s -> %s\n",
                       courses[i].name,
                       courses[j].name);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No prerequisite relationships available.\n");
    }
}

/* Perform Topological Sort using Kahn's Algorithm */
void topologicalSort() {
    int tempIndegree[MAX_COURSES];
    int queue[MAX_COURSES];
    int front = 0;
    int rear = 0;
    int order[MAX_COURSES];
    int count = 0;

    /* Copy original in-degree values */
    for (int i = 0; i < courseCount; i++) {
        tempIndegree[i] = indegree[i];
    }

    /* Add courses with zero in-degree */
    for (int i = 0; i < courseCount; i++) {
        if (tempIndegree[i] == 0) {
            queue[rear++] = i;
        }
    }

    /* Process the queue */
    while (front < rear) {
        int current = queue[front++];

        order[count++] = current;

        for (int i = 0; i < courseCount; i++) {
            if (graph[current][i] == 1) {
                tempIndegree[i]--;

                if (tempIndegree[i] == 0) {
                    queue[rear++] = i;
                }
            }
        }
    }

    printf("\n----------------------------------------\n");
    printf("COURSE-TAKING ORDER\n");
    printf("----------------------------------------\n");

    /* Cycle detection */
    if (count != courseCount) {
        printf("Cycle detected in the prerequisite graph.\n");
        printf("A valid course-taking order cannot be generated.\n");
        printf("----------------------------------------\n");
        return;
    }

    printf("Valid course sequence:\n\n");

    for (int i = 0; i < count; i++) {
        printf("%d. %s\n", i + 1, courses[order[i]].name);
    }

    printf("\nNo cycle detected.\n");
    printf("Valid topological ordering generated successfully.\n");
    printf("----------------------------------------\n");
}

/* Main function */
int main() {
    int choice;
    char prerequisite[MAX_NAME];
    char course[MAX_NAME];
    char name[MAX_NAME];

    printf("==============================================\n");
    printf(" UNIVERSITY COURSE PREREQUISITE MANAGEMENT\n");
    printf("       USING TOPOLOGICAL SORTING\n");
    printf("==============================================\n");

    while (1) {
        printf("\n");
        printf("------------- MENU ----------------\n");
        printf("1. Add Course\n");
        printf("2. Add Prerequisite Relationship\n");
        printf("3. Display Courses\n");
        printf("4. Display Prerequisite Graph\n");
        printf("5. Generate Valid Course Order\n");
        printf("6. Exit\n");
        printf("-----------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter course name: ");
                scanf(" %[^\n]", name);

                addCourse(name);
                break;

            case 2:
                printf("Enter prerequisite course: ");
                scanf(" %[^\n]", prerequisite);

                printf("Enter dependent course: ");
                scanf(" %[^\n]", course);

                addPrerequisite(prerequisite, course);
                break;

            case 3:
                displayCourses();
                break;

            case 4:
                displayGraph();
                break;

            case 5:
                topologicalSort();
                break;

            case 6:
                printf("\nThank you for using the system.\n");
                exit(0);

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
