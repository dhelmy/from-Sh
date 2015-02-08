#include "continued.h"

static int remainderz;
unsigned int division(unsigned int dividend, unsigned int divisor)
{
    int quotient = 1;

    unsigned int tempdividend = dividend;
    unsigned int tempdivisor = divisor;

     if (tempdivisor == tempdividend) {
        remainderz = 0;
        return 1;
     } else if (tempdividend < tempdivisor) {
       remainderz = (int) tempdividend;
              return 0;
     }
    while (tempdivisor<<1 <= tempdividend)
    {
        tempdivisor = tempdivisor << 1;
        quotient = quotient << 1;

     }
     /* Call division recursively */
    quotient = quotient + division((tempdividend-tempdivisor) , divisor);

     return quotient;
 }


unsigned int gcd(unsigned int a, unsigned int b){
	int g;
	if ((a+b) == 0) return 0; /* Error, both parameters zero */

	g = b;
	/* Iterate until a = 0 */
	while(a > 0){
		g = a;
		a = b % a;
		b = g;
	}

	return g;
};

unsigned int gcdFaster(unsigned int a, unsigned int b) 	{

	int g;
	if ((a+b) == 0) return 0; /* Error, both parameters zero */

	g = b;
	/* Iterate until a = 0 */
	while(a > 0){
		g = a;
		a = division (b , a);
		b = g;
	}

return g;
};

ContinuedFraction *getCFlargerThanOne(unsigned int b, unsigned int a) {
	auto toRet = new ContinuedFraction;
	if (b<a){
		toRet->tail = nullptr;
		return toRet;
	}
	int head = division(b,a);
	int remaindr = b - (head * a);
	toRet->head = head;

	if (remaindr != 0 ) toRet->tail = getCFlargerThanOne(a, remaindr);
	else toRet->tail = nullptr;

	return toRet;
}

//ContinuedFraction *getCF(unsigned int b, unsigned int a) {
//	//TODO
//	return nullptr;
//}


ContinuedFraction *getCF(unsigned int head, ContinuedFraction *fixed, ContinuedFraction *period) {
    auto toRet = new ContinuedFraction;

    int cnt=0;
    
    ContinuedFraction *newListPtr, *oldListPtr ;
    
    newListPtr = toRet;
    
    newListPtr->head = head;
    oldListPtr = fixed;
    
    while (oldListPtr != nullptr){
        newListPtr->tail =  new ContinuedFraction;
        newListPtr->head = oldListPtr->head;
        
        newListPtr = newListPtr->tail;
        oldListPtr = oldListPtr->tail;
        
        if (oldListPtr==nullptr && cnt<3) {
            oldListPtr = period;
            cnt++;
        }
    }
    
    return toRet;
}


Fraction getApproximation(ContinuedFraction *fr, unsigned int n) {
    int head;
    int actualhead;
    int tail;
    Fraction toRet;
    ContinuedFraction * CF;
    
    CF = fr;
    head  = CF->head;
    actualhead = head;
    tail = CF->tail->head;
    int denom = 0;
    
    for(int i = 0; i < n; i++){
        denom += gcdFaster(head, tail);
        CF = CF->tail;
    }
    toRet.denominator = denom;
    toRet.numerator = actualhead * denom;
    
    return toRet;
}
