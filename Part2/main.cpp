#include <curl/curl.h>
#include <iostream>

constexpr bool USE_REAL_API = false; // Binance has limits and I don't want to go over them while testing

size_t WriteCallback(void* ptr, size_t size, size_t nmemb, std::string* userdata) {
    userdata->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

std::string getBinanceData() {
    if (!USE_REAL_API) {
        return R"([{"a":2801252062,"p":"117881.20","q":"0.018","f":6506173943,"l":6506173943,"T":1753608340535,"m":true},{"a":2801252063,"p":"117881.30","q":"0.001","f":6506173944,"l":6506173944,"T":1753608340550,"m":false})";
    }

    curl_global_init(CURL_GLOBAL_DEFAULT);
    std::string response;

    if (CURL* curl = curl_easy_init()) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://fapi.binance.com/fapi/v1/aggTrades?symbol=BTCUSDT&limit=5");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        CURLcode responseCode = curl_easy_perform(curl);

        if (responseCode != CURLE_OK) {
            std::cerr << "Request failed: " << curl_easy_strerror(responseCode) << std::endl;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            throw std::runtime_error("Binance request failed");
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return response;
}

int main() {
    auto binanceData = getBinanceData();
    std::cout << binanceData << std::endl;

    return 0;
}