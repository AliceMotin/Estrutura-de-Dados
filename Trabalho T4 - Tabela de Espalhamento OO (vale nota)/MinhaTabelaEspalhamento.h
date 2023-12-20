#ifndef MINHA_TABELA_ESPALHAMENTO_H
#define MINHA_TABELA_ESPALHAMENTO_H

#include "MinhaListaEncadeada.h"
// MinhaListaEncadeada
#include "TabelaEspalhamentoAbstrata.h"
// TabelaEspalhamentoAbstrata
#include "excecoes.h"
// ExcecaoDadoInexistente
#include <cmath>

template<typename T, std::size_t capac>
class MinhaTabelaEspalhamento final:
    public TabelaEspalhamentoAbstrata<T, capac>
{
    public:
        virtual ~MinhaTabelaEspalhamento()
        {

        }
        
        virtual std::size_t capacidade() const
        {
            return this->tabela.size();
        }

        virtual void inserir(T dado)
        {
            std::size_t posicao = funcaoEspalhamento(dado);
            this->tabela[posicao].inserirNoFim(dado); 
            totalElementos++;
        }
        
        virtual void remover(T dado)
        {
            size_t posicao = funcaoEspalhamento(dado);
            this->tabela[posicao].remover(dado);
            totalElementos--;
        }

        virtual bool contem(T dado) const
        {
            size_t posicao = funcaoEspalhamento(dado);
            return this->tabela[posicao].contem(dado);
        }

        virtual std::size_t quantidade() const
        {
            return totalElementos;
        }
    
    protected:

        int totalElementos = 0;

        virtual std::size_t funcaoEspalhamento(T dado) const
        {
            if constexpr(!std::is_integral<T>::value){
                size_t result = codigoEspalhamento(dado);
                return (result % capac);
            }
            else{
                return (static_cast<size_t>(dado) % capac); 
            }
        }
    
    private:
        template<typename U>
        std::size_t codigoEspalhamento(U integral) const
        {
            return static_cast<size_t>(integral);
        }

        std::size_t codigoEspalhamento(std::string const& string) const
        {
            size_t hash = 0;
            size_t expoente = string.size() - 1;
            for (char c : string)
            {
                hash += static_cast<std::size_t>(c) * pow(31, expoente);
                expoente--;
            }
            return hash;
        }
    };

#endif
