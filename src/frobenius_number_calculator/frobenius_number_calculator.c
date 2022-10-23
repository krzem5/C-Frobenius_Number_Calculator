#ifdef __SLL_BUILD_WINDOWS
#include <intrin.h>
#endif
#include <stdint.h>
#include <stdlib.h>



#ifdef _MSC_VER
#pragma intrinsic(_BitScanReverse64)
static __SLL_FORCE_INLINE uint32_t FIND_LAST_SET_BIT(uint64_t m){
	unsigned long o;
	_BitScanReverse64(&o,m);
	return o;
}
#else
#define FIND_LAST_SET_BIT(m) (63-__builtin_clzll((m)))
#endif



uint64_t frobenius_number(const uint64_t* data,uint64_t count){
	if (!count){
		return 0;
	}
	if (count==1){
		return data[0]-1;
	}
	if (count==2){
		return (data[0]-1)*(data[1]-1)-1;
	}
	uint64_t* a=malloc((2*count-1)*sizeof(uint64_t));
	uint64_t* b=a+count;
	for (uint64_t i=0;i<count;i++){
		a[i]=data[i];
	}
	uint64_t merge_sort_tmp_length=1<<(FIND_LAST_SET_BIT(count)+1);
	if (merge_sort_tmp_length>count){
		merge_sort_tmp_length=count;
	}
	uint64_t* left=malloc(2*merge_sort_tmp_length*sizeof(uint64_t));
	uint64_t* right=left+merge_sort_tmp_length;
	uint64_t w=1;
	count--;
	while (w<=count){
		uint64_t l=0;
		while (l<=count){
			uint64_t m=l+w-1;
			uint64_t r=m+w;
			if (m>count){
				m=count;
			}
			if (r>count){
				r=count;
			}
			uint64_t left_l=m-l+1;
			uint64_t right_l=r-m;
			if (!right_l){
				l+=w<<1;
				continue;
			}
			for (uint64_t i=0;i<left_l;i++){
				left[i]=a[l+i];
			}
			for (uint64_t i=0;i<right_l;i++){
				right[i]=a[m+i+1];
			}
			uint64_t i=0;
			uint64_t j=0;
			while (1){
				if (left[i]>right[j]){
					a[l]=right[j];
					j++;
					if (j==right_l){
						do{
							l++;
							a[l]=left[i];
							i++;
						} while (i<left_l);
						break;
					}
				}
				else{
					a[l]=left[i];
					i++;
					if (i==left_l){
						do{
							l++;
							a[l]=right[j];
							j++;
						} while (j<right_l);
						break;
					}
				}
				l++;
			}
			l++;
		}
		w<<=1;
	}
	free(left);
	uint64_t a1=a[0];
	a++;
	uint64_t l=(a1+63)>>6;
	uint64_t* m=malloc((l+3*a1)*sizeof(uint64_t));
	uint64_t* p=m+l;
	uint64_t* q=p+a1;
	uint64_t* s=q+a1;
	count--;
	p[0]=count;
	q[0]=0;
	s[0]=0;
	for (uint64_t i=0;i<=count;i++){
		b[i]=a[i]%a1;
	}
	for (uint64_t i=0;i<l;i++){
		m[i]=0;
	}
	uint64_t v=a1*a[count];
	for (uint64_t i=1;i<a1;i++){
		s[i]=v;
	}
	uint64_t i=0;
	uint64_t j=1;
	do{
		uint64_t u=q[i];
		i++;
		if (i==a1){
			i=0;
		}
		m[u>>6]&=~(1ull<<(u&63));
		uint64_t t=s[u];
		for (uint64_t k=0;k<=p[u];k++){
			uint64_t v=u+b[k];
			if (v>=a1){
				v-=a1;
			}
			uint64_t w=t+a[k];
			if (w>=s[v]){
				continue;
			}
			s[v]=w;
			p[v]=k;
			uint64_t n=1ull<<(v&63);
			if (m[v>>6]&n){
				continue;
			}
			q[j]=v;
			j++;
			if (j==a1){
				j=0;
			}
			m[v>>6]|=n;
		}
	} while (i!=j);
	free(a-1);
	uint64_t out=0;
	for (uint32_t i=0;i<a1;i++){
		if (s[i]>out){
			out=s[i];
		}
	}
	free(m);
	return out-a1;
}
