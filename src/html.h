#ifndef HTML_CODE
    #define HTML_CODE
    

const char page[] PROGMEM = R"rawliteral(
<!DOCTYPE html><html>
<head><meta name="viewport" content="width=device-width, initial-scale=1"><link rel="icon" href="data:,">
<style>
html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;} form { display: inline-block; //Or display: inline; }
.btn{background-color:#f4511e;border:none;color:white;padding:16px32px;text-align:center;font-size:16px;margin:4px2px;opacity:0.6;transition:0.3s;display:inline-block;text-decoration:none;cursor:pointer;}.btn:hover {opacity: 1}
.inputCentered { text-align: center; }
</style>
<h1>Food dispenser</h1></head><body>
<center><h2>Wifi Configuration</h2></center>
<form action="/get">
<input type="text" id="ssidInput" name="ssidInput" placeholder="SSID" required minlength="4" maxlength="50" size="50"></br>
<input type="password" id="pass" name="pass" placeholder="Password" required minlength="4" maxlength="50" size="50">
<p><button class="btn" type="submit" value="Submit">Change WiFi</button></a>
</form>
</br><center><h2>Date configuration</h2></center>
<form action="/get">
<center>Insert hour</center>
<input class="inputCentered" type="text" id="hora_min" name="hora_min" placeholder="HH:mm" required minlength="5" maxlength="5" size="6"></br>
</br><center>Insert day</center>
<input class="inputCentered" type="text" id="dia" name="dia"  placeholder="Elige: 'L','M','X','J','V','S','D','T'" required minlength="1" maxlength="1" size="20"></br>
</br><center>Insert weight(g)</center>
<input class="inputCentered" type="text" id="peso" name="peso" required minlength="1" maxlength="2" size="4"></br>
<p><button class="btn" type="submit" value="Submit">Save</button></a></p>
</form>
</body></html>)rawliteral";

#endif