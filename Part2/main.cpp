#include <curl/curl.h>
#include <iostream>

size_t WriteCallback(void* ptr, size_t size, size_t nmemb, std::string* userdata) {
    userdata->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

int main() {
    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (CURL* curl = curl_easy_init()) {
        std::string response;
        curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT&limit=5");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode responseCode = curl_easy_perform(curl);

        if (responseCode != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(responseCode) << std::endl;
        }
        else {
            std::cout << response << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}