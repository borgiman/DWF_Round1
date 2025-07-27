#include <curl/curl.h>
#include <iostream>
#include <vector>

constexpr bool USE_REAL_API = false; // Binance has limits and I don't want to go over them while testing

size_t WriteCallback(void* ptr, size_t size, size_t nmemb, std::string* userdata) {
    userdata->append(static_cast<char*>(ptr), size * nmemb);
    return size * nmemb;
}

std::string getBinanceAPIResponse() {
    if (!USE_REAL_API) {
        return R"([{"a":2801252062,"p":"117881.20","q":"0.018","f":6506173943,"l":6506173943,"T":1753608340535,"m":true},{"a":2801252063,"p":"117881.30","q":"0.001","f":6506173944,"l":6506173944,"T":1753608340550,"m":false}])";
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

struct Trade {
    unsigned long long a; // Aggregate tradeId
    double p; // Price
    double q; // Quantity
    unsigned long long f; // First tradeId
    unsigned long long l; // Last tradeId
    unsigned long long T; // Timestamp
    bool m; // Was the buyer the maker?
};

// since the binance api is versioned, i am strict about the format of the response and make all the assumptions possible
std::vector<Trade> parseBinanceResponse(const std::string& response) {
    // if the response only contains "[]" or less, it is considered empty
    if (response.length() <= 2) {
        return {};
    }

    std::vector<Trade> trades;
    size_t position = 6; // start at the value for the first "a" property

    while (true) {
        Trade trade {};

        // parse "a" property
        size_t propertyValueEndsAtIndex = response.find(',', position);
        trade.a = std::stoull(response.substr(position, propertyValueEndsAtIndex - position));

        // parse "p" property
        position = propertyValueEndsAtIndex + 6;
        propertyValueEndsAtIndex = response.find('"', position);
        trade.p = std::stod(response.substr(position, propertyValueEndsAtIndex - position));

        // parse "q" property
        position = propertyValueEndsAtIndex + 7;
        propertyValueEndsAtIndex = response.find('"', position);
        trade.q = std::stod(response.substr(position, propertyValueEndsAtIndex - position));

        // parse "f" property
        position = propertyValueEndsAtIndex + 6;
        propertyValueEndsAtIndex = response.find(',', position);
        trade.f = std::stoull(response.substr(position, propertyValueEndsAtIndex - position));

        // parse "l" property
        position = propertyValueEndsAtIndex + 5;
        propertyValueEndsAtIndex = response.find(',', position);
        trade.l = std::stoull(response.substr(position, propertyValueEndsAtIndex - position));

        // parse "T" property
        position = propertyValueEndsAtIndex + 5;
        propertyValueEndsAtIndex = response.find(',', position);
        trade.T = std::stoull(response.substr(position, propertyValueEndsAtIndex - position));

        // parse "m" property
        position = propertyValueEndsAtIndex + 5;
        trade.m = response[position] == 't';
        propertyValueEndsAtIndex = position + (trade.m ? 4 : 5);

        trades.push_back(trade);

        // is there another trade?
        if (response[propertyValueEndsAtIndex + 1] != ',') {
            break;
        }

        position = propertyValueEndsAtIndex + 7; // move to the value of the next "a" property
    }

    return trades;
}

int main() {
    std::cout << "Getting binance response..." << std::endl;
    auto binanceData = getBinanceAPIResponse();
    std::cout << "Printing response for convenience..." << std::endl;
    std::cout << binanceData << std::endl << std::endl;

    std::cout << "Parsing..." << std::endl;
    auto trades = parseBinanceResponse(binanceData);
    std::cout << std::endl;

    // print as specified in the question
    // i could have done this while parsing, for example to have the original string in the floating point numbers
    // but i considered after parsing to be better as a proof
    std::cout << "Printing parsed data..." << std::endl;
    std::cout << "[" << std::endl;
    for (auto i = 0; i < trades.size(); i++) {
        const auto& trade = trades[i];
        std::cout << "  {" << std::endl;
        std::cout << "    \"a\": " << trade.a << ", // Aggregate tradeId" << std::endl;
        std::cout << "    \"p\": \"" << std::fixed << trade.p << "\", // Price" << std::endl;
        std::cout << "    \"q\": \"" << std::fixed << trade.q << "\", // Quantity" << std::endl;
        std::cout << "    \"f\": " << trade.f << ", // First tradeId" << std::endl;
        std::cout << "    \"l\": " << trade.l << ", // Last tradeId" << std::endl;
        std::cout << "    \"T\": " << trade.T << ", // Timestamp" << std::endl;
        std::cout << "    \"m\": " << (trade.m ? "true" : "false") << " // Was the buyer the maker?" << std::endl;
        std::cout << "  }" << (i < trades.size() - 1 ? "," : "") << std::endl;
    }
    std::cout << "]" << std::endl;

    return 0;
}