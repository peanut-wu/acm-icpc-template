#include<iostream>
#include<cstdio>
#define MAX  65536
using namespace std;
int a[1000001],b[1000001],c[MAX+2],d[MAX+2],n;
int main()
{
 freopen("sort.in","r",stdin);freopen("sort.out","w",stdout);
 scanf("%d",&n);
 for (int q=0;q<n;q++) 
  {
	scanf("%d",&a[q]);
	c[1+(a[q]/MAX)]++;
	d[1+(a[q]%MAX)]++;
  }
 for (int q=1;q<=MAX;q++)
  {
	c[q]+=c[q-1];
	d[q]+=d[q-1];
  }
 for (int q=0;q<n;q++) b[d[a[q]%MAX]++]=a[q];
 for (int q=0;q<n;q++) a[c[b[q]/MAX]++]=b[q];
 for (int q=0;q<n;q++) printf("%d ",a[q]);
 fclose(stdin);fclose(stdout);
 return 0;
}
