#include<stdio.h> 
#include<math.h>
#define MAXN 101
double data[MAXN][MAXN];
double ansQ[MAXN][MAXN];
double ansR[MAXN][MAXN];
// m vectors belong to V(n)
int n,m;
const char *TEXT[]={
"Input n,m(Q:n*m,R:m*m):",
"--------------------"
};
double getLenth(int xx){
	int i;
	double rtn=0;
	for(i=1;i<=n;++i){
		rtn += ansQ[i][xx]*ansQ[i][xx];
	}
	return sqrt(rtn);
}
double getKi(int lx,int rx){
	int i;
	double rtn=0,tp=0;
	for(i=1;i<=n;++i){
		rtn+=data[i][lx]*ansQ[i][rx];
		tp+=ansQ[i][rx]*ansQ[i][rx];
	}
	return rtn/tp;
}
int main(){
	int i,j,k;
	double tp;
	printf(TEXT[0]);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			scanf("%lf",&data[i][j]);
		}
	}
	// begin Schimidt
	for(j=1;j<=m;++j){
		for(i=1;i<=n;++i){
			ansQ[i][j]=data[i][j];
		}
		for(k=1;k<j;++k){
			tp=getKi(j,k);
			for(i=1;i<=n;++i){
				ansQ[i][j]-=tp*ansQ[i][k];
			}
		}
	}
	
	for(j=1;j<=m;++j){
		tp=getLenth(j);
		for(i=1;i<=n;++i){
			ansQ[i][j]/=tp;
		}
	}
	// end Schimidt
	
	for(j=1;j<=m;++j){
		for(i=1;i<=j;++i){
			for(k=1;k<=n;++k){
				ansR[i][j]+=data[k][j]*ansQ[k][i];
			}
		}
	}
	
	puts(TEXT[1]);
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j){
			printf("%5.2lf ",ansQ[i][j]);
		}
		puts("");
	}
	puts(TEXT[1]);
	
	for(i=1;i<=m;++i){
		for(j=1;j<=m;++j){
			printf("%5.2lf ",ansR[i][j]);
		}
		puts("");
	}
	
	puts("Press ENTER to exit...");
	getchar();
	getchar();
}
#undef MAXN
