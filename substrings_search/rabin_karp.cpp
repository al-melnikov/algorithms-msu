#include <iostream>
#include <string>

const int t = 256;
const int w = 1283;

void Rabin_Karp_Algorithm(std::string text, std::string pattern){
    
    //Length of text string.
    int tlen = text.length();
    
    //Length of pattern string.
    int plen = pattern.length();
    
    int flag;
    int c=1,i=0;
    
    //Calculate hash_p(hash value of pattern) and hash_0
    int hash_p=0,hash=0;
    while(i<plen){
        hash_p=(hash_p*t + pattern[i])%w;
        hash=(hash*t + text[i])%w;
        i++;
    }
    
     //Calculate (t^(plen-1))%w
    for(int i=1;i<=plen-1;i++)
        c=(c*t)%w;
    
    i=0;
    while(i<=tlen-plen){
       if(hash_p==hash){
            flag=1;
            for(int j=0;j<plen;j++){
                if(pattern[j]==text[i+j]){
                    continue;
                }
                else{
                    flag = 0;
                    break;
                }
           }
            if(flag==1)
                std::cout<<i<<" ";
       }
       
       
       //Calculate hash value of next window
       //hash_i+1 = t * {hash_i - text[i] * t^(plen-1)} + text[i+plen]
       if(i<tlen-plen){
           hash=((t*(hash-text[i]*c))+text[i+plen])%w;
            if(hash<0){
                hash = hash + w;
            }
       }
       i++;
    }
    std::cout << std::endl;
}

          
 
int main() 
{ 
    std::string text = "aa也池施aa地土人"; 
    std::string pattern = "aa";
    std::cout << text << std::endl;
    std::cout << pattern << std::endl;
    std::cout << text[2] << std::endl;
    Rabin_Karp_Algorithm(text,pattern);
    return 0; 
}

//some chinese letters
// 也 池 施 地 土 人 