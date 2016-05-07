
// Our own version of 'send' which is otherwise in the ESP8266WebServer library. Much inproved without
//   the performance issue in the stock library. We may be able to get rid of this some time in the
//   future if the library's version of send is fixed.
void sendMime (String mimeType, String message) {
  WiFiClient client = server.client();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: " + mimeType);
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Content-Length: " + String(message.length()));
  client.println("");
  client.print(message);
  //  delay(1); // Give the web browser time to receive the data.
  client.stop();
}

// Our own version of 'send' which is otherwise in the ESP8266WebServer library. Much inproved without
//   the performance issue in the stock library. We may be able to get rid of this some time in the
//   future if the library's version of send is fixed.
void send(String message) {
  WiFiClient client = server.client();

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");  // the connection will be closed after completion of the response
  client.println("Content-Length: " + String(message.length()));
  client.println("");
  client.print(message);
  //  delay(1); // Give the web browser time to receive the data.
  client.stop();
}




