#include <iostream>
#include<fstream>
#include <string>
#include "curl/curl.h" //load_path

using namespace std;

static char errorBuffer[CURL_ERROR_SIZE];
static string buffer;
static int writer(char *data, size_t size, size_t nmemb,string *buffer){
  int result = 0;

  if (buffer != NULL) {
    buffer->append(data, size * nmemb); //番地がメソッド的なものを使うときは -> を使う
    result = size * nmemb;
  }
  return result;
}

int usage() {
  cout << "curlsample: \n" << endl;
  cout << "\tUsage: curlsample url\n" <<endl;
}

int main(int argc, char **argv) {
  if (argc > 1){
    string url(argv[1]);

    cout << "Retrieving " << url << endl;

    CURL *curl;
    CURLcode result;

    curl = curl_easy_init();

    if (curl) {
      curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorBuffer);
      curl_easy_setopt(curl, CURLOPT_URL, argv[1]);
      curl_easy_setopt(curl, CURLOPT_HEADER, 0);
      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer);
      curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

      result = curl_easy_perform(curl);

      curl_easy_cleanup(curl);

      if (result == CURLE_OK){
        //cout << buffer << "\n";
        basic_ofstream<char> ofs(argv[1]);
        ofs << buffer << endl; // ファイルに出力する
      } else {
        cout << "Error: [" << result << "] - " << errorBuffer << endl;
        exit(-1);
      }
    }
  } else {
    usage();
  }
  return 0;
}
