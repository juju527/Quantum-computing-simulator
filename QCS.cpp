//Code by juju527.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<complex<double>> vec;
typedef vector<vec> Matrix;
#define eb emplace_back
int read(){
    int x=0,y=1;
    char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')y=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<3)+(x<<1)+(ch^48),ch=getchar();
    return x*y;
}
mt19937_64 rnd(random_device{}());
const Matrix X={{0, 1},{1, 0}};
const Matrix H={{1/sqrt(2),1/sqrt(2)},{1/sqrt(2),-1/sqrt(2)}};
Matrix phase(double theta){return{{1, 0},{0, exp(complex<double>(0, theta))}};}
struct Qubits{
    int n;
    vec a;
    Qubits(int m){
        n=m;
        a.resize(1<<m,0);
        a[0]=1;
    }
    void apply_gate(Matrix T,int p){
        int S=(1<<n)-1;
        vec b(S+1);
        for(int s=0;s<=S;s++){
            int c=(s>>p)&1;
            for(int d=0;d<2;d++)b[s^((c^d)<<p)]+=T[d][c]*a[s];
        }
        a=b;
    }
    void apply_cnot(int con,int tar){
        int S=(1<<n)-1;
        vec b(S+1);
        for(int s=0;s<=S;s++){
            int c=(s>>con)&1;
            b[s^(c<<tar)]+=a[s];
        }
        a=b;
    }
    int measure(int p){
        int S=(1<<n)-1;
        double pro[2]={0,0};
        for(int s=0;s<=S;s++)pro[(s>>p)&1]+=norm(a[s]);
        uniform_real_distribution<double> dist(0.0,1.0);
        int d=dist(rnd)<pro[1];
        vec b(S+1);
        double coef=sqrt(pro[d]);
        for(int s=0;s<=S;s++){
            int c=(s>>p)&1;
            if(c^d)b[s]=0;
            else b[s]=a[s]/coef;
        }
        a=b;
        return d;
    }
};
ll shor_quantum_part(ll a,ll N){
    int n=0,m=0;
    while((1ll<<n)<N)n++;
    m=2*n;
    Qubits st(m+n);
    for(int i=0;i<m;i++)st.apply_gate(H,i);
    st.apply_gate(X,m);
    ll r=0;
    return r;
}
ll power(ll x,ll b,ll n){
    ll res=1;
    while(b){
        if(b&1)res=(__int128)x*x%n;
        x=(__int128)x*x%n;
        b>>=1;
    }
    return res;
}
ll factor(ll n){
    ll a,g,r;
    do{
        a=rnd()%(n-1)+1,g=__gcd(n,a);
        if(g>1){printf("%lld %lld\n",g,n/g);exit(0);}
        r=shor_quantum_part(a,n);
    }while(r&1);
    ll x=__gcd(power(a,r/2-1,n),n);
    if(x>1){printf("%lld %lld\n",x,n/x);exit(0);}
    x=__gcd(power(a,r/2+1,n),n);
    printf("%lld %lld\n",x,n/x);
    exit(0);
}
int main(){
    
    return 0;
}