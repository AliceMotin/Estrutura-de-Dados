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
            //int tmp = 0;
            //while(!this->tabela.empty())
            //{
              //  tmp++;
            //}
            //return tmp;
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
        /**
         * @brief Calcula a representação numérica de um tipo integral.
         * 
         * @tparam U O tipo integral.
         * @param integral Um valor integral.
         * @return Um inteiro calculado através de static_cast<std::size_t>(integral)
         */
        template<typename U>
        std::size_t codigoEspalhamento(U integral) const
        {
            return static_cast<size_t>(integral);
            //return 0;//Implemente aqui. Dica use std::is_integral_v<U> para garantir que U é um tipo integral
        }
        
    
        /**
         * @brief Calcula a representação numérica de um string.
         * 
         * @param s um string.
         * @return Um inteiro calculado conforme s[0]*31^(n-1) + s[1]*31^(n-2) + ... + s[n-1].
         */
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
