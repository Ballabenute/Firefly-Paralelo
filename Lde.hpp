#ifndef LDE_HPP
#define LDE_HPP

#include "node.hpp"
#include <cstdlib>
#include <iostream>

//classe template de uma Lde
template <class Type_Name> class Lde
{
   public:
        Lde()
        {
            this->First = NULL;
            this->Amount = 0;
        }

        int getAmount()
        {
            return this->Amount;
        }

      //função de inserção em uma lde
      template <class Type> bool Insert(Type Value)
      {
         Node<Type> *New;
         New = new Node<Type>;
         New->setContent(Value);

         if(Amount == 0){
            First = New;
            Amount++;
            return true;
         }
         Node<Type> *Now = this->First;
         Node<Type> *Back = NULL;
         while(Now != NULL && Now->template getContent<Type>() > Value){
            Back = Now;
            Now = Now->getNext();
         }
         if(Back == NULL){
            New->setNext(Now);
            First = New;
            Amount++;
            return true;
         }else{
             if(Now != NULL){
                New->setNext(Now);
                Back->setNext(New);
                Amount++;
                return true;
             }
             else{
                Back->setNext(New);
                Amount++;
                return true;
             }
          }
         return false;
      }

    //retira o 1 conteudo de uma lde
      template <class Type> Type getFirst(){
        Node<Type> *Now = this->First;
        this->First = Now->getNext();
        return Now->template getContent<Type>();
      }
      
      //função de buca de uma lde
      template <class Type> Type Search(int Key)
      {
         Node<Type> *Now = this->First;
         while(Now != NULL && Now->template getContent<Type>() != Key){
            Now = Now->getNext();
         }
         if (Now == NULL)
            Type Temp;
         return Now->template getContent<Type>();
      }

      template <class Type> void Print()
      {
         Node<Type> *Now = this->First;
         while(Now != NULL){
            std::cout<<Now->template getContent<Type>()<<std::endl;
            Now = Now->getNext();
         }
      }

//função de deletar em uma lde
template <class Type> bool Delete(int Key)
      {
         if(Amount == 0)
            return false;

            Node<Type> *Now = this->First;
            Node<Type> *Back = NULL;
            while(Now != NULL && Now->template getContent<Type>() != Key){
               Back = Now;
               Now = Now->getNext();
            }
            if(Now == NULL)
               return false;
            else if(Back == NULL){
               this->First = Now->getNext();
               delete Now;
            }else{
               Back->setNext(Now->getNext());
               delete Now;
            }

         return true;
      }

   private:
      Node<Type_Name> *First;
      int Amount;

};
#endif // LDE_HPP
