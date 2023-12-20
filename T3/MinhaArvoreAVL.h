#ifndef MINHA_ARVORE_AVL_HPP
#define MINHA_ARVORE_AVL_HPP

#include "ArvoreBinariaDeBusca.h"

/**
 * @brief Representa uma árvore AVL.
 *
 * @tparam T O tipo de dado guardado na árvore.
 */
template <typename T>
class MinhaArvoreAVL final : public ArvoreBinariaDeBusca<T>
{
    virtual ~MinhaArvoreAVL()
    {
        destrutor(this->raiz);
    }

    virtual bool vazia() const
    {
        return (this->raiz == nullptr);
    }

    virtual int quantidade() const
    {
        return this->qtd_recursiva(this->raiz);
    }

    virtual bool contem(T chave) const
    {
        Nodo<T> *cont = this->raiz;
        while (cont != nullptr){
             if (cont->chave == chave){
                return true;
            }
            else{
                if (chave > cont->chave){
                    cont = cont->filhoDireita;
                }
                else{
                    cont = cont->filhoEsquerda;
                }
            }
        }
        return false;
    }

    virtual std::optional<int> altura(T chave) const
    {
        Nodo<T> *nodo = this->raiz;
        while (nodo != nullptr){
            if (nodo->chave == chave){
                return nodo->altura;
            }
            else{
                if (chave > nodo->chave){
                    nodo = nodo->filhoDireita;
                }
                else{
                    nodo = nodo->filhoEsquerda;
                }
            }
        }
        return std::nullopt;
    }

    virtual void inserir(T chave)
    {
        if(this->raiz == nullptr){
            this->raiz = new Nodo<T>{chave};
        }
        else{
           this->inserir_recursiva(this->raiz, chave); 
        } 
    }

    virtual void remover(T chave)
    {
        if(this->contem(chave) == false){
            return;
        }
        else if((this->raiz->chave == chave) && (this->raiz->filhoDireita == nullptr && this->raiz->filhoEsquerda == nullptr)){
            delete this->raiz;
            this->raiz = nullptr;
        }
        else{
            this->remover_recursiva(this->raiz, chave); 
        }
    }

    virtual std::optional<T> filhoEsquerdaDe(T chave) const
    {
        Nodo<T> *pai = this->raiz;
        while (pai != nullptr){
            if (pai->chave == chave && pai->filhoEsquerda != nullptr){
                return pai->filhoEsquerda->chave;
            }
            if (chave < pai->chave){
                pai = pai->filhoEsquerda;
            }
            else{
                pai = pai->filhoDireita;
            }   
        }
        return std::nullopt;
    }

    virtual std::optional<T> filhoDireitaDe(T chave) const
    {
        Nodo<T> *pai = this->raiz;
        while (pai != nullptr){
            if (pai->chave == chave && pai->filhoDireita != nullptr){
                return pai->filhoDireita->chave;
            }
            if (chave >= pai->chave){
                pai = pai->filhoDireita;
            }
            else{
                pai = pai->filhoEsquerda;
            }
        }
        return std::nullopt;
    }

    virtual ListaEncadeadaAbstrata<T> *emOrdem() const
    {
        MinhaListaEncadeada<T> *listaC = new MinhaListaEncadeada<T>();
        this->rec_emOrdem(this->raiz, listaC);
        return listaC;
    }

    virtual ListaEncadeadaAbstrata<T> *preOrdem() const
    {
        MinhaListaEncadeada<T> *listaA = new MinhaListaEncadeada<T>();
        this->rec_preOrdem(this->raiz, listaA);
        return listaA;
    }

    virtual ListaEncadeadaAbstrata<T> *posOrdem() const
    {
        MinhaListaEncadeada<T> *listaE = new MinhaListaEncadeada<T>();
        this->rec_posOrdem(this->raiz, listaE);
        return listaE;
    }

//////////////////////////////////////////////////////////////////////////////////////////////////////////

    Nodo<T>* rot_dir_esq(Nodo<T>* nodo)
    {
        Nodo<T> *newRaiz = nodo->filhoDireita->filhoEsquerda;
        Nodo<T> *oldRaiz = newRaiz->filhoDireita;

        newRaiz->filhoDireita = nodo->filhoDireita;
        nodo->filhoDireita->filhoEsquerda = oldRaiz;

        nodo->filhoDireita = newRaiz;
        newRaiz->filhoEsquerda = nodo->filhoDireita->filhoEsquerda;

        nodo->filhoDireita->filhoDireita->altura = atualizar_altura(nodo->filhoDireita->filhoDireita); //h do 2
        newRaiz->altura = atualizar_altura(newRaiz); //h do 3
        
        nodo->filhoDireita = newRaiz->filhoEsquerda; //ta null o 3
        newRaiz->filhoEsquerda = nodo;

        nodo->altura = atualizar_altura(nodo); // h do 4
        newRaiz->altura = atualizar_altura(newRaiz); // h do 3

        return newRaiz;
    }

    Nodo<T>* rot_esq_dir(Nodo<T>* nodo)
    {
        Nodo<T> *newRaiz = nodo->filhoEsquerda->filhoDireita;
        Nodo<T> *oldRaiz = newRaiz->filhoEsquerda;

        newRaiz->filhoEsquerda = nodo->filhoEsquerda;
        nodo->filhoEsquerda->filhoDireita = oldRaiz;

        nodo->filhoEsquerda = newRaiz;
        newRaiz->filhoDireita = nodo->filhoEsquerda->filhoDireita;

        nodo->filhoEsquerda->filhoEsquerda->altura = atualizar_altura(nodo->filhoEsquerda->filhoEsquerda); //h do 2
        newRaiz->altura = atualizar_altura(newRaiz); //h do 3

        nodo->filhoEsquerda = newRaiz->filhoDireita; //ta null o 3
        newRaiz->filhoDireita = nodo;

        nodo->altura = atualizar_altura(nodo); // h do 4
        newRaiz->altura = atualizar_altura(newRaiz); // h do 3

        return newRaiz;
    }

    Nodo<T>* rot_dir(Nodo<T>* nodo)
    {
        Nodo<T> *newRaiz = nodo->filhoEsquerda;
        Nodo<T> *oldRaiz = newRaiz->filhoDireita;

        newRaiz->filhoDireita = nodo;
        nodo->filhoEsquerda = oldRaiz;

        nodo->altura = atualizar_altura(nodo);
        newRaiz->altura = atualizar_altura(newRaiz);

        return newRaiz;
    }

    Nodo<T>* rot_esq(Nodo<T>* nodo)
    {
        Nodo<T> *newRaiz = nodo->filhoDireita; 
        Nodo<T> *oldRaiz = newRaiz->filhoEsquerda;

        newRaiz->filhoEsquerda = nodo;
        nodo->filhoDireita = oldRaiz;

        nodo->altura = atualizar_altura(nodo);
        newRaiz->altura = atualizar_altura(newRaiz);

        return newRaiz;
    }

    Nodo<T> *x (Nodo<T> *nodo){
        Nodo<T> *tmp = nodo->filhoEsquerda->filhoEsquerda;
        Nodo<T> *nulo = tmp->filhoDireita->filhoDireita;
        nodo->filhoEsquerda->filhoEsquerda = tmp->filhoDireita;
        tmp->filhoDireita->filhoEsquerda = nulo;
        nodo->filhoEsquerda = tmp;
        nodo->altura = atualizar_altura(nodo); 
        return tmp;  
    }

    void verifica(Nodo<T> *nodo)
    {
        if(nodo == this->raiz){
            int fatorB_raiz = get_fatorB(this->raiz);
            if(fatorB_raiz > 1){ 
                int raizEsq = get_fatorB(this->raiz->filhoEsquerda);
                //Testa o nodo filhoEsquerda:
                if(raizEsq >= 0){             
                    this->raiz = rot_dir(this->raiz);
                }
                else if(raizEsq < 0 && this->raiz->filhoEsquerda->filhoDireita != nullptr){
                    int raizEsqDir = get_fatorB(this->raiz->filhoEsquerda->filhoDireita);
                    if(raizEsqDir <= 0){
                        this->raiz = rot_esq_dir(this->raiz);
                    }    
                }

            }else if(fatorB_raiz < -1){
                int raizDir = get_fatorB(this->raiz->filhoDireita);
                //Testa o nodo filhoDireita:
                if(raizDir <= 0){            
                    this->raiz = rot_esq(this->raiz);
                }
                else if(raizDir > 0 && this->raiz->filhoDireita->filhoEsquerda != nullptr){
                    int raizDirEsq = get_fatorB(this->raiz->filhoDireita->filhoEsquerda);
                    if(raizDirEsq >= 0){
                        this->raiz = rot_dir_esq(this->raiz);
                    }
                }
            }
        }
        if(nodo->filhoDireita != nullptr && this->contem(nodo->filhoDireita->chave) == true){
            Nodo<T> *filhoD = nodo->filhoDireita;
            int fatorB_dir = get_fatorB(filhoD);
            if(fatorB_dir > 1){ 
                int dirFilhoE = get_fatorB(filhoD->filhoEsquerda);
                //Testa o nodo filhoEsquerda:
                if(dirFilhoE >= 0){             
                    filhoD = rot_dir(filhoD);
                }
                else if(dirFilhoE < 0 && filhoD->filhoEsquerda->filhoDireita != nullptr){
                    int filhoEsqDir = get_fatorB(filhoD->filhoEsquerda->filhoDireita);
                    if(filhoEsqDir <= 0){
                        filhoD->filhoEsquerda = rot_esq_dir(filhoD);
                        //nodo = x(nodo);
                    }    
                }

            }else if(fatorB_dir < -1){
                int dirFilhoD = get_fatorB(filhoD->filhoDireita);
                //Testa o nodo filhoDireita:
                if(dirFilhoD <= 0){            
                    filhoD = rot_esq(filhoD);
                }
                else if(dirFilhoD > 0 && filhoD->filhoDireita->filhoEsquerda != nullptr){
                    int filhoDirEsq = get_fatorB(this->raiz->filhoDireita->filhoEsquerda);
                    if(filhoDirEsq >= 0){
                        //sem inserção rotação direita-esquerda ;)
                    }
                }
            }
        }
        if(nodo->filhoEsquerda != nullptr && this->contem(nodo->filhoEsquerda->chave) == true){
            Nodo<T> *filhoE = nodo->filhoEsquerda;
            int fatorB_esq = get_fatorB(filhoE);
            if(fatorB_esq > 1){ 
                int esqFilhoE = get_fatorB(filhoE->filhoEsquerda);
                //Testa o nodo filhoEsquerda:
                if(esqFilhoE >= 0){             
                    filhoE = rot_dir(filhoE);
                }
                else if(esqFilhoE < 0 && filhoE->filhoEsquerda->filhoDireita != nullptr){ 
                    int _filhoEsqDir = get_fatorB(filhoE->filhoEsquerda->filhoDireita); //b do 3
                    if(_filhoEsqDir <= 0){
                        filhoE->filhoEsquerda = rot_esq_dir(filhoE);
                        nodo = x(nodo);
                    }    
                }

            }else if(fatorB_esq < -1){
                int esqFilhoD = get_fatorB(filhoE->filhoDireita);
                //Testa o nodo filhoDireita:
                if(esqFilhoD <= 0){            
                    filhoE = rot_esq(filhoE);
                }
            }
        }    
    }

    int get_fatorB(Nodo<T> *nodo)
    {
        int alt_esquerda = -1;
        int alt_direita = -1;
        if(nodo->filhoEsquerda != nullptr){
            alt_esquerda = nodo->filhoEsquerda->altura;
        }
        if(nodo->filhoDireita != nullptr){
            alt_direita = nodo->filhoDireita->altura;
        }
        return (alt_esquerda - alt_direita);
    }

    int atualizar_altura(Nodo<T>* nodo)
    {
        int alt_esquerda = -1;
        int alt_direita = -1;
        if(nodo->filhoEsquerda != nullptr){
            alt_esquerda = nodo->filhoEsquerda->altura;
        }
        if(nodo->filhoDireita != nullptr){
            alt_direita = nodo->filhoDireita->altura;
        }
        int max_altura = std::max(alt_esquerda, alt_direita);
        return (max_altura + 1);
    }

    Nodo<T> *get_pai(Nodo<T> *filho)
    {
        if(filho == this->raiz){
            return nullptr;
        }

        Nodo<T> *pai = this->raiz;
        while (pai != nullptr && pai->filhoDireita != filho && pai->filhoEsquerda != filho){
            if (filho->chave >= pai->chave){
                pai = pai->filhoDireita;
            }
            else{
                pai = pai->filhoEsquerda;
            }
        }
        return pai;
    }

    Nodo<T> *chave_minima(Nodo<T>* nodo)
    {
        Nodo<T>* minimo = nodo;
        while(minimo != nullptr && minimo->filhoEsquerda != nullptr){
            minimo = minimo->filhoEsquerda;
        }
        return minimo;
    }

    void remover_recursiva(Nodo<T> *nodo, T novachave)
    {
        if(nodo->chave == novachave){
            //algoritmo de busca
            if(nodo->filhoDireita == nullptr && nodo->filhoEsquerda == nullptr){ //caso 1
                Nodo<T> *pai = get_pai(nodo);
                delete nodo;
                if(pai == nullptr){
                    this->raiz = nullptr;
                }
                else if(novachave >= pai->chave){ 
                    pai->filhoDireita = nullptr;
                }
                else{ 
                    pai->filhoEsquerda = nullptr;
                }
                return;

            }else if (nodo->filhoDireita == nullptr){
                nodo->chave = nodo->filhoEsquerda->chave;
                remover_recursiva(nodo->filhoEsquerda, nodo->filhoEsquerda->chave);
            }
            else if (nodo->filhoDireita != nullptr && nodo->filhoDireita->filhoEsquerda != nullptr){
                Nodo<T> *minimo = chave_minima(nodo->filhoDireita);
                nodo->chave = minimo->chave;
                remover_recursiva(minimo, minimo->chave);
            }
            else if (nodo->filhoDireita != nullptr && nodo->filhoDireita->filhoEsquerda == nullptr && nodo->filhoDireita->filhoDireita != nullptr){
                Nodo<T> *_minimo = chave_minima(nodo->filhoDireita);
                nodo->chave = _minimo->chave;
                _minimo->chave = _minimo->filhoDireita->chave;
                remover_recursiva(_minimo->filhoDireita, _minimo->filhoDireita->chave);
                nodo->filhoDireita->altura = atualizar_altura(nodo->filhoDireita);
            }
            else if (nodo->filhoDireita != nullptr && nodo->filhoDireita->filhoEsquerda == nullptr && nodo->filhoDireita->filhoDireita == nullptr){
                Nodo<T> *minimo = chave_minima(nodo->filhoDireita);
                nodo->chave = minimo->chave;
                remover_recursiva(minimo, minimo->chave);
            }
        }else{
            if(novachave > nodo->chave){
                remover_recursiva(nodo->filhoDireita, novachave);
            }
            else if(novachave < nodo->chave){
                remover_recursiva(nodo->filhoEsquerda, novachave);
            }
        }   
        nodo->altura = atualizar_altura(nodo);
        verifica(nodo);
    }

    void inserir_recursiva(Nodo<T>* nodo, T novachave)
    {
        if(novachave >= nodo->chave){
            if(nodo->filhoDireita == nullptr){
                nodo->filhoDireita = new Nodo<T>{novachave};//{} por ser uma struct
            }
            else{
                inserir_recursiva(nodo->filhoDireita, novachave);
            }
        }else{
            if(nodo->filhoEsquerda == nullptr){
                nodo->filhoEsquerda = new Nodo<T>{novachave};//{} por ser uma struct
            }
            else{
                inserir_recursiva(nodo->filhoEsquerda, novachave);
            }
        }
        nodo->altura = atualizar_altura(nodo);
        verifica(nodo);
    }
    
    void rec_posOrdem(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *listaF) const
    {
        if (nodo != nullptr){
            rec_posOrdem(nodo->filhoEsquerda, listaF);
            rec_posOrdem(nodo->filhoDireita, listaF);
            listaF->inserirNoFim(nodo->chave);    
        }
    }

    void rec_preOrdem(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *listaB) const
    {
        if (nodo != nullptr){
            listaB->inserirNoFim(nodo->chave);
            rec_preOrdem(nodo->filhoEsquerda, listaB);
            rec_preOrdem(nodo->filhoDireita, listaB);
        }
    }

    void rec_emOrdem(Nodo<T> *nodo, ListaEncadeadaAbstrata<T> *listaD) const
    {
        if(nodo != nullptr){    
            rec_emOrdem(nodo->filhoEsquerda, listaD);
            listaD->inserirNoFim(nodo->chave);
            rec_emOrdem(nodo->filhoDireita, listaD);      
        }
    }

    int qtd_recursiva(Nodo<T> *nodo) const
    {
        if (nodo == nullptr){
            return 0;
        }
        else{
            return 1 + qtd_recursiva(nodo->filhoDireita) + qtd_recursiva(nodo->filhoEsquerda);
        }
    }

    void destrutor(Nodo<T> *nodo) {
        if (nodo != nullptr) {
            destrutor(nodo->filhoEsquerda);
            destrutor(nodo->filhoDireita);
            delete nodo;
        }
    }
};

#endif
