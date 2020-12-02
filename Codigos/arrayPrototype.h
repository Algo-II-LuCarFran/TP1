#ifndef _ARRAYPROTOTYPE_H_
#define _ARRAYPROTOTYPE_H_

template<class T>
class Array
{
	public:
		Array(); //Constructor base
		Array( const Array<T> & ); //Creador-Copiador
		Array(size_t); //Creador mediante tamaño del array
		~Array( ); //Destructor
		void ArrayRedim(size_t); //Redimensionador de arrays.
		size_t getSize( )const; //Método: determina el tamaño del array
		Array<T> getSubArray(const size_t n1,const size_t n2); //Obtiene un subarreglo que consta de los mismos datos que el arreglo original entre
															  // las posiciones n1 y n2. Ejemplo: si n1=1 y n2=4, devuelve un subarray de 4 elementos:
															 // los del arreglo original limitados por n1-1 (cero) y n2-1 (tres).
															// Si n2 es mayor al tamaño del subarreglo original, se genera un subarreglo
															// delimitado por n1 y el final del arreglo original.
		Array<T> &operator=( const Array<T> & ); //Operador asignación para una array: A=B, donde A y B son arrays. Recibe como parámetro un array por referencia constante, para no modificar lo que tiene dentro
		bool operator==( const Array<T> & ) ; //Operador lógico para comprobar si son iguales 2 arrays. Recibe como parámetri un array por referencia constante, para no modificar lo que tiene dentro
		T & operator[](size_t); //Operador indexación: Retorna un elemento del vector (se puede cambiar, pues se retorna por referencia)
		template <class TT>
		friend std::ostream &operator<<(std::ostream&, Array <TT> &); //Operador de impresion de salida
		bool empty(); // Verifica si un arreglo esta vacio.


	private:
		size_t rsize; //Atributo que indica el tamaño del array 
		size_t vsize;
		T *ptr; //Atributo que indica la dirección donde inicia el puntero
};


//--------------------------CLASE BLOCK----------------------------------------------------------------------------------------
class block
{   
	private:
	hdr header;
	bdy body;

	public:
	block(); //Constructor base
	block(const string,const  size_t, istream*); //Constructor en base al hash del bloque previo, al nivel de  
												//dificultad y un flujo de entrada por el que se reciben las 
											   // transacciones.
	block(const string ); //Constructor en base a una string.
	~block( ); //Destructor
	block & operator=(const block &);
	void setHeader(const string&,const size_t);
	string setBody(istream *iss);
	void setHeader(hdr header);
	void setBody(bdy body);
	void setBlockFromFile(istream *iss);
	hdr getHeader();
	bdy getBody();
	string getBlockAsString();
	void addTxn(txn aux_txn);
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, block& block) 
	{
		block.show(oss);
		return oss;
	}
};

#endif //_ARRAYPROTOTYPE_H_