#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
struct employee
{
    int id;
    int sal;
    char empName[40];
    char designation[40];
    struct employee *next;
};

struct employee *insert(struct employee *root, int id, int sal, char name[], char desg[])
{
    struct employee *temp;

    temp = (struct employee *)malloc(sizeof(struct employee));
    temp->id = id;
    strcpy(temp->empName, name);
    strcpy(temp->designation, desg);
    temp->sal = sal;
    temp->next = NULL;
    if (root == NULL)
    {
        root = temp;
    }
    else
    {
        struct employee *p;
        p = root;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = temp;
    }
    cout << "Inserted\n";
    return (root);
}
void display(struct employee *p)
{

    cout << "\n Emp No         :" << p->id;
    cout << "\n Name           :" << p->empName;
    cout << "\n Designation    :" << p->designation;
    cout << "\n Salary         :" << p->sal;
    cout << "\n-------------------------------------\n";
}
struct employee *deleteNode(struct employee *root, int id)
{
    struct employee *ptr;
    struct employee *bptr;

    if (root->id == id)
    {
        ptr = root;
        cout << "\n Node deleted:";
        display(root);
        root = root->next;
        free(ptr);
        return (root);
    }
    for (ptr = root->next, bptr = root; ptr != NULL; ptr = ptr->next, bptr = bptr->next)
    {
        if (ptr->id == id)
        {
            cout << "\n Node deleted:";
            display(ptr);
            bptr->next = ptr->next;
            free(ptr);
            return (root);
        }
    }
    cout << "\n Employee Number not found ";
    return (root);
}
void search(struct employee *root, int key)
{
    struct employee *ptr;

    for (ptr = root; ptr != NULL; ptr = ptr->next)
    {
        if (ptr->id == key)
        {
            printf("\n Key found:");
            display(ptr);
            return;
        }
    }
    cout << "\n Employee Number not found ";
}
void print(struct employee *first)
{
    struct employee *ptr;
    cout << "\n Employee Details...\n";
    for (ptr = first; ptr != NULL; ptr = ptr->next)
    {
        display(ptr);
    }
}
int main()
{
    struct employee *linkList;
    char name[40], desig[40];
    int choice = 1;
    int id, sal;
    linkList = NULL;
    ifstream file("input.txt");
    string str;
    string a[10];
    char buffer[50];
    char *b[50];
    int i;
    int o, p;
    while (getline(file, str))
    {
        i = 0;
        strcpy(buffer, str.c_str());
        char *ptr;
        ptr = strtok(buffer, ",");
        while (ptr != NULL)
        {
            b[i] = ptr;
            i++;
            ptr = strtok(NULL, ",");
        }
        o = atoi(b[0]);
        p = atoi(b[3]);
        linkList = insert(linkList, o, p, b[1], b[2]);
    }
    cout << "---------------------------------------------\n";
    cout << "Press 1 to DELETE a node from the list       \n";
    cout << "Press 2 to DISPLAY the list                 \n";
    cout << "Press 3 to SEARCH the list                   \n";
    cout << "Press 4 to EXIT                              \n";
    cout << "---------------------------------------------\n";
    do
    {
        cout << "\nEnter a choice:";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "\n\n Enter the employee number to be deleted: ";
            cin >> id;
            linkList = deleteNode(linkList, id);
            break;
        case 2:
            if (linkList == NULL)
            {
                cout << "\n List empty";
                break;
            }
            print(linkList);
            break;
        case 3:
            cout << "\n\n Enter the employee number to be searched: ";
            cin >> id;
            search(linkList, id);
            break;
        case 4:
            break;
        default:
            "Enter a valid choice";
        }
    } while (choice != 5);
    return 0;
}