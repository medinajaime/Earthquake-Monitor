//
// Created by Jaime on 6/20/2024.
//

#ifndef EARTHQUAKE_EARTHQUAKEFETCHER_H
#define EARTHQUAKE_EARTHQUAKEFETCHER_H


#include <string>
#include <curl/curl.h>

class EarthquakeFetcher {
public:
    EarthquakeFetcher(const std::string& apiKey)
            : apiKey(apiKey), currentIndex(0) {}

    std::string fetch() {
        const std::vector<std::string> urls = {
                "https://opendata.cwa.gov.tw/api/v1/rest/datastore/E-A0015-001?Authorization=" + apiKey,
                "https://opendata.cwa.gov.tw/api/v1/rest/datastore/E-A0016-001?Authorization=" + apiKey
        };

        CURL* curl;
        CURLcode res;
        std::string readBuffer;

        curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, urls[currentIndex].c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
            res = curl_easy_perform(curl);

            if (res != CURLE_OK) {
                throw std::runtime_error("curl_easy_perform() failed: " + std::string(curl_easy_strerror(res)));
            }

            curl_easy_cleanup(curl);

            currentIndex = (currentIndex + 1) % urls.size();
        }

        return readBuffer;
    }

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string apiKey;
    int currentIndex;
};


#endif //EARTHQUAKE_EARTHQUAKEFETCHER_H
