#ifndef _USER_H_
#define _USER_H_

#include "Array.h"
#include "block.h"

class user
{
	string name;
	double balance;
	bdy transactions;
public:
	user();
	user(string);
	~user();
	string getName();
	double getBalance();
	const bdy& getTransactions();

	void setName(const string &);
	void setBalance(const double &);
	void setTransactions(const bdy &);
	void show(ostream&);
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
	string balance_str;

	getline(ss, name, '\n');
	getline(ss, balance_str, '\n');
	balance = stod(balance_str);

	transactions.setTxns(&ss);
}

string user::getName(){return name;}
double user::getBalance(){return balance;}
const bdy & user::getTransactions(){return transactions;}

void user::setName(const string & str){name = str;}
void user::setBalance(const double & n){balance = n;}
void user::setTransactions(const bdy & body){transactions = body;}

void user::show(ostream& oss)
{
	if(name == "")
		return ;
	oss << name << endl;

	oss << balance << endl;
	
	oss << transactions;
}
#endif //_USER_H_