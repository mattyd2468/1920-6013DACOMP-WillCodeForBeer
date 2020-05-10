#### embedded-systems
Coursework

Group Name: WillCodeForBeer
Members: Matt, Chris, Becky, Sean

### Useful Links
http://willcodeforbeer12345.azurewebsites.net/ -- this is the link to the web server

https://github.com/mattyd2468/1920-6013DACOMP-WillCodeForBeer -- this is the link to the project repo

#### Tutorial links
https://www.instructables.com/id/How-to-use-a-Push-Button-Arduino-Tutorial/ --this is task G snooze button info

### PlatformIO Configuration!

You first need to install PlatformIO which will also install VS code for you, once this is done do the above and then you need to go to Terminal > Run Task.. and look for PlatformIO Build, once that has been a success you want Terminal > Run Task.. and look for PlatformIO Upload. To get your serial monitor up you want to run the PlatformIO monitor task. It should just work as the config is set up for it (or should be!)

To connect to your hotspot you will need to change the value of the variables called SSID and PASS. These can be found in the file Connect_WiFi.h

To run the unit tests you must make sure only 1 of the _test files is uncommented as it only allows for 1 setup and loop method, uncomment the file you want to run and then save the files, then go to Terminal > Run Task > PlatformIO:Test - if no logging shows then urn the monitor task as it might run in there. The regression suite file contains all unit tests for the project

#### Libraries Needed
Aunit

Adafruit GFX Library

DHT sensor library for ESPx

DHT sensor library

ESP8266_SSD1306

HTTPClientESP32Ex

Time

Vector

### Versioning

<table>
  <tr>
    <th>Hardware Version</th>
    <th>Software Version</th>
    <th>Schematics file name</th>
    <th>Tasks Included</th>
  </tr>
  <tr>
    <td>1</td>
    <td>v1.0</td>
    <td>v1.0</td>
    <td>A, B, D</td>
  </tr>
  <tr>
    <td>2</td>
    <td>v2.0</td>
    <td>v2.0</td>
    <td>C, G, H</td>
  </tr>
   <tr>
    <td>3</td>
    <td>v3.0</td>
    <td>v3.0</td>
    <td>E, F, I</td>
  </tr>
</table>
