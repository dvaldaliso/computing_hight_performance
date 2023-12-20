#include <stdio.h>
#include <iostream>
#include "tbb/parallel_pipeline.h" 
using namespace tbb;
using namespace std;

#define BUFFER_SIZE 100

class MyBuffer {
  private:
    static const size_t buffer_size = 10000;
    char* my_end;
    // storage[0] holds the last character of the prec. buffer
    char storage[1+buffer_size];
  public:
    // Pointer to first character in the buffer
    char* begin() {return storage+1;}
    const char* begin() const {return storage+1;}
    // Pointer to one past last character in the buffer
    char* end() const {return my_end;}
    // Set end of buffer.
    void set_end( char* new_ptr ) {my_end=new_ptr;}
    // Number of bytes a buffer can hold
    size_t max_size() const {return buffer_size;}
    // Number of bytes in buffer.
    size_t size() const {return my_end-begin();}
};



int main( )  {

  FILE* input_file;
  FILE* output_file;
  char fichero_entrada[100];
  char fichero_salida[100];

  size_t next_buffer = 0;
  char last_char_of_previous_buffer = ' ';
  static const size_t n_buffer = 4;
  MyBuffer buffer[n_buffer];

  cout << "Introduce el fichero de entrada: " ;
  cin >> fichero_entrada;
  if( ( input_file = fopen(fichero_entrada,"r") ) == NULL ) {
    cout << "Fichero no existente." << endl;
    return 0;
  }
  cout << "Introduce el fichero de salida: " ;
  cin >> fichero_salida;
  output_file = fopen(fichero_salida,"w");


  auto f1 = [&]( flow_control& fc ) -> MyBuffer* {
    MyBuffer& b = buffer[next_buffer];
    next_buffer = (next_buffer+1) % n_buffer;
    size_t n = fread( b.begin(), 1, b.max_size(), input_file );
    if( !n ) { // end of file
      fc.stop();
      return NULL;
    } else {
      b.begin()[-1] = last_char_of_previous_buffer;
      last_char_of_previous_buffer = b.begin()[n-1];
      b.set_end( b.begin()+n );
      return &b;
    }
  };

  auto f2 = [=]( MyBuffer* b ) -> MyBuffer* {
    bool prev_char_is_space = b->begin()[-1]==' ';
    for( char* s=b->begin(); s!=b->end(); ++s ) {
    if( prev_char_is_space && islower(*s) )
      *s = toupper(*s);
      prev_char_is_space = isspace(*s);
    }
    return b;
  };

  auto f3 = [=]( MyBuffer* b ) -> void* {
    fwrite( b->begin(), 1, b->size(), output_file );
    return NULL;
  };

  parallel_pipeline( /*max_number_of_live_token=*/ 2,
    make_filter<void,MyBuffer*>( filter_mode::serial_in_order, f1 ) &
    make_filter<MyBuffer*,MyBuffer*>( filter_mode::parallel, f2 ) &
    make_filter<MyBuffer*,void>( filter_mode::serial_in_order, f3 )
  );



  /*************************/
  /* Resolucion secuencial */
  /* char buffer[BUFFER_SIZE];
  size_t n;
  bool primero = false;
  do {
    n = fread( buffer, 1, BUFFER_SIZE, input_file );
    if( primero ) buffer[0] = toupper(buffer[0]);
    primero = false;
    for( int i=1; i<n; i++ ) {
      char *c = &(buffer[i-1]);
      if( *c == ' ' || *c == '\r' || *c == '\n' ) {
        *c = toupper(*(++c));
      }
    }
    fwrite( buffer, 1, n, output_file );
    if( buffer[n-1] == ' ' ) primero = true;
  } while ( n ); */
  /*************************/
  
  fclose(input_file);
  fclose(output_file);
}


