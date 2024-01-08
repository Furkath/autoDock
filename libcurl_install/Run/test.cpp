#include <iostream>
#include <curl/curl.h>
//#include <string>

//int WriteDate(void *buffer, size_t sz, size_t nmemb, void *ResInfo)
//{
//	string* psResponse = (string*)ResInfo;
//	psResponse->append((char*)buffer, sz*nmemb);
//	return sz*nmemb;
//}
int main(void)
{
	CURL *curl;
	CURLcode res;

	curl_global_init(CURL_GLOBAL_DEFAULT);

	curl=curl_easy_init();
	if(curl)
	{
         	curl_easy_setopt(curl, CURLOPT_URL,"https://cloud.arest.io/VM450G12/test?params=rg10");
		//curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION ,WriteDate); as long as receiving, WriteData woul be called, if default, just cout the 
		//                                                          information to comman line; also the command line stdout could be replaced 
		//                                                          to WRUTEDATA specification as below.
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ResString); you can declare the ResString [string] before and set it as where the receive 
		//                                                       data should be stored, this can aslo be stored to a file id. 
	 	res=curl_easy_perform(curl);
	 	if(res!=CURLE_OK)
	 	{
			std::cerr<<"curl_easy_perform() failed: "<<curl_easy_strerror(res)<<std::endl;
			curl_easy_cleanup(curl);
		}
		//else
		//{
			//cout<<ResString<<endl;
		//}
	}
	curl_global_cleanup();
	return 0;
}
