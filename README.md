## Knop IoT
### IoT Button interface

#### Setup
##### API
Deploy API to a web server on port 3005. I'm using an EC2 t2.micro instance to save on cost. There is a dockerfile in the `api/` directory that should help with this.
I also ensured the security group for the EC2 instance is set to only permit connections to port 3005 from the IP address where the ESP8266 device will run. In this case it's my home network.

##### ESP8266
1. In /esp8266/main, create a `config.h` file to define the sensitive data to be written to the ESP8266 chip:
```
const char* ssid     = "your wifi network name";
const char* password = "your wifi network password";
const char* device_id = ""; // a unique device id sent in the query string of the API request
const char* url = "http://0.0.0.0"; // the url of the API endpoint
```
_Hopefully it is obvious why this information is not in the `main.ino` file._

2. Upload the arduino code to the ESP8266 device.