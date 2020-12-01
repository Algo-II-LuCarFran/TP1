#ifndef _USER_H_
#define _USER_H_

#include "block.h"
#include "Lista.h"

class user
{
	string name;
	double balance;
	list<txn> transactions;
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
	istringstream ss(str_user);
	string str;

	getline(ss, name, '\n');
	getline(ss, str, '\n');
	balance = stod(str);
	getline(ss, str, '\n');
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
#endif //_USER_H_