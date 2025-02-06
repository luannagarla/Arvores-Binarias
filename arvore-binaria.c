/*
  EP: Árvore Binária de Busca (BST)
  Professor Anderson Ávila - UEL
  Descrição: Completar as funções solicitadas, sem alterar suas assinaturas.

  A main() contém testes que exibem resultados esperados como comentário.
  Quando as funções estiverem corretamente implementadas, esses testes
  devem produzir a saída indicada.
*/

#include <stdio.h>
#include <stdlib.h>

// Estrutura do nó
typedef struct no
{
    int chave;
    int contador;   // número de cópias (frequência) dessa chave
    struct no *esq; // ponteiro para subárvore esquerda
    struct no *dir; // ponteiro para subárvore direita
} NO, *PONT;

// Protótipos das funções
void inicializar(PONT *raiz);
PONT criarNo(int valor);
PONT inserir(PONT raiz, int valor);
PONT removerUmaOcorrencia(PONT raiz, int valor);
PONT removerTodasOcorrencias(PONT raiz, int valor);
PONT buscar(PONT raiz, int valor);
void exibirInOrder(PONT raiz);
int contarNos(PONT raiz);
int contarTotalElementos(PONT raiz);
int kEsimoMenor(PONT raiz, int k);
void imprimirIntervalo(PONT raiz, int min, int max);
// (Opcional) PONT lowestCommonAncestor(PONT raiz, int val1, int val2);

//------------------------------------------------------------------------------
// 1) Inicializar
void inicializar(PONT *raiz)
{
    *raiz = NULL;
}

//------------------------------------------------------------------------------
// 2) Criar nó
PONT criarNo(int valor)
{
    PONT novo = (PONT)malloc(sizeof(NO));
    if (novo)
    {
        novo->chave = valor;
        novo->contador = 1;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

//------------------------------------------------------------------------------
// 3) Buscar
PONT buscar(PONT raiz, int valor)
{
    // COMPLETAR
    // Retorna ponteiro para nó com chave == valor ou NULL se não existir.
    if (raiz == NULL)
        return NULL;

    // Usar a lógica de BST:
    //  - se valor < raiz->chave => buscar à esquerda
    //  - se valor > raiz->chave => buscar à direita
    //  - se valor == raiz->chave => retorna raiz
    if (raiz->chave == valor)
        return raiz;
    else if (valor < raiz->chave)
        return buscar(raiz->esq, valor);
    else
        return buscar(raiz->dir, valor);

    return NULL;
}

//------------------------------------------------------------------------------
// 4) Inserir
PONT inserir(PONT raiz, int valor)
{
    // COMPLETADO
    // Se raiz == NULL => cria nó
    if (raiz == NULL)
        return criarNo(valor);

    // Se valor < raiz->chave => raiz->esq = inserir(raiz->esq, valor)
    if (valor < raiz->chave)
        raiz->esq = inserir(raiz->esq, valor);

    // Se valor > raiz->chave => raiz->dir = inserir(raiz->dir, valor)
    else if (valor > raiz->chave)
        raiz->dir = inserir(raiz->dir, valor);

    // Se valor == raiz->chave => incrementa raiz->contador
    else if (valor == raiz->chave)
        raiz->contador++;

    return raiz;
}

//------------------------------------------------------------------------------
// 5) Remover UMA ocorrência
PONT removerUmaOcorrencia(PONT raiz, int valor)
{
    if (raiz == NULL)
        return NULL;

    // COMPLETAR
    // 1) Buscar nó do valor:
    //    - se não achar, não faz nada
    if (valor < raiz->chave)
        raiz->esq = removerUmaOcorrencia(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = removerUmaOcorrencia(raiz->dir, valor);
    else
    {
        if (raiz->contador > 1)
        {
            raiz->contador--; // 2) se achar e contador>1 => decrementa
        }
        else
        {
            // 3) se contador==1 => remoção clássica de BST (casos 0,1,2 filhos)
            if (raiz->esq == NULL)
            {
                PONT temp = raiz->dir;
                free(raiz);
                return temp;
            }
            else if (raiz->dir == NULL)
            {
                PONT temp = raiz->esq;
                free(raiz);
                return temp;
            }

            PONT temp = raiz->dir;
            while (temp->esq != NULL)
                temp = temp->esq;

            raiz->chave = temp->chave;
            raiz->contador = temp->contador;
            raiz->dir = removerTodasOcorrencias(raiz->dir, temp->chave);
        }
    }
    return raiz;
}

//------------------------------------------------------------------------------
// 6) Remover TODAS ocorrências
PONT removerTodasOcorrencias(PONT raiz, int valor)
{
    if (raiz == NULL)
        return NULL;
    // COMPLETAR
    // 1) Buscar nó do valor
    //    - se não achar, não faz nada
    if (valor < raiz->chave)
        raiz->esq = removerTodasOcorrencias(raiz->esq, valor);
    else if (valor > raiz->chave)
        raiz->dir = removerTodasOcorrencias(raiz->dir, valor);
    else
    {
        if (raiz->esq == NULL)
        {
            PONT temp = raiz->dir;
            free(raiz);
            return temp;
        }
        else if (raiz->dir == NULL)
        {
            PONT temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // 2) se achar => remove nó da BST (casos 0,1,2 filhos)
        PONT temp = raiz->dir;
        while (temp->esq != NULL)
            temp = temp->esq;

        raiz->chave = temp->chave;
        raiz->contador = temp->contador;
        raiz->dir = removerTodasOcorrencias(raiz->dir, temp->chave);
    }
    return raiz;
}

//------------------------------------------------------------------------------
// 7) Exibir InOrder
void exibirInOrder(PONT raiz)
{
    // COMPLETAR
    // Percurso InOrder: esq -> (raiz->chave impresso contador vezes) -> dir
    if (raiz == NULL)
        return;

    exibirInOrder(raiz->esq);
    for (int i = 0; i < raiz->contador; i++)
    {
        printf("%d ", raiz->chave);
    }
    exibirInOrder(raiz->dir);
}

//------------------------------------------------------------------------------
// 8) Contar nós distintos
int contarNos(PONT raiz)
{
    // COMPLETAR
    // Se raiz==NULL => 0
    if (raiz == NULL)
    {
        return 0;
    }

    // Senao => 1 + contarNos(esq) + contarNos(dir)
    return 1 + contarNos(raiz->esq) + contarNos(raiz->dir);
}

//------------------------------------------------------------------------------
// 9) Contar total de elementos (somando contadores)
int contarTotalElementos(PONT raiz)
{
    // COMPLETAR
    // soma = raiz->contador + subárvores
    if (raiz == NULL)
    {
        return 0;
    }

    return raiz->contador + contarTotalElementos(raiz->esq) + contarTotalElementos(raiz->dir); // subarvores
}

//------------------------------------------------------------------------------
// 10) k-ésimo menor
int kEsimoMenor(PONT raiz, int k)
{
    // COMPLETAR
    // Deve considerar o contador de cada nó
    
    if (raiz == NULL) return -1; // Retorne -1 se não existir

    int totalEsquerda = 0;
    if (raiz->esq != NULL) {
        totalEsquerda = contarTotalElementos(raiz->esq);
    }

    if (k <= totalEsquerda) {
        return kEsimoMenor(raiz->esq, k);
    }
    else if (k > totalEsquerda + raiz->contador) {
        return kEsimoMenor(raiz->dir, k - (totalEsquerda + raiz->contador));
    }
    else {
        return raiz->chave;
    }

    return -1; // Retorne -1 se não existir
}

//------------------------------------------------------------------------------
// 11) Imprimir Intervalo [min, max]
void imprimirIntervalo(PONT raiz, int min, int max)
{
    // COMPLETAR
    
    if (raiz == NULL) return; 

    if (raiz->chave > min) {
        imprimirIntervalo(raiz->esq, min, max);
    }

    // Imprimir todos (com contadores) que estejam no intervalo [min, max]
    if (raiz->chave >= min && raiz->chave <= max) {
        for (int i = 0; i < raiz->contador; i++) {
            printf("%d ", raiz->chave);
        }
    }

    if (raiz->chave < max) {
        imprimirIntervalo(raiz->dir, min, max);
    }
}

//------------------------------------------------------------------------------

PONT lowestCommonAncestor(PONT raiz, int val1, int val2)
{
    // COMPLETAR
    // Retorna o nó que é o ancestral comum mais próximo das chaves val1 e val2.

    // • Usando a propriedade da BST:
    // – Se val1 < raiz− > chave e val2 < raiz− > chave, o LCA está na
    // subárvore esquerda.
    // – Se val1 > raiz− > chave e val2 > raiz− > chave, o LCA está na
    // subárvore direita.
    // – Caso contrário, raiz é o LCA (presumindo que val1 e val2 existam).
    // • Se não houver ambas as chaves na árvore, a função pode retornar NULL
    // ou algo similar.

    return NULL;
}

//------------------------------------------------------------------------------
// main() para testes com expectativas de resultado
int main()
{
    PONT raiz;
    inicializar(&raiz);

    raiz = inserir(raiz, 10);
    raiz = inserir(raiz, 5);
    raiz = inserir(raiz, 15);
    raiz = inserir(raiz, 10); // repetido => contador(10)++
    raiz = inserir(raiz, 5);  // repetido => contador(5)++
    raiz = inserir(raiz, 5);  // repetido => contador(5)++
    raiz = inserir(raiz, 18);

    printf("\n--- APÓS INSERIR (10,5,15,10,5,5,18) ---\n");
    printf("InOrder esperado: 5 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 2) Busca por valores
    PONT node5 = buscar(raiz, 5);
    if (node5)
    {
        printf("\nBuscar(5): encontrado com contador=%d (esperado=3)\n", node5->contador);
    }
    else
    {
        printf("\nBuscar(5): não encontrado (inesperado)\n");
    }

    PONT nodeX = buscar(raiz, 999); // valor não existente
    if (!nodeX)
    {
        printf("Buscar(999): não encontrado (esperado)\n");
    }
    else
    {
        printf("Buscar(999): encontrado??? (inesperado)\n");
    }

    // -------------------------------------------------------
    // 3) Remover UMA ocorrência
    //    removerUmaOcorrencia(5) => contador(5) deve passar de 3 para 2
    removerUmaOcorrencia(raiz, 5);

    printf("\n--- APÓS removerUmaOcorrencia(5) ---\n");
    printf("Esperado InOrder: 5 5 10 10 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    node5 = buscar(raiz, 5);
    if (node5)
    {
        printf("Agora contador(5)=%d (esperado=2)\n", node5->contador);
    }

    // -------------------------------------------------------
    // 4) Remover TODAS ocorrências
    //    removerTodasOcorrencias(10) => remove nó com chave=10 por completo
    removerTodasOcorrencias(raiz, 10);

    printf("\n--- APÓS removerTodasOcorrencias(10) ---\n");
    printf("Esperado InOrder: 5 5 15 18\n");
    printf("InOrder obtido:   ");
    exibirInOrder(raiz);
    printf("\n");

    // -------------------------------------------------------
    // 5) Contagem de nós e total de elementos
    //    Árvores resultante: {5(cont=2), 15(cont=1), 18(cont=1)}
    //      => contarNos=3   (chaves distintas: 5,15,18)
    //      => contarTotalElementos=4   (5,5,15,18)
    int qtdNos = contarNos(raiz);
    int totalElem = contarTotalElementos(raiz);
    printf("\ncontarNos => %d (esperado=3)\n", qtdNos);
    printf("contarTotalElementos => %d (esperado=4)\n", totalElem);

    // -------------------------------------------------------
    // 6) k-ésimo menor (considerando contadores)
    //    InOrder real: [5,5,15,18]
    //       k=1 => 5
    //       k=2 => 5
    //       k=3 => 15
    //       k=4 => 18
    //       k=5 => -1 (não existe)
    printf("\n--- Teste k-ésimo menor ---\n");
    printf("k=1 => %d (esperado=5)\n", kEsimoMenor(raiz, 1));
    printf("k=2 => %d (esperado=5)\n", kEsimoMenor(raiz, 2));
    printf("k=3 => %d (esperado=15)\n", kEsimoMenor(raiz, 3));
    printf("k=4 => %d (esperado=18)\n", kEsimoMenor(raiz, 4));
    printf("k=5 => %d (esperado=-1)\n", kEsimoMenor(raiz, 5));

    // -------------------------------------------------------
    // 7) imprimirIntervalo [6..18]
    //    InOrder da árvore: 5,5,15,18
    //    Filtrando [6..18], esperamos: 15 18
    printf("\n--- Teste imprimirIntervalo [6..18] ---\n");
    printf("Esperado: 15 18\nObtido:   ");
    imprimirIntervalo(raiz, 6, 18);
    printf("\n");

    // -------------------------------------------------------
    // 8) Testar LCA (lowestCommonAncestor) - não é opcional
    //    Vamos inserir mais alguns valores para teste de LCA
    //    Situação final da árvore atual: 5(cont=2),15(cont=1),18(cont=1)
    //    Inserir(12), Inserir(16), Inserir(3)
    //    Nova BST (com contadores):
    //       5 (cont=2)
    //           /    \
    //         3(1)   15(1)
    //                /  \
    //              12(1) 18(1)
    //                  \
    //                  16(1)
    raiz = inserir(raiz, 12);
    raiz = inserir(raiz, 16);
    raiz = inserir(raiz, 3);

    printf("\n--- Árvore após inserir(12,16,3) ---\n");
    printf("InOrder esperado: 3 5 5 12 15 16 18\n");
    printf("Obtido:          ");
    exibirInOrder(raiz);
    printf("\n");

    // LCA tests:
    //  LCA(3,5) -> 5 ou 3?
    //     - 3 e 5 estão ambos na subárvore da raiz=5?
    //     - Se a raiz é 5, e 3<5 => esq
    //       => LCA(3,5) deve ser 5, mas depende da estrutura exata
    //  LCA(3,12) -> 5
    //  LCA(16,18) -> 16 ou 15?
    //     => Analisando: 16 < 18 => 16 deve estar na subárvore direita(15)
    //        -> 15 < 16 => goes right => 18
    //        => 16 < 18 => subárvore esquerda de 18
    //        => LCA deve ser 15 ou 18? Precisamos verificar a implementação.
    //  LCA(5,18) -> 5 (pois 5 é raiz, e 18 está à direita)

    PONT nLCA;

    nLCA = lowestCommonAncestor(raiz, 3, 5);
    if (nLCA)
    {
        printf("\nLCA(3,5) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 3, 12);
    if (nLCA)
    {
        printf("LCA(3,12) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 16, 18);
    if (nLCA)
    {
        printf("LCA(16,18) => chave=%d (esperado=15)\n", nLCA->chave);
    }

    nLCA = lowestCommonAncestor(raiz, 5, 18);
    if (nLCA)
    {
        printf("LCA(5,18) => chave=%d (esperado=5)\n", nLCA->chave);
    }

    // Por fim, buscar um LCA com valor inexistente
    nLCA = lowestCommonAncestor(raiz, 100, 3);
    if (!nLCA)
    {
        printf("LCA(100,3) => NULL (esperado=chave nao existe)\n");
    }

    printf("\n--- FIM DOS TESTES ---\n");

    return 0;
}