    #include <cstdio>
    #include <cstring>
    #include <iostream>
    //#include <cmath>
    #include <algorithm>
    using namespace std;
    #define scnaf scanf
    #define maxtot 2097252
    #define maxsize 5500
    #define maxnum 900
    int me_po[maxnum],nxt[maxnum],siz[maxnum];
    char data[maxnum][maxsize],res[maxtot];
    int n,pos,cnt;
    struct list{
    	int cat_max(const int &a,const int &b){return a>b ? a:b;}
    	int cat_min(const int &a,const int &b){return a<b ? a:b;}
    	list(){
    		for(int i=1;i<maxnum;++i) me_po[i] = i;
    		cnt = 1;
    		nxt[0] = -1;siz[0] = 0;
    	}
    	void find(int &p,int &b){
    		for( b=0 ;b != -1 && p > siz[b] ;b = nxt[b])
    			p -= siz[b];
    	}
    	int newnode(){return me_po[cnt++];}
    	void delete_node(int x){me_po[--cnt] = x;}
    	void copy(int b,int len,char ch[],int ne){
    		siz[b] = len;nxt[b] = ne;
    		memcpy(data[b],ch,len);
    	}
    	void split(int p,int b){
    		if( p == siz[b] || b == -1 ) return ;
    		int t = newnode();
    		copy(t,siz[b]-p,data[b] + p,nxt[b]);
    		siz[b] = p;nxt[b] = t;
    	}
    	void maintain(int b){
    		for(;b != -1;b = nxt[b])
    			for(int i = nxt[b] ;i != -1&& siz[b] + siz[i] <= maxsize;i = nxt[b]){
    				memcpy(data[b]+siz[b],data[i],siz[i]);
    				siz[b] += siz[i];nxt[b] = nxt[i];
    				delete_node(i);
    			}
    	}
    	void insert(int now,int len,char res[]){
    		int b;find(now,b);
    		split(now,b);
    		int i,t;
    		for(i=0;i+maxsize <= len;i+=maxsize){
    			t = newnode();
    			copy(t,maxsize,res + i,nxt[b]);
    			nxt[b] = t;b = t;
    		}
    		if( len - i ){
    			t = newnode();
    			copy(t,len-i,res+i,nxt[b]);
    			nxt[b] = t;
    		}
    		maintain(b);
    	}
    	void delete_word(int p,int len){
    		int b,t;
    		find(p,b);split(p,b);
    		for(t = nxt[b];t != -1 && len > siz[t];t = nxt[t]) 
    			len -= siz[t];
    		split(len,t);t = nxt[t];
    		for(int i = nxt[b];i!=t;i=nxt[i]){
    			nxt[b] = nxt[i];delete_node(i);
    		}
    		maintain(b);
    	}
    	void get_data(int p,int len){
    		int b,i,t;
    		find(p,b);
    		i = cat_min(len,siz[b] - p);
    		memcpy(res,data[b] + p,i);
    		for(t = nxt[b]; t != -1 && i + siz[t] <= len;i+=siz[t],t = nxt[t])
    			memcpy(res+i,data[t],siz[t]);	
    		if( len - i && t != -1 ) memcpy(res+i,data[t],len-i);
    		res[len] = '\0';
    		printf("%s\n",res);
    	}
    };
    FILE *___=freopen("editor2003.in","r",stdin);
    FILE *_=freopen("editor2003.out","w",stdout);
    char ch[100];
    int main(){
    	list cojs;
    	//printf("point\n");
    	scnaf("%d",&n);
    	int x;char c;
    	for(int i=1;i<=n;++i){
    		scanf("%s",ch);
    		if( ch[0] == 'M' ){
    			scnaf("%d",&pos);
    		}else if( ch[0] == 'I' ){
    			scnaf("%d",&x);
    			for(int i=0;i<x;++i){
    				while(c = getchar(),c<32 || c> 126);
    				res[i] = c;				
    			}
    			cojs.insert(pos,x,res);
    		}else if(ch[0] == 'D'){
    			scanf("%d",&x);
    			cojs.delete_word(pos,x);
    		}else if(ch[0] == 'G'){
    			scnaf("%d",&x);
    			cojs.get_data(pos,x);
    		}else if(ch[0] == 'P') --pos;
    		else ++pos;
    	}
    	getchar();getchar();
    }