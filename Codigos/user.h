#ifndef _USER_H_
#define _USER_H_

#include "block.h"
#include "Lista.h"

class user
{
	string name;
	double balance;
	list <txn> transactions; //Solo se guardan las transacciones donde user aparece como output.
	public:
	user();
	user(string);
	~user();
	string getName();
	double getBalance();
	list<txn>& getTransactions();

	void setName(const string &);
	void setBalance(const double &);
	void setTransactions(const list<txn> &);
	void show(ostream&);
	
	string toString();
	friend ostream& operator<<(ostream& oss, user& usr) 
	{
		usr.show(oss);
		return oss;
	}

	user const &operator=(user const &);

};

user::user()
{
	name = "";
	balance = 0;
}

user::~user()
{
}

user::user(string str_user)
{
	//Para crear el usuario a partir de una string, se considera que dicha string contiene todos los campos de user separados 
	//por fines de linea (\n): name,balance y transactions.
	istringstream ss(str_user);
	bdy aux_body;

	string aux_str;
	txn aux_txn;
	getline(ss, this->name, '\n');
	getline(ss, aux_str, '\n');
	balance = stod(aux_str);
	aux_body.setTxns(&ss); 

	Array <txn> array_aux_txns=aux_body.getTxns();
	for(size_t i=0; i<aux_body.getTxnCount(); i++)
	{
		this->transactions.append(array_aux_txns[i]);
	}
	// }
}

string user::getName()
{
	return name;
}
double user::getBalance(){return balance;}
list<txn>& user::getTransactions(){return transactions;}

void user::setName(const string & str){name = str;}
void user::setBalance(const double & n){balance = n;}
void user::setTransactions(const list<txn> & d){transactions = d;}

void user::show(ostream& oss)
{
	if(name == "")
		return ;
	oss << name << endl;

	oss << balance << endl;
	
	oss << transactions;
}

string user::toString()
{
    ostringstream ss;
    ss << *this;
    return ss.str();
}


user const &user::operator=(user const &right)
{
	if(&right != this)
	{
		name = right.name;
		balance = right.balance;
		transactions = right.transactions;
		return *this;
	}
	return *this;
}
#endif //_USER_H_