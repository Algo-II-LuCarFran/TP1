#ifndef _BLOCK_H_
#define _BLOCK_H_
#include <iostream>
#include <string.h>
#include <cstring>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <bitset>
#include <ctype.h>
#include <iomanip>

#include "math.h"
#include "tools.h"
#include "Array.h"
#include "sha256.h"
#define NULL_HASH "0000000000000000000000000000000000000000000000000000000000000000"

// o Se usaran strings para representar los hash
//
// o Jerarquía de clases: Bloque > Header/Body>Txn > Input/Output > Outpoint (estructura que pertenece a Input).

//--------------------------ESTRUCTURA OUTPOINT----------------------------------------------------------------------------------------
struct outpnt
{
	string tx_id; //Es un hash de la transaccion de donde este input toma fondos
	size_t idx; //Valor entero no negativo que representa un indice sobre la secuencia de outputs de la transaccion con hash tx id
};
//--------------------------CLASE INPUT----------------------------------------------------------------------------------------
class inpt
{   
	outpnt outpoint;
	string addr; //La direccion de origen de los fondos (que debe coincidir con la direccion del output referenciado)
	public:
	inpt(); //Creador base
	inpt(string&); //Creador mediante una string
	~inpt( ); //Destructor
	inpt & operator=(const inpt &);
	//Si hay getters deberian haber setters. Si no se usan, eliminarlos.
	string getAddr();
	outpnt getOutPoint();
	string getInputAsString();
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, inpt& in) 
	{
		in.show(oss);
		return oss;
	}
};
inpt::inpt(){}//Creador base

inpt::~inpt(){} //Destructor base

inpt::inpt(string & str) //Creador mediante una string
{
	istringstream ss(str);
	string str_tx_id,str_id,str_addr;
	
	getline(ss, str_tx_id, ' '); // Se recorren los campos. Si el formato es erroneo, se detecta como una cadena vacia.
	getline(ss, str_id, ' ');
	getline(ss, str_addr, '\n');

	if((isHash(str_tx_id)==true) && (isNumber<size_t>(str_id)==1) && (isHash(str_addr)==true))
	{
		this->outpoint.tx_id=str_tx_id;
		this->outpoint.idx=stoi(str_id);
		this->addr=str_addr;
	}
	else
	{
		this->addr=ERROR; // Si hay un error pone addr en ERROR, para avisar a un nivel mas alto
	}
}

inpt & inpt::operator=(const inpt & right)
{
	if (&right != this)
	{
		outpoint = right.outpoint;
		addr = right.addr;
		return *this;
	}
	return *this;
}

outpnt inpt::getOutPoint(){return outpoint;}

string inpt::getAddr(){return addr;}

string inpt::getInputAsString()
{
	stringstream ss; 
	string aux;

	ss<<(this->getOutPoint().idx);	 //Pasaje de size_t   
	ss>>aux; 						// a string
	
	string result;
	result.append((this->getOutPoint()).tx_id);
	result.append(" ");
	result.append(aux);
	result.append(" ");
	result.append((this->getAddr()));

	return result;
}

void inpt::show(ostream& oss)
{
	if(outpoint.tx_id == "" || addr == "")
	{
		return ;
	}
	oss << outpoint.tx_id << " " << outpoint.idx << " " << addr;
}
//--------------------------CLASE OUTPUT----------------------------------------------------------------------------------------
class outpt
{
	double value; //La  cantidad de Algocoins a transferir en este output
	string addr; //La direccion de origen de los fondos (que debe coincidir con la direccion del output referenciado)

	public:

	outpt(); //Creador base
	outpt(string&); //Creador mediante una string
	~outpt( ); //Destructor
	outpt & operator=(const outpt &);
	double getValue();
	string getAddr();
	string getOutputAsString();
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, outpt& out) 
	{
		out.show(oss);
		return oss;
	}
};

outpt::outpt() //Creador base
{    
}

outpt::~outpt() //Destructor base
{    
}

outpt & outpt::operator=(const outpt & right)
{
	if(&right != this)
	{
		value = right.value;
		addr = right.addr;
		return *this;
	}
	return *this;
}

outpt::outpt(string & str) //Creador mediante una string
{
	istringstream ss(str);
	string str_value,str_addr;

	getline(ss, str_value, ' '); // Se recorren los campos. Si el formato es erroneo, se detecta como una cadena vacia.
	getline(ss, str_addr, '\n');

	if((isNumber<double>(str_value)==1) && (isHash(str_addr)==true))
	{
		this->value=stod(str_value);
		this->addr=str_addr;
	}
	else
	{
		this->addr=ERROR;
	}
}

string outpt::getAddr(){return addr;}

double outpt::getValue(){return value;}

string outpt::getOutputAsString()
{
	string aux;
	string str_exact_precision;
	string result;
	ostringstream str_os;

	size_t i;
	aux=to_string(this->value);	
	for(i=aux.length()-1; aux[i] -'0'==0 ;i--); //Indica la posicion con decimales exactos (sin ceros de mas)
	str_exact_precision=aux.substr(0,i+1); //Se copia la sub cadena desdeada

	result.append(str_exact_precision);
	result.append(" ");
	result.append((this->getAddr()));
	return result;
}

void outpt::show(ostream& oss)
{
	string aux;
	string str_exact_precision;
	aux=to_string(value);
	size_t i;
	for(i=aux.length()-1; aux[i] -'0'==0 ;i--); //Indica la posicion con decimales exactos (sin ceros de mas)
	str_exact_precision=aux.substr(0,i+1); //Se copia la sub cadena desdeada

	if(addr == "")
	{
		return ;
	}
	oss << str_exact_precision << " " << addr;
}
//--------------------------CLASE TXN----------------------------------------------------------------------------------------


class txn
{   
	private:
	size_t n_tx_in; //Indica la cantidad total de inputs en la transaccion
	size_t n_tx_out; //Indica la cantidad total de outputs en la transaccion
	Array <inpt> tx_in; //Datos de entrada para las transacciones
	Array <outpt> tx_out; //Datos de salida para las transacciones

	public:
	txn(); //Creador base
	txn(Array<string>&); //Creador en base a un array de cadenas. El array debe contener todos los campos necesarios
						// para crear la transaccion.
	~txn( ); //Destructor
	txn &operator=( const txn & );

	void setNTxIn(const size_t) ;
	void setNTxOut(const size_t);
	string setTxIn(const size_t n, istream *iss); // Seteador que valida los datos y devuelve un booleano para el error
	bool setTxIn(const size_t, Array<string>&);
	string setTxOut(const size_t n, istream *iss);
	bool setTxOut(const size_t, Array<string>&);
	string setTxOutFile(const size_t n, istream *iss);

	size_t getNTxIn();
	size_t getNTxOut();
	Array<inpt>& getInputs();
	Array<outpt>& getOutputs();

	string getTxnAsString();
	string validateTxn();
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, txn& tx) 
	{
		tx.show(oss);
		return oss;
	}
};


txn::txn()
{
	n_tx_in=0;
	n_tx_out=0;
	tx_in.ArrayRedim(0);
	tx_out.ArrayRedim(0);
}

txn::txn(Array<string>& txn_str_arr)
{
	size_t i;
	this->setNTxIn(stoi(txn_str_arr[0]));
	for(i=1;i<(this->getNTxIn())+1;i++)
	{
		inpt in(txn_str_arr[i]);
		tx_in[i] = in;
	}
	this->setNTxOut(stoi(txn_str_arr[i]));
	for( ;i<(this->getNTxOut())+1;i++)
	{
		outpt out(txn_str_arr[i]);
		tx_out[i] = out;
	}
}

txn::~txn()
{
}

txn & txn::operator=(const txn &right)
{
	if(&right != this)
	{
		n_tx_in = right.n_tx_in;
		n_tx_out = right.n_tx_out;
		tx_in = right.tx_in;
		tx_out = right.tx_out;
		return *this;
	}
	return *this;
}
void txn::setNTxIn(const  size_t n) 
{
	n_tx_in=n;
	if(tx_in.getSize() == 0)
	{
		tx_in.ArrayRedim(n);
	}
}


void txn::setNTxOut(const size_t n)
{
	n_tx_out=n;
	if(tx_out.getSize() == 0)
	{
		tx_out.ArrayRedim(n);
	}
}



string txn::setTxIn(const size_t n, istream *iss)  //Se modifica el retorno del setter por defecto (void) por
{												// necesidad. Verifica si el setteo pudo realizarse correctamente.
	string aux_s;
	for (size_t i = 0; i < n; i++)
	{
		getline(*iss, aux_s, '\n');
		if(isHash(aux_s)==true)
		{
			return aux_s;
		}
		inpt in(aux_s);
		if(isError(in.getAddr())==false)
			return "ERROR: addres invalida";
		tx_in[i] = in;
	}
	return "OK";
}

bool txn::setTxIn(const size_t n, Array<string>& tx_in_str_arr)
{
	//Se modifica el retorno del setter por defecto (void) por
	// necesidad. Verifica si el setteo pudo realizarse correctamente. 
	string aux_s;
	for (size_t i = 0; i < n; i++)
	{
		inpt in(tx_in_str_arr[i]);
		if(isError(in.getAddr())==false)
			return false;
		tx_in[i] = in;
	}
	return true;
}


// bool txn::setTxOut(const size_t n, istream *iss) //Se modifica el retorno del setter por defecto (void) por
// 												// necesidad. Verifica si el setteo pudo realizarse correctamente.
// {
// 	string aux_s;
// 	for (size_t i = 0; i < n; i++)
// 	{
// 		getline(*iss, aux_s, '\n');
// 		outpt out(aux_s);
// 		if(isError(out.getAddr())==false)
// 			return false;
// 		tx_out[i] = out;
// 	}
// 	return true;
// }

string txn::setTxOut(const size_t n, istream *iss) //Se modifica el retorno del setter por defecto (void) por
												// necesidad. Verifica si el setteo pudo realizarse correctamente.
{
	string aux_s;
	for (size_t i = 0; i < n; i++)
	{
		getline(*iss, aux_s, '\n');
		if(isHash(aux_s)==true)
		{
			return aux_s;
		}
		outpt out(aux_s);
		if(isError(out.getAddr())==false)
			return "ERROR: addres invalida";
		tx_out[i] = out;
	}
	return "OK";
}

// string txn::setTxOutFile(const size_t n, istream *iss) //Se modifica el retorno del setter por defecto (void) por
// 												// necesidad. Verifica si el setteo pudo realizarse correctamente.
// {
// 	string aux_s;
// 	for (size_t i = 0; i < n; i++)
// 	{
// 		if(iss.eof()!=1)
// 		{
// 			return "\n";
// 		}
// 		getline(*iss, aux_s, '\n');
// 		if (isHash(aux_s)==true)
// 		{
// 			return aux_s;
// 		}
		
// 		outpt out(aux_s);
// 		if(isError(out.getAddr())==false)
// 		{
// 			cerr << "ERROR: Carga invalida"<< endl;
// 			exit(1);
// 		}
// 		tx_out[i] = out;
// 	}
// 	return "\0";
// }

bool txn::setTxOut(const size_t n, Array<string>& tx_in_str_arr) //Se modifica el retorno del setter por defecto (void) por
												// necesidad. Verifica si el setteo pudo realizarse correctamente.
{
	for (size_t i = 0; i < n; i++)
	{
		outpt out(tx_in_str_arr[i]);
		if(isError(out.getAddr())==false)
			return false;
		tx_out[i] = out;
	}
	return true;
}

size_t txn::getNTxIn(){return n_tx_in;}

size_t txn::getNTxOut(){return n_tx_out;}

Array<inpt>& txn::getInputs(){return tx_in;}
Array<outpt>& txn::getOutputs(){return tx_out;}


string txn::getTxnAsString()
{
	
	string result, aux;
	aux = to_string(n_tx_in);
	if(((this->getNTxIn()==0)) && ((this->getNTxOut())==0))
		return result.append("0");
	result.append(aux);
	result.append("\n");
	for(size_t i = 0; i < n_tx_in; i++)
	{
		result.append(tx_in[i].getInputAsString());
		result.append("\n");
	}
	aux = to_string(n_tx_out);
	result.append(aux);
	result.append("\n");
	for(size_t i = 0; i < n_tx_out; i++)
	{
		result.append(tx_out[i].getOutputAsString());
		result.append("\n"); //Es necesario para separar las transacciones al enviarlas al flujo de salida
	}
	return result;
}

void txn::show(ostream& oss)
{
	if(n_tx_in == 0)
		return ;
	oss << n_tx_in << endl;
	for (size_t i = 0; i < tx_in.getSize(); i++)
	{
		oss << tx_in[i] << endl;
	}
	
	oss << n_tx_out << endl;
	for (size_t i = 0; i < tx_out.getSize(); i++)
	{
		oss << tx_out[i] << endl;
	}
}
//--------------------------CLASE BODY----------------------------------------------------------------------------------------

class bdy
{
	friend class block;
	size_t txn_count;
	Array <txn> txns;
	public:
	bdy();
	~bdy();
	bdy & operator=(const bdy &);
	bdy getBody();
	string getBodyAsString();
	size_t getTxnCount();
	Array<txn> getTxns();
	string getTxnAsString();
	void setTxns(Array <txn> txns);
	string setTxns(istream *iss);
	void setTxnCount(const size_t n);
	void txnsArrRedim(const size_t );
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, bdy& body) 
	{
		body.show(oss);
		return oss;
	}
};	
bdy::bdy()
{
}

bdy::~bdy(){}

bdy & bdy::operator=(const bdy & right)
{
	if(&right != this)
	{
		txn_count = right.txn_count;
		txns = right.txns;
		return *this;
	}
	return *this;
}

void bdy::setTxnCount(const size_t n)
{
	txn_count = n;
	if(this->txns.getSize() == 0)
	{
		txns.ArrayRedim(n);
	}
}

void bdy::setTxns(Array <txn> n)
{
	txns = n;
}

string bdy::setTxns(istream *iss)
{
	string str,error_string;
	size_t aux, i = 0;
	bool err=false;
	while(getline(*iss, str, '\n'))
	{
		if(isHash(str)==true || str == "")
		{
			return str;
		}
		if(i >=txns.getSize())
		{
			txns.ArrayRedim(txns.getSize()*2); // Dependiendo de cuantos datos haya que analizar se puede modificar
		}									  // la estrategia de crecimiento del arreglo.

		// Se verifica n_tx_in
		if(isNumber<size_t>(str)==0 || (str[0]) == '\0')
		{
			err=true;
			break;
		}
	

		aux = stoi(str);
		txns[i].setNTxIn(aux);
		// Se verifican las entradas

		if(txns[i].setTxIn(aux, iss)!="OK")
		{
			err=true;
			break;
		}
		

		// Se verifica n_tx_out
		getline(*iss, str, '\n');

		if(isNumber<size_t>(str)==0 || (str[0]) == '\0')
		{
			err=true;
			break;
		}
		
		aux = stoi(str);
		txns[i].setNTxOut(aux);

		// Se verifican las salidas
		str=txns[i].setTxOut(aux, iss);
		
		if(isHash(str)==true)
		{
			return str;
		}
		else if(str=="OK")
		{
			return str;
		}
		else 
		{
			err=true;
			break;
		}
		i++;
		
	}
	if(err==true)
	{
		error_string.append("Error en la transaccion ");
		error_string.append(to_string(i+1));
		error_string.append("\n");
		error_string.append("Carga de datos interrumpida");
		error_string.append("\n");
		error_string.append("Vuelva a cargar los datos del bloque");
		return error_string;
	}
	txn_count = i;
	if(str == "")
	{
		return str;
	}
	return "OK";
}

string bdy::getBodyAsString()
{
	string result, str,aux;
	str = to_string(txn_count);
	result.append(str);
	result.append("\n");

	if((txn_count==1) && (!txns[0].getTxnAsString().compare("0")))
		return "0\n";

	for (size_t i = 0; i < txn_count; i++)
	{
		result.append(txns[i].getTxnAsString());
	}
	
	return result;
}

size_t bdy::getTxnCount(){return txn_count;}
Array<txn> bdy::getTxns(){return txns;}

bdy bdy::getBody(){return *this;}

void bdy::txnsArrRedim(const size_t n ){txns.ArrayRedim(n);}


void bdy::show(ostream& oss)
{
	oss << txn_count << endl;
	for (size_t i = 0; i < txns.getSize(); i++)
	{
		oss << txns[i];
	}
}
//--------------------------CLASE HEADER----------------------------------------------------------------------------------------

class hdr
{
	friend class block;
	string prev_block;//El hash del bloque completo que antecede al bloque actual en la Algochain.
	string txns_hash;//El hash de todas las transacciones incluidas en el bloque.
	size_t bits;    // Valor entero positivo que indica la dificultad con la que fue minada este bloque.
	size_t nonce;  // Un valor entero no negativo que puede contener valores arbitrarios. El objetivo de este 
				  // campo es tener un espacio de prueba modificable para poder generar hashes sucesivos hasta 
				 // satisfacer la dificultad del minado.
	public:
	hdr();
	~hdr();
	hdr & operator=(const hdr &);
	bool setPrevBlock(const string&);
	void setTxnsHash(const string&);
	void setBits(const size_t n);
	void setNonce(const string prev_block,const  string txns ,const  size_t bits);
	void setNonce(const  size_t nonce);
	string getPrevBlock();
	string getTxnHash();
	size_t getBits();
	size_t getNonce();
	string getHeaderAsString();
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, hdr& header) 
	{
		header.show(oss);
		return oss;
	}
};

hdr::hdr()
{
	prev_block = "\0";
	txns_hash = "\0";
	bits = 0; 	//Se podría hacer que los bits y el nonce fueran ints para detectar errores haciendo que estos valgan -1 (por ej)
	nonce = 0;
}

hdr::~hdr(){}

hdr & hdr::operator=(const hdr & right)
{
	if(&right != this)
	{
		prev_block = right.prev_block;
		txns_hash = right.txns_hash;
		bits = right.bits;
		nonce = right.nonce;
		return *this;
	}
	return *this;
}

bool hdr::setPrevBlock(const string & str)//Se modifica el retorno del setter por defecto (void) por
										// necesidad. Verifica si el setteo pudo realizarse correctamente.
{
	if(isHash(str) == false)
		return false;
	else
	{
		prev_block = str;
		return true;
	}
}


void hdr::setTxnsHash(const string & str)
{
	if(isHash(str)==true)
	{
		txns_hash = str;
	}
	else
		txns_hash = sha256(sha256(str));
}


void hdr::setBits(const size_t n){bits = n;}

void hdr::setNonce(const size_t n){nonce = n;}


string hdr::getPrevBlock(){return prev_block;}


string hdr::getTxnHash(){return txns_hash;}


size_t hdr::getBits(){return bits;}


size_t hdr::getNonce(){return nonce;}


string hdr::getHeaderAsString()
{
	string str;
	string bit_string = to_string(bits); //convierto el bits a string y lo agrego a la string
	string nonce_string; //para guardar cuando transforme en string del nonce

	str.append(prev_block);//pongo primero en la string el prev block
	str.append("\n");//PREGUNTAR si no viene con el barra n, creo que no pero si no ya esta
	str.append(txns_hash);//agrego el txns, ver comentario de la linea 25
	str.append("\n");
	str.append(bit_string);
	str.append("\n");
	nonce_string = to_string(nonce); //convierto el nonce a string
	str.append(nonce_string); 
	return str;

}
void hdr::setNonce(const string prev_block,const  string txns ,const  size_t bits) // Setea el header con el nonce que verifica que el hash del header cumpla con los primeros d bits en cero
{
	size_t out = 0; //inicializo d_auz que contara el nivel de difucultar y out que es un flag para el for
	size_t nonce_aux = 0; //inicializo el nonce, para mi hay que hacerlo double porque se puede hacer muy grande pero hay que cambiar struct

	string header_str; //defino un header_aux auxiliar para hacer la string antes de hashearla
	string hash_header; // para guardar el hash del header_aux
	
	int j, i, aux;

	int cant_char = bits/4;// me da la cantidad de char en 0 que necesito
	int cant_bit = bits%4; //me da la cantidad de bits del ultimo char en 0


	for (nonce_aux = 0; out ==0 ; nonce_aux++)//aumento el nonce hasta que el flag out sea 1, igualmente tambien hay un break, es por las dudas que el break no funcione como espero
	{
		header_str.clear();
		nonce = nonce_aux;
		header_str = getHeaderAsString();
		header_str.append("\n");
		hash_header = sha256(sha256(header_str)); //calculo el hash del header_aux
		i=0;
		aux=0;
		while (i<cant_char)
		{
			if(hash_header[i] != '0')
			{
				aux=1;
				break;
			}
			i++;
		}
		if(aux==1)
		{
			continue;
		}
		else
		{
			hash_header = Hex2Bin(hash_header.substr(i,i+1));
			
			j=0;
			aux=0;
			while (j<cant_bit)
			{
				if(hash_header[j] != '0')
				{
					aux=1;
					break;
				}
				j++;
			}
			if(aux == 0)
			{
				nonce = nonce_aux;//guardo el nonce en el header_aux
		   		out = 1; // Para verificar que termine el for
				break; //como cumple la canditad de bits necesarias y ya esta guardado y hasheado salgo
			}
		}
	}
	return ;
}

void hdr::show(ostream& oss)
{
	oss << prev_block << endl;
	oss << txns_hash << endl;
	oss << bits << endl;
	oss << nonce << endl;
}
//--------------------------CLASE BLOCK----------------------------------------------------------------------------------------
class block
{   
	private:
	hdr header;
	bdy body;

	public:
	block(); //Creador base
	block(const string,const  size_t, istream*); //Creador en base al hash del bloque previo, al nivel de  
												//dificultad y un flujo de entrada por el que se reciben las 
											   // transacciones.
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
	void show(ostream&);
	friend ostream& operator<<(ostream& oss, block& block) 
	{
		block.show(oss);
		return oss;
	}
};

hdr block::getHeader()
{
	return header;
}
bdy block::getBody()
{
	return body;
}


void block::setHeader(hdr h){header = h;}

void block::setHeader(const string& prev_block_str,const size_t diffic)
{
	string aux;
	header.setPrevBlock(prev_block_str);
	aux = body.getBodyAsString();
	header.setTxnsHash(aux);
	header.setBits(diffic);
	header.setNonce(header.getPrevBlock(),header.getTxnHash(),header.getBits());
}

block & block::operator=(const block & right)
{
	if(&right != this)
	{
		header = right.header;
		body = right.body;
		return *this;
	}
	return *this;
}

string block::setBody(istream *iss)
{
	string str;
	getline(*iss, str, '\n');
	size_t txn_count = stoi(str);
	//validar que sea numero
	body.setTxnCount(txn_count);
	//body.txnsArrRedim(1); //Se inicializa en uno. Tiene redimensionamiento automatico a
						 // traves de metodos de la clase.
	str=body.setTxns(iss);
	if (isHash(str)==true)
	{
		return str;
	}	
	else if (str=="")
	{
		return str;
	}	
	else if(str!="OK")
	{
		cerr<< "ERROR: set txns fallo";
	   exit(1);
	}
	return "OK";
}

block::block()
{
	header.prev_block=NULL_HASH;
	header.txns_hash=NULL_HASH;
	header.bits=0;
	header.nonce=0;

	body.txn_count=0;
	//El campo txn tiene su propio inicializador base. No hace falta ponerlo
}

block::block(const string str,const  size_t diffic, istream *iss)
{
	setBody(iss);
	setHeader(str, diffic);
}

block::~block()
{
}

string block::getBlockAsString()
{
	string result, str;
	result.append(header.getHeaderAsString());
	result.append("\n");
	result.append(body.getBodyAsString());
	return result;
}

void block::show(ostream& oss)
{
	oss << header;
	oss << body;
}


#endif //_BLOCK_H_