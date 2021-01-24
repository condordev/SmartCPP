#pragma once

#include<iostream> 
#include<string> 
using namespace std;


class BigDataBase
{
protected:
	long bignumber;
public:
	inline BigDataBase(const long& number) : bignumber (number){
	}

	long getNumber(){
		return bignumber;
	}

	void print() {
		wcout << L"BigDataBase::bignumber " << bignumber << endl;
	}
};


class BigData : public BigDataBase
{
public:
	wstring titel;
	wstring author;
	//BigData(const long& num, const wstring& title, const wstring& author);
	BigData(const long& num, const wstring& title, const wstring& author) : titel(title), author(author), BigDataBase(num){
		//this->titel = title;
		//this->author = author;
	}

	void print() {
		BigDataBase::print();
		wcout << L"Number: " << this->getNumber() << L" Title: " << this->titel << L" Author: " << this->author << endl;
	}
};

