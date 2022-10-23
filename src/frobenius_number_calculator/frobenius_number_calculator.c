#include <stdint.h>
#include <stdlib.h>



uint64_t frobenius_number(const uint64_t* data,uint64_t count){
	if (!count){
		return 0;
	}
	uint64_t a1=*data;
	count--;
	if (!count){
		return a1-1;
	}
	data++;
	uint64_t l=(a1+63)>>6;
	uint64_t* b=malloc((count+l+3*a1)*sizeof(uint64_t));
	uint64_t* m=b+count;
	uint64_t* p=m+l;
	uint64_t* q=p+a1;
	uint64_t* s=q+a1;
	p[0]=count;
	q[0]=0;
	s[0]=0;
	for (uint64_t i=0;i<count;i++){
		b[i]=data[i]%a1;
	}
	for (uint64_t i=0;i<l;i++){
		m[i]=0;
	}
	uint64_t v=a1*data[count-1];
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
		for (uint64_t k=0;k<p[u];k++){
			uint64_t v=u+b[k];
			if (v>=a1){
				v-=a1;
			}
			uint64_t w=t+data[k];
			if (w>=s[v]){
				continue;
			}
			s[v]=w;
			p[v]=k+1;
			uint64_t n=1ull<<(v&63);
			if (m[v>>6]&n){
				continue;
			}
			q[j]=v;
			m[v>>6]|=n;
			j++;
			if (j==a1){
				j=0;
			}
		}
	} while (i!=j);
	uint64_t out=0;
	for (uint32_t i=0;i<a1;i++){
		if (s[i]>out){
			out=s[i];
		}
	}
	free(b);
	return out-a1;
}
