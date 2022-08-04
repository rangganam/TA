void realtime () {

  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "ranggana/dashboard/value?volta=";
    url += busvoltageA;
    url += "&currenta=";
    url += current_mAA;
    url += "&powera=";
    url += power_mWA;
    url += "&voltb=";
    url += busvoltageB;
    url += "&currentb=";
    url += current_mAB;
    url += "&powerb=";
    url += power_mWB;
    url += "&battavolt=";
    url += busvoltageC;
    url += "&battapercentage=";
    url += batAPercentage;
    url += "&battbvolt=";
    url += busvoltageD;
    url += "&battbpercentage=";
    url += batBPercentage;
    url += "&charging=";
    url += charging;
    url += "&acvolt=";
    url += voltage;
    url += "&accurrent=";
    url += current;
    url += "&acpower=";
    url += power;
    url += "&description=";
    url += frequency;
    url += "&acpf=";
    url += pf;
    url += "&acenergy=";
    url += energy;
    Serial.println(url);

    String serverPath = serverName + url;
    Serial.println(serverPath);

    // Your Domain name with URL path or IP address with path
    http.begin(serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}

void history() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "ranggana/history/value?volta=";
    url += busvoltageA;
    url += "&currenta=";
    url += current_mAA;
    url += "&powera=";
    url += power_mWA;
    url += "&voltb=";
    url += busvoltageB;
    url += "&currentb=";
    url += current_mAB;
    url += "&powerb=";
    url += power_mWB;
    url += "&battavolt=";
    url += busvoltageC;
    url += "&battapercentage=";
    url += batAPercentage;
    url += "&battbvolt=";
    url += busvoltageD;
    url += "&battbpercentage=";
    url += batBPercentage;
    url += "&charging=";
    url += charging;
    url += "&acvolt=";
    url += voltage;
    url += "&accurrent=";
    url += current;
    url += "&acpower=";
    url += power;
    url += "&description=";
    url += frequency;
    url += "&acpf=";
    url += pf;
    url += "&acenergy=";
    url += energy;
    Serial.println(url);

    String serverPath = serverName + url;
    Serial.println(serverPath);

    // Your Domain name with URL path or IP address with path
    http.begin(serverPath.c_str());

    // Send HTTP GET request
    int httpResponseCode = http.GET();

    if (httpResponseCode > 0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      String payload = http.getString();
      Serial.println(payload);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
}
