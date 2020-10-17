## Usage

* make a copy of `connection.example.h` and name it `connection.h`
* open the project in Arduino and edit `connection.h`
  - in place of `"wifi network name"` and `"wifi network password"` put
  the relevant wifi credentials for the space you are in
  - change `websockets_server_host` to match the IP address or URL of
    the Spacebrew server you are targetting
  - `websocket_server_port` is set to the default Spacebrew port number,
    so in most instances you won't need to change this number
* Upload to your microcontroller
* Open the [web-chat][wc] example for testing
  - you may need to change the server address/IP after `server=` in the
    web browser address bar
* Using the [Spacebrew admin][wa], connect the web-chat and "duino"
  clients
  - you may need to change the server address/IP after `server=` in the
    web browser address bar
* Send a message from the web-chat. You should see it pop up twice (once
  for "me" and once for "them")
* Optional: open the Arduino serial monitor, set the baud rate to 115200
  and send messages from the web-chat client, you should see the JSON
  and extracted message logged in the serial monitor.

[wa]: http://spacebrew.github.io/spacebrew/admin/admin.html?server=localhost
[wc]: http://www.quinkennedy.com/spacebrew-stuff/web-chat/index.html?server=localhost
