#include "Tax.h"

string Tax::save()
{
	return name + "," + food + "," + to_string(coupon);
}
