#pragma once
#include "MenuManager.h"
#include "TaxManager.h"
#include "PersonManager.h"
#include <time.h>
#include <stdio.h>
#include <io.h>
#include <conio.h>

class Sale
{
	PersonManager PM;
	MenuManager MM;
	TaxManager TM;
	
public:
	Sale();

	void manageMain();

	void saleMain();

	void saleManage();

	void foodSaleTax();

	int personFoodBuySum(string name, string food);

	int personCouponBuySum(string name, string food);

	int personBuySum(string name);

	void personSaleTax();

	void personBuyTax();

	void dateSaleTax();

	string getToday();
	//~Sale();
};