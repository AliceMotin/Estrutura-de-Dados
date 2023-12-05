#ifndef DEC0006_MINHA_LISTA_ENCADEADA_H
#define DEC0006_MINHA_LISTA_ENCADEADA_H

#include <cstddef>
// std::size_t

#include "Elemento.h"
// Elemento
#include "ListaEncadeadaAbstrata.h"
#include "excecoes.h"
// ExcecaoDadoInexistente
// ExcecaoListaEncadeadaVazia
// ExcecaoNaoImplementado
// ExcecaoPosicaoInvalida

/**
 * @brief Uma lista encadeada de dados.
 *
 * @tparam T O tipo dos dados armazenados na lista.
 */
template <typename T>
class MinhaListaEncadeada : public ListaEncadeadaAbstrata<T>
{
    virtual ~MinhaListaEncadeada()
    {
        while(vazia()!= true){
            removerDoInicio();
        }
    }

    virtual std::size_t tamanho() const
    {
        return this->_tamanho;
    }

    virtual bool vazia() const
    {
        return (this->_tamanho == 0);
    }

    virtual std::size_t posicao(T dado) const
    { 
        if (this->vazia()){
           throw ExcecaoListaEncadeadaVazia();
        }
        else{ 
            size_t i = 0;
            Elemento<T> *pos = this->_primeiro;
            while (pos != nullptr){
               if (pos->dado == dado)
                {
                    return (i);
                }
            pos = pos->proximo;
            i++;
            }
        }

        throw ExcecaoDadoInexistente();
        return 0;
    }

    virtual bool contem(T dado) const
    {  
        size_t i=0;
        Elemento<T> *cont = this->_primeiro;
        while (cont != nullptr){ 
            if (cont->dado == dado){
                return true;
            }
            cont = cont->proximo;
            i++;
        }
        return false;
    }

    virtual void inserirNoInicio(T dado)
    {
        Elemento<T> *novoElemento = new Elemento<T>(dado, this->_primeiro);
        this->_primeiro = novoElemento;
        this->_tamanho++;
    }

    virtual void inserir(std::size_t posicao, T dado)
    {
        if (posicao < 0 || posicao > this->_tamanho){
            throw ExcecaoPosicaoInvalida();
        }
        if (posicao == 0){
            inserirNoInicio(dado);
        }
        else{
            Elemento<T>* novo = new Elemento<T>(dado);
            Elemento<T>* anterior = this->_primeiro;
            for (std::size_t i = 1; i < posicao; i++){
                anterior = anterior->proximo;
            }
            novo->proximo = anterior->proximo;
            anterior->proximo = novo;
            this->_tamanho++;    
        }
    }

    virtual void inserirNoFim(T dado)
    {
        if (this->vazia()){
            inserirNoInicio(dado);
        }
        else{
            Elemento<T> *newElement = new Elemento<T>(dado, nullptr);
            Elemento<T> *atual = this->_primeiro;
            while (atual->proximo != nullptr)
            {
                atual = atual->proximo;
            }
            atual->proximo = newElement;
            this->_tamanho++; 
        }
    }

    virtual T removerDoInicio()
    {
        if (this->vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }
        else{
            T tpm = this->_primeiro->dado;
            Elemento<T> *inicio = this->_primeiro;
            this->_primeiro = this->_primeiro->proximo;
            delete inicio;
            this->_tamanho--;
            return tpm;
        }
    }

    virtual T removerDe(std::size_t posicao)
    {
        if (posicao < 0 || posicao >= this->_tamanho){
            throw ExcecaoPosicaoInvalida(); 
        }
        if (posicao == 0){
            return this->removerDoInicio();
        }
        else{
            Elemento<T>* kMenosUm = this->_primeiro;
            for (std::size_t i = 1; i < posicao; i++){
                kMenosUm = kMenosUm->proximo;
            }
            Elemento<T> *k = kMenosUm->proximo;
            T x = k->dado;
            kMenosUm->proximo = k->proximo;
            delete k;
            this->_tamanho--;
            return x;
        }
    }
    
    virtual T removerDoFim()
    {
         if (this->vazia()){
            throw ExcecaoListaEncadeadaVazia();
        }
        if (this->_primeiro->proximo == nullptr){
            return this->removerDoInicio();    
        }
        else{
            Elemento<T> *antesUltimo = this->_primeiro;
            for (std::size_t i = 2; i < this->_tamanho; i++){
                antesUltimo = antesUltimo->proximo;
            }

            Elemento<T> *ultimo = antesUltimo->proximo;
            T u = ultimo->dado;
            antesUltimo->proximo = nullptr;
            delete ultimo;
            this->_tamanho--;
            return u;
        }
    }

    virtual void remover(T dado)
    {
        if (this->vazia()){
           throw ExcecaoListaEncadeadaVazia();
        }
        if (this->_primeiro->dado == dado){
            removerDoInicio();
        }
        else{
            Elemento<T> *itemAnterior = nullptr;
            Elemento<T> *item = this->_primeiro;
            while (item != nullptr && item->dado != dado){
                itemAnterior = item;
                item = item->proximo;
            }
            if(item == nullptr){
                throw ExcecaoDadoInexistente();
            }
            //T d = item->dado;
            itemAnterior->proximo = item->proximo;
            delete item;
            this->_tamanho--;
        }
    }
};

#endif