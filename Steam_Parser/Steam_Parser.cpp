#include <iostream>
#include <curl/curl.h>
#include <string>
#include <vector>

static size_t write_data(char* ptr, size_t size, size_t nmemb, std::string* data) {
    if (data) {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }
    else
        return 0;
}

std::string delete_link(std::string htmlData)
{
    std::size_t startPos = htmlData.find("market_listing_row_link") + 31;
    std::size_t endPos = htmlData.find("resultlink") - 6;
    if (startPos != -1 && endPos != -1) {
        htmlData = htmlData.substr(startPos + endPos - startPos);
    }
    return htmlData;
}

std::string append_link(std::string htmlData, std::vector<std::string> links) {
    std::size_t startPos = htmlData.find("market_listing_row_link") + 31;
    std::size_t endPos = htmlData.find("resultlink") - 6;
    std::string link = "";

    if (startPos != -1 && endPos != -1) {
        link = htmlData.substr(startPos, endPos - startPos);
        links.push_back(link);
        std::cout << link << std::endl;
        return link;
    }
    
}

int main()
{
    CURL* curl;
    CURLcode response;
    std::string htmlData;
    std::vector<std::string> links;

    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "https://steamcommunity.com/market/");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &htmlData);
    response = curl_easy_perform(curl);

    std::cout << std::endl << std::endl << std::endl;
    std::cout << htmlData;

    std::size_t startPos = htmlData.find("market_listing_row_link");
    
    while (startPos != -1) {
        startPos = htmlData.find("market_listing_row_link");
        append_link(htmlData, links);
        htmlData = delete_link(htmlData);
    }
    
    return 0;
}