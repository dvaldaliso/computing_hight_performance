#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <list>
#include "tbb/parallel_for_each.h"

using namespace std;
using namespace tbb;
//g++ -o actividad6 actividad6.cpp  -ltbb
void Foo( double& f ) { 
  f = f*f; 
}


struct s_item {
  double data;
  struct s_item *next;
};

typedef struct s_item Item;

class ApplyFoo {
  public:
  void operator()( Item& item ) const {
    Foo(item.data);
  }
};

/*void SerialApplyFooToList( Item *root ) { 
  for( Item* ptr=root; ptr!=NULL; ptr=ptr->next )
    Foo(ptr->data);
}*/

void ParallelApplyFooToList( list<Item>& lista ) {
  parallel_for_each( lista.begin(), lista.end(), ApplyFoo() );
}

int main( )  {

  long n = 10;
  Item *root = NULL;
  root = new( Item );
  root->data = 0.0;
  Item *p; 
  size_t i;
  list<Item> lista;
  
  for( i=1, p = root; i<n; i++, p = p->next ) {
    lista.push_back(*p);
    p->next = new( Item );
    p->next->data = (double) i;
    p->next->next = NULL;
  }

  ParallelApplyFooToList( lista );
  for (auto &i: lista )
  {
    cout << "Dato = " << i.data << endl;
  }
  
  cout << "Valores = " << endl;
  for( p = root; p!=NULL; p=p->next ) {
    cout << "Dato = " << p->data << endl;
  }

}

