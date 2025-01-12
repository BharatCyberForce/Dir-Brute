#include<stdio.h>
#include<curl/curl.h>
#include<stdlib.h>
#include<string.h>


void dirbrute(const char* url,char* wordlis[],size_t nums);

void main(){
    printf("=========================\n");
    printf("        Dir-Brute\n");
    printf("=========================\n\n");

    //const char* url ="https://google.com";
    char words[256]; 
    char url[256];
    printf("Enter Your Target Site: ");
    scanf("%255s",url);
    printf("Enter Your Word List Name: ");
    scanf("%255s",words);

    FILE* file=fopen(words,"r");



    char* wordlist[2048];
    size_t nums=0;
    char line[256];
    while (fgets(line,sizeof(line),file))
    {
        line[strcspn(line,"\n")]='\0';
        wordlist[nums]=strdup(line);
        nums++;
    }
    fclose(file);

    
    /*
    const char* words[]={"/admin","/Dashboard","/admin/Dashboard","/api","/admin2","/api2","/admin/admin","/dashboard","/images","/slider","/app","/wp","/ftp"};

    //char urls[512];
    //sprintf(urls,sizeof(urls),"%s%s",url,words[4]);

    printf("Scanning Started!");
    printf(urls);
    size_t nums=sizeof(words)/sizeof(words[0]);
   */
  dirbrute(url,wordlist,nums);



}

void dirbrute(const char* url,char* wordlist[],size_t nums){

    CURL* curl;
    CURLcode res;
    curl=curl_easy_init();
    if(curl)
    {
        for (size_t i=0;i<nums;i++) 
        {
            char urls[512];
            snprintf(urls,sizeof(urls),"%s%s",url,wordlist[i]);
            curl_easy_setopt(curl,CURLOPT_URL,urls);
            curl_easy_setopt(curl,CURLOPT_NOBODY,1L);
            curl_easy_setopt(curl,CURLOPT_FOLLOWLOCATION,1L);
            res=curl_easy_perform(curl);
            

            if(res==CURLE_OK){
                long response;
                curl_easy_getinfo(curl,CURLINFO_RESPONSE_CODE,&response);
                printf("Target: %s Status Code: %ld \n",urls,response);

            }
            else{
                printf("Something Wrong!(Check Your Internet Connection....)\n");
            }
        }


    }
    else{
        printf("Initi. Failed!!!");
    }



}
