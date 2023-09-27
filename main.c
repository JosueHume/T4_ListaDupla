#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

    typedef struct _produto{
    int codigo;
    char nome[20];
    float preco;
    } TpProduto;

    typedef struct _nodo{
    TpProduto info;
    struct _nodo *next;
    struct _nodo *prev;
    } TpNodo;

    typedef struct _lista{
    int nItens;
    struct _nodo *first;
    struct _nodo *last;
    } TpLista;

    TpLista *criarLista()
    {
        TpLista *lista = (TpLista *)malloc(sizeof(TpLista));

        lista->nItens = 0;

        lista->first = (TpNodo *)malloc(sizeof(TpNodo));
        lista->last = (TpNodo *)malloc(sizeof(TpNodo));

        lista->first->next = lista->last;
        lista->last->prev = lista->first;

        return lista;
    }

    void inserir(TpLista *lista, TpProduto produto)
    {
        TpNodo *nodo = (TpNodo *)malloc(sizeof(TpNodo));
        nodo->info = produto;

        nodo->next = lista->last;
        nodo->prev = lista->last->prev;
        lista->last->prev->next = nodo;
        lista->last->prev = nodo;

        lista->nItens++;
    }

    void excluir(TpLista *lista, int codigo)
    {
        TpNodo *atual = lista->first->next;

        while(atual != lista->last)
        {
            if(atual->info.codigo == codigo)
            {
                atual->prev->next = atual->next;
                atual->next->prev = atual->prev;
                free(atual);
                lista->nItens--;

                return;
            }
        }
    }

    void listar(TpLista *lista)
    {
        TpNodo *atual = lista->first->next;

        while(atual != lista->last)
        {
            printf("Codigo: %d, Nome: %s, Preco: %.2f\n", atual->info.codigo, atual->info.nome, atual->info.preco);
            atual = atual->next;
        }
    }

int main()
{
    TpLista *lista = criarLista();
    TpProduto produto;
    int opcao;

    do
    {
        printf("Escolha uma opcao:\n"
               "(1) Para inserir um produto na lista.\n"
               "(2) Para excluir um elemento da lista.\n"
               "(3) Para listar todos os campos dos elementos da lista.\n"
               "(0) Para finalizar o programa\n");

        scanf("%d", &opcao);

        switch(opcao)
        {
            case 1:
                printf("Digite os dados na seguinte ordem: Codigo, Nome e Preco: \n");
                scanf("%d %s %f", &produto.codigo, produto.nome, &produto.preco);
                inserir(lista, produto);
                printf("Produto inserido com sucesso!\n");
                break;
            case 2:
                printf("Digite o codigo do produto a ser removido: \n");
                scanf("%d", &produto.codigo);
                excluir(lista, produto.codigo);
                break;
            case 3:
                listar(lista);
                break;
            case 0:
                printf("Finalizando o programa...\n");
                break;
            default:
                break;
        }
    } while (opcao != 0);

    return 0;
}
