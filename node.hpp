#ifndef NODE_H
#define NODE_H
#include <cstdlib>

template <class Type_Name> class Node
{
   public:
      Node()
      {
         this->Next = NULL;
      }
      void setNext(Node* Next)
      {
         this->Next = Next;
      }
      template <class Type> void setContent(Type Content)
      {
         this->Content = Content;
      }
      template <class Type> Type getContent()
      {
         return Content;
      } 
      Node* getNext()
      {
         return Next;
      }
      template <class Type> bool operator<(Type a)
      {
         if(Content<a)
            return true;
         else return false;
      }
   private:
      Node* Next;
      Type_Name Content;
};
#endif 
