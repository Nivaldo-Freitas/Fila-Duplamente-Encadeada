#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <ios>
using namespace std;

class Node
{
    public:
    int data;    // Prioridade do Paciente
    string name; // Nome do paciente
    int id_code; // Codigo que será gerado ou inserido
    Node* next;  // Ponteiro para o proximo da fila
    Node* prev;  // Ponteiro para o anterior da fila
};




/* Dada a referencia (ponteiro de ponteiro)
Para a cabeça da lista
e os dados do paciente, insere um novo nó
Na frente da lista */
void push(Node** head_ref, int new_data, string new_name, int new_id_code)
{
    /* 1. Aloca novo Nó */
    Node* new_node = new Node();

    /* 2. Adiciona os dados */
    new_node->data = new_data;
    new_node->name = new_name;
    new_node->id_code = new_id_code;

    /* 3. Faz do novo nó a Cabeça e o anterior aponta para NULL */
    new_node->next = (*head_ref);
    new_node->prev = NULL;

    /* 4. Muda prev da cabeça para new node */
    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;

    /* 5. faz o referencial da cabeça apontar para o novo nó */
    (*head_ref) = new_node;
}

/* Dado um Nó como Nó Anterior, insere
um novo nó após o Nó dado */
void insertAfter(Node* prev_node, int new_data, string new_name, int new_id_code)
{
    /*1. Checa se o nó anterior aponta para NULL */
    if (prev_node == NULL)
    {
        cout<<"O anterior está apontando para NULL *Function Insert After";
        return;
    }

    /* 2. Alloca novo Nó */
    Node* new_node = new Node();

    /* 3. Adiciona os dados aos atributos */
    new_node->data = new_data;
    new_node->name = new_name;
    new_node->id_code = new_id_code;

    /* 4. Captura para onde o anterior está apontando para próximo e faz o novo nó apontar para este. */
    new_node->next = prev_node->next;

    /* 5. Faz o próximo do nó anterior apontar para novo nó */
    prev_node->next = new_node;

    /* 6. Faz o nó inserido apontar anterior para o nó anterior. */
    new_node->prev = prev_node;

    /* 7. Faz o anterior do próximo nó apontar para o nó inserido */
    if (new_node->next != NULL)
        new_node->next->prev = new_node;
}

Node* escolhe_lugar_na_fila(Node* head_ref)
{
    Node* node_aux = head_ref;
    if(head_ref == NULL)
        return head_ref;
    while (node_aux->data >= head_ref->data) {
        if (node_aux->next == NULL) {
            return(node_aux);
        }
        node_aux = head_ref;
        head_ref = head_ref->next;
    }
    return(node_aux);
}

/* Dada a referencia (pointer to pointer) para a cabeça
da LDE, acrescenta o novo nó ao final desta. */
void append(Node** head_ref, int new_data, string new_name, int new_id_code)
{
    /* 1. Aloca o nó */
    Node* new_node = new Node();

    Node* last = *head_ref; /* Usarei no passo 5*/

    /* 2. Adiciona os dados */
    new_node->data = new_data;
    new_node->name = new_name;
    new_node->id_code = new_id_code;

    /* 3. Esse novo nó sera o ultimo nó, então
        faço proximo apontar para NULL*/
    new_node->next = NULL;

    /* 4. Se a LDE estiver vazia, faço do
        novo nó a nova cabeça */
    if (*head_ref == NULL)
    {
        new_node->prev = NULL;
        *head_ref = new_node;
        return;
    }

    /* 5. em caso do next do last não apontar para NULL, faço o ultimo apontar para o next do ultimo. */
    while (last->next != NULL)
        last = last->next;

    /* 6. Faço o próximo do ultimo nó apontar para o novo nó */
    last->next = new_node;

    /* 7. Faço o novo nó apontar para o ultimo */
    new_node->prev = last;

    return;
}

/* Função para Deletar elemento em Fila Duplamente Encadeada.
head_ref --> Ponteiro para o ponteiro do nó cabeça.
del é o ponteiro para o nó que vai ser deletado. */
void deleteNode(Node** head_ref, Node* del)
{
    /* base case */
    if (*head_ref == NULL || del == NULL)
        return;

    /* If node to be deleted is head node */
    if (*head_ref == del)
        *head_ref = del->next;

    /* Change next only if node to be
    deleted is NOT the last node */
    if (del->next != NULL)
        del->next->prev = del->prev;

    /* Change prev only if node to be
    deleted is NOT the first node */
    if (del->prev != NULL)
        del->prev->next = del->next;

    /* Finally, free the memory occupied by del*/
    free(del);
    return;
}

// This function prints contents of linked list starting
// from the given node
void printList(struct Node* node)
{
    struct Node* last;
    cout <<"\n| Prioridade  |  Nome do Paciente  |        ID        |\n";
    while (node != NULL) {
        cout << "    " << node->data
             << "                 " << node->name
             << "                 " << node->id_code << endl;
        last = node;
        node = node->next;
    }
}

void menu()
{
    cout << endl << "                Bem vindo ao escritorio do Nivaldinho " << endl << endl;
    cout << "       O que precisa fazer agora? Digite o numero da opcao desejada." << endl;
    cout << "1 - Chamar Paciente    |    2 - Inserir Paciente    |    3 - Exibir a fila" << endl;
    cout << "Opcao: ";
}

int coleta_prioridade()
{

    int new_data;
    cout << endl << "Qual a prioridade de atendimento de 1 a 3, sendo 3 maior prioridade e 1 menor prioridade?" << endl << "A prioridade de atendimento do Paciente e: ";
    cin >> new_data;
    return(new_data);
}
string coleta_nome()
{
    string new_name;
    cout << "Qual o nome do Paciente?" << endl << "O nome do Paciente é: ";
    cin >> new_name;
    return(new_name);
}


int main()
{
    /* Começamos com a lista vazia */
    Node* head = NULL;
    struct Node* node_aux;
    bool flag = true;
    int opcao = 0;
    int prioridade = 0;
    int intaux = 0;
    string stringaux = "";

    while(flag)
    {
        menu();
        cin >> opcao;
        switch(opcao)
        {
            case 1:
                break;
            case 2:
                prioridade = coleta_prioridade();
                stringaux = coleta_nome();
                intaux = rand() % 100 + 1;
                node_aux = escolhe_lugar_na_fila(head);
                if(node_aux != NULL){
                    insertAfter(node_aux, prioridade, stringaux, intaux);
                }else{
                    append(&head, prioridade, stringaux, intaux);
                }
                break;
            case 3:
                printList(head);
                break;
            default:
                break;
        }
    }
    cout << "sai";
    system("pause");
    // Insert 6. So linked list becomes 6->NULL
        //append(&head, 6, "luffy", 2);

    // Insert 7 at the beginning. So
     //linked list becomes 7->6->NULL
        //push(&head, 7, "joao", 3);

    // Insert 1 at the beginning. So
    // linked list becomes 1->7->6->NULL
        //push(&head, 1, "diana", 4);

    // Insert 4 at the end. So linked
    // list becomes 1->7->6->4->NULL
        //append(&head, 4, "zoro", 6);

    // Insert 8, after 7. So linked
    // list becomes 1->7->8->6->4->NULL
        //insertAfter(head->next, 8, "sanji", 1);

    //cout << "Created DLL is: ";
    //printList(head);

    return 0;
}
