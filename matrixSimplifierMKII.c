#include<stdio.h>
#define ll long long
#define MAXN 305
#define MAXM 3005
ll data[MAXN][MAXN];
int lab_c[MAXM];
int n,m; //n lines * m columns
int tot=0;
int lab_1[MAXM],lab_2[MAXM];
ll lab_3[MAXM];
double ki=1.0;
#define SWAPLINE 1
#define DIMLINE 2
#define MULONLY 3
#define DIV 4
const char *LABSTR[]={"NONE","SWAPLINE","DIMLINE","MUL","DIV"};
void inline lswap(ll *a,ll *b){
	ll tp=*a;
	*a=*b;
	*b=tp;
}
ll inline gcd(ll a,ll b){
	ll tp;
	if(a<0) a=-a;
	if(b<0) b=-b;
	if(a<b)
		lswap(&a,&b);
	tp = a%b;
	while(tp){
		a=b;
		b=tp;
		tp = a%b;
	}
	return b;
}
ll inline lcm(ll a,ll b){
	if(a<0) a=-a;
	if(b<0) b=-b;
	return a/gcd(a,b)*b;
}
ll gcd_line(int line){
	int i;
	ll rtn=0ll;
	for(i=1;i<=m;++i){
		if(data[line][i]!=0ll){
			if(rtn==0ll)
				rtn=data[line][i];
			else
				rtn=gcd(rtn,data[line][i]);
		}
		if(rtn==1ll)
			break;
	}
	return rtn;
}
ll lcm_column(int column){
	int i;
	ll rtn=0ll;
	for(i=1;i<=n;++i){
		if(data[i][column]!=0ll){
			if(rtn==0ll)
				rtn=data[i][column];
			else
				rtn=lcm(rtn,data[i][column]);
		}
	}
	return rtn;
}
void upd_line(int line){
	ll res=gcd_line(line);
	if(res==0ll||res==1ll)
		return ;
	else{
		int i;
		for(i=1;i<=m;++i){
			data[line][i]/=res;
		}
		++tot;
		lab_c[tot]=DIV;
		lab_1[tot]=line;
		lab_3[tot]=res;
		ki*=res;
	}
}
void swap_line(int line1,int line2){
	int i;
	for(i=1;i<=m;++i)
		lswap(&data[line1][i],&data[line2][i]);
	++tot;
	lab_c[tot]=SWAPLINE;
	lab_1[tot]=line1;
	lab_2[tot]=line2;
	ki*=-1;
}
void mul_line(int line,ll w){
	if(w==1ll)
		return ;
	int i;
	for(i=1;i<=m;++i)
		data[line][i]*=w;
	++tot;
	lab_c[tot]=MULONLY;
	lab_1[tot]=line;
	lab_3[tot]=w;
	ki/=w;
}
void dim_line(int line0,int line1){
	int i;
	for(i=1;i<=m;++i){
		data[line0][i]-=data[line1][i];
	}
	++tot;
	lab_c[tot]=DIMLINE;
	lab_1[tot]=line0;
	lab_2[tot]=line1;
}
void upd_line_2(int line){
	ll res=gcd_line(line);
	int i;
	if(res==0ll)
		return ;
	else if(res == 1ll){
		for(i=1;i<=m;++i){
			if(data[line][i]<0){
				i=0;
				break;
			}else if(data[line][i]>0)
				break;
		}
		if(i==0){
			mul_line(line,-1ll);
		}
		return ;
	}else{
		for(i=1;i<=m;++i){
			if(data[line][i]<0){
				i=0;
				break;
			}else if(data[line][i]>0)
				break;
		}
		if(i==0)
			res=-res;
		for(i=1;i<=m;++i){
			data[line][i]/=res;
		}
		++tot;
		lab_c[tot]=DIV;
		lab_1[tot]=line;
		lab_3[tot]=res;
		ki*=res;
	}
		

}
void solve(){
	int i,j,k;
	int nw=1;
	ll tp;
	for(j=1;j<=m;++j){
		for(i=nw;i<=n;++i){
			if(data[i][j]!=0ll)
				break;
		}
		if(i>n){
			continue;
		}
		if(nw!=i)
			swap_line(nw,i);
		for(i=1;i<=n;++i)
			upd_line(i);
		tp=lcm_column(j);
		mul_line(nw,tp/data[nw][j]);
		for(i=1;i<=n;++i){
			if(i!=nw&&data[i][j]!=0ll){
				mul_line(i,tp/data[i][j]);
				dim_line(i,nw);
				upd_line(i);
			}
		}
		++nw;
	}
	for(i=1;i<=n;++i){
		upd_line_2(i);
	}
}
int main(){
	int i,j;
	printf("Input n and m plz:"); 
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		for(j=1;j<=m;++j)
			scanf("%lld",&data[i][j]);
	puts("--------------------"); 
	solve();
	for(i=1;i<=n;++i){
		for(j=1;j<=m;++j)
			printf("%lld ",data[i][j]);
		puts("");
	}
	printf("K=%.3lf\n",ki);
	puts("Press ENTER to get detailed information...");
	getchar();
	getchar();
	printf("tot=%d\n",tot);
	for(i=1;i<=tot;++i){
		switch(lab_c[i]){
			case SWAPLINE:{
				printf("%s:#%d & #%d\n",LABSTR[lab_c[i]],lab_1[i],lab_2[i]);
				break;
			}
			case DIMLINE:{
				printf("%s:#%d - #%d\n",LABSTR[lab_c[i]],lab_1[i],lab_2[i]);
				break;
			}
			case MULONLY:case DIV:{
				printf("%s:line #%d %s %lld\n",LABSTR[lab_c[i]],lab_1[i],LABSTR[lab_c[i]],lab_3[i]);
				break;
			}
		}
	}
	puts("Press ENTER to continue...");
	getchar();
	return 0;
}
#undef ll
#undef MAXN
#undef MAXM
#undef SWAPLINE
#undef DIMLINE
#undef MULONLY
#undef DIV
/*
3 4
1 2 3 4
1 1 2 2
5 6 7 8
*/
