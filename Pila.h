#ifndef LA_PLANTILLA_DE_PILA
#define LA_PLANTILLA_DE_PILA

template < class T >
class Pila {
   private:
     class Celda {
        public:
           T elemento;
           Celda * resto;
           Celda(T elemento){
              this->elemento = elemento;
              resto = 0;
           }
           Celda( Celda & otra){
              resto = 0;
              *this = otra;
           }
           ~Celda(){
              if(resto){
                delete resto;
              }
           }
           
           // Requiere: Todos los constructores deben poner resto = 0 antes de usar este método
           // Efectua: asigna una copia de otra celda y las siguientes a la celda que se aplica
           // Modifica: elemento y resto 
           Celda & operator=(Celda & otra){
              if(resto){
                 delete resto;
              }
              this->elemento = otra.elemento;
              this->resto = 0;
              if(otra.resto){
                resto = new Celda( *(otra.resto) );
              }
              return *this;
           }

     };

      Celda * tope;

   public:
      Pila(){
         tope = 0;
      }
      Pila(const Pila& otra){
         tope = 0;
         *this = otra;
      }
      ~Pila(){
         if(tope){
            delete tope;
         }
      }
      Pila & operator=(const Pila& otra){
         if(tope){
            delete tope;
         }
         tope = 0;
         if(otra.tope){
            tope = new Celda( *(otra.tope) );
         }         
         return *this;
      }
      T& top(){
         return tope->elemento;
      }
      Pila& pop(){
          if(tope){
             Celda * victima = tope;
             tope = tope->resto;
             victima->resto=0;
             delete victima;
          }
          return *this;
      }
      Pila& push( T elemento ){
          Celda * nueva = new Celda(elemento);
          nueva->resto = tope;
          tope = nueva;
          return *this;
      }
      int isEmpty(){
         return !tope;
      }
};

#endif
