#include<stdio.h>
#define MAXN 302 
#define ll long long
#define rep(i,a,n) for(i=a;i<=n;++i)
ll data1[MAXN][MAXN];
ll data2[MAXN][MAXN];
ll ans[MAXN][MAXN];
int m,n,p;
void matrixMul(){
	int i,j,k;
	rep(i,1,m)
		rep(j,1,p)
			rep(k,1,n)
				ans[i][j]+=data1[i][k]*data2[k][j];
}
int main(){
	int i,j;
	puts("Input m,n,p:");
	scanf("%d%d%d",&m,&n,&p);
	puts("--------------------");
	rep(i,1,m)
		rep(j,1,n)
			scanf("%lld",&data1[i][j]);
	puts("--------------------");
	rep(i,1,n)
		rep(j,1,p)
			scanf("%lld",&data2[i][j]);
	puts("--------------------");
	matrixMul();
	rep(i,1,m){
		rep(j,1,p)
			printf("%lld ",ans[i][j]);
		puts(" ");
	}
	puts("Press ENTER to exit...");
	getchar();
	getchar();
	return 0;
}
#undef rep
#undef ll
#undef MAXN
