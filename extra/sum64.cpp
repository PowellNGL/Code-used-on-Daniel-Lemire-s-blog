/**
* Scalar product over 64-bit integers
g++ -O3 -o sum64 sum64.cpp && ./sum64
*/
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <iostream>

using namespace std;



// u and v must be multiplied, result is l,h,vh (192-bit integer counter)
void mult64to128thenaddto192(uint64_t u, uint64_t v,  uint64_t &vh, uint64_t& h, uint64_t &l)
{
	__uint128_t duh = (__uint128_t) u * (__uint128_t) v;
	__uint128_t base = ((__uint128_t) l) + (((__uint128_t) h )<<64);
	__uint128_t carryless = duh + base;
	if(carryless < base) vh++;
	l = (uint64_t)carryless;
	h = (uint64_t)(carryless >> 64);
}

void asm_mult64to128thenaddto192(uint64_t u, uint64_t v,  uint64_t &rhh, uint64_t& rh, uint64_t &rl)
{
    __asm__ ("mulq %[v]\n"
             "addq %%rax,  %[rl]\n"
              "adcq %%rdx,  %[rh]\n"
             "adcq $0,  %[rhh]\n"
             :  [rh] "+r" (rh), [rhh] "+r" (rhh) , [rl] "+r" (rl)  : [u] "a" (u), [v] "rm" (v)  :"rdx","cc" );

}

struct uint192 {
	uint64_t low;
	uint64_t high;
	uint64_t vhigh;
} ;

uint192 scalarproduct(size_t length, const uint64_t * a, const uint64_t * x) {
	uint192 s;
	s.low = 0;
	s.high = 0;
	s.vhigh = 0;
	
	__uint128_t base = 0;
	for(size_t i = 0; i<length; ++i) {
	  __uint128_t carryless = (__uint128_t) a[i] * (__uint128_t) x[i];
	  base += carryless;
	  s.vhigh += (carryless > base);
	}
	s.low = (uint64_t)base;
	s.high = (uint64_t)(base>>64);
	return s;
}


uint192 asmscalarproduct(size_t length, const uint64_t * a, const uint64_t * x) {
	uint192 s;
	s.low = 0;
	s.high = 0;
	s.vhigh = 0;
	for(size_t i = 0; i<length; ++i) {
    __asm__ ("mulq %[v]\n"
             "addq %%rax,  %[rl]\n"
        "adcq %%rdx,  %[rh]\n"
             "adcq $0,  %[rhh]\n"
             :  [rh] "+r" (s.high), [rhh] "+r" (s.vhigh) , [rl] "+r" (s.low)  : [u] "a" (a[i]), [v] "rm" (x[i])  :"rdx","cc");
	}
	return s;
}


void check() {

    uint64_t l1 = 0;
    uint64_t h1 = 0;
    uint64_t vh1 = 0;
    uint64_t l2 = 0;
    uint64_t h2 = 0;
    uint64_t vh2 = 0;
    for(int k = 0; k<1000; ++k) {
        const uint64_t u =  rand()+(((uint64_t)rand())<<32);
        const uint64_t v = rand() + (((uint64_t)rand())<<32);


        {
            mult64to128thenaddto192(u, v,  vh1, h1, l1);
        }
        {
            asm_mult64to128thenaddto192(u, v,  vh2, h2, l2);

        }
        if((h1!=h2) or (l1!=l2) or (vh1!=vh2)) {
            cerr<<"bug"<<endl;
            cout<<"low "<<l1<<" "<<l2<<endl;
            cout<<"high "<<h1<<" "<<h2<<endl;
            cout<<vh1<<" "<<vh2<<endl;
            break;
        }
    }
}

int main() {
	const size_t N = 100000;
	uint64_t a[N];
	uint64_t x[N];
	for(size_t i = 0; i < N; ++i) {
	  a[i] = rand() + (((uint64_t)rand())<<32);
	  x[i] = rand() + (((uint64_t)rand())<<32);
	}
	uint192 s1, s2;
	int t1 = 0; 
	int t2 = 0;
	const clock_t S1 = clock();

	for(int T=0; T<10000;++T) {
	  s1 = scalarproduct(N, a, x);
    }
	const clock_t S2 = clock();
	for(int T=0; T<10000;++T) {
	  s2 = asmscalarproduct(N, a, x);
	}
    const clock_t S3 = clock();
    cout<<"GCC time="<<(double)(S2-S1)/ CLOCKS_PER_SEC<<endl;
    cout<<"asm time="<<(double)(S3-S2)/ CLOCKS_PER_SEC<<endl;

	cout<<s1.low<<" "<<s1.high<<" "<<s1.vhigh<<endl;
	cout<<s2.low<<" "<<s2.high<<" "<<s2.vhigh<<endl;
}