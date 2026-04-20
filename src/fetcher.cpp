#include "fetcher.h"
#include <curl/curl.h>
#include <iostream>

static size_t writeCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize=size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

std::string httpGet(const std::string& url) {
    CURL* curl=curl_easy_init();
    std::string response;

    if (!curl) {
        std::cerr<<"Failed to initialize curl"<<std::endl;
        return "";
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res=curl_easy_perform(curl);

    if (res!=CURLE_OK) {
        std::cerr<<"curl error: "<<curl_easy_strerror(res)<<std::endl;
    }

    curl_easy_cleanup(curl);
    return response;
}