#include<stdio.h>
#include<curl/curl.h>



void dirbrute(const char* url,const char* words[],size_t nums);

void main(){


    //const char* url ="https://google.com";

    char url[256];
    printf("Enter Target URL: ");
    scanf("%255s",url);
    const char* words[]={"/admin","/Dashboard","/admin/Dashboard","/api","/admin2","/api2","/admin/admin","/dashboard","/images","/slider","/app","/wp","/ftp"};

    /*char urls[512];
    sprintf(urls,sizeof(urls),"%s%s",url,words[4]);

    printf("Scanning Started!");
    printf(urls);
    */


   size_t nums=sizeof(words)/sizeof(words[0]);
   dirbrute(url,words,nums);

}

void dirbrute(const char* url,const char* words[],size_t nums){

    CURL* curl;
    CURLcode res;
    curl=curl_easy_init();
    if(curl)
    {
        for (size_t i=0;i<nums;i++) 
        {
            char urls[512];
            snprintf(urls,sizeof(urls),"%s%s",url,words[i]);
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
                printf("Something Wrong");
            }
        }


    }
    else{
        printf("Initi Failed!!!");
    }



}
