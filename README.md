#### embedded-systems
Coursework

Group Name: WillCodeForBeer
Members: Matt, Chris, Becky, Sean

When pulling changes from stash you will find that you will get compile errors. To fix this you need to go into the spec.d file and change the file location to your local. Also if you go into Project>Properties make sure that under C/C++ Build>Environment that any paths are correct (they will be set to Matt's laptop as he created the project so you will need to change them for your own local

### Useful Link
http://willcodeforbeer12345.azurewebsites.net/

### PlatformIO Configuration!

So, i got platformIO working for our project (and the set up is bliss compared to eclipse). So, you will need to add the applicable libraries again, but only 1 needs adding, to do this go to platformio home, libraries, and search for 'DHT esp' then install the dhtespx library, this should be the only set up you need. Hopefully the rest will work automatically. 

You first need to install PlatformIO which will also install VS code for you, once this is done do the above and then you need to go to Terminal > Run Task.. and look for PlatformIO Build, once that has been a success you want Terminal > Run Task.. and look for PlatformIO Upload. To get your serial monitor up you want to run the PlatformIO monitor task. It should just work as the config is set up for it (or should be!)

### Versioning

<table>
  <tr>
    <th>Hardware Version</th>
    <th>Software Version</th>
    <th>Schematics file name</th>
  </tr>
  <tr>
    <td>1</td>
    <td>Task A</td>
    <td>taskA_schematics.pdf</td>
  </tr>
  <tr>
    <td>2</td>
    <td>v1.0</td>
    <td>example</td>
  </tr>
   <tr>
    <td>3</td>
    <td>v2.0</td>
    <td>example</td>
  </tr>
   <tr>
    <td>4</td>
    <td>v3.0</td>
    <td>example</td>
  </tr>
</table>
