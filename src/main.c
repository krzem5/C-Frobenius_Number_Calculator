#include <frobenius_number_calculator.h>
#include <stdint.h>
#include <stdio.h>



int main(int argc,const char** argv){
	uint64_t nums_a[]={5,7};
	uint64_t nums_b[]={9,6,20};
	uint64_t nums_c[]={999991,999992,999993,999994,999995,999996,999997,999998,999999,1000000};
	printf("%lu\n",frobenius_number(nums_a,sizeof(nums_a)/sizeof(uint64_t),1));
	printf("%lu\n",frobenius_number(nums_b,sizeof(nums_b)/sizeof(uint64_t),0));
	printf("%lu\n",frobenius_number(nums_c,sizeof(nums_c)/sizeof(uint64_t),1));
	return 0;
}
