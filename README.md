# Плата WiFi-Bot #

Плата предназначена для конструирования различных подвижных платформ, с возможностью беспроводного подключения к локальной и глобальной (Internet) сети через 
локальные точки достпупа WiFi (AP) или выполнять роль AP. Программирование платы осуществляется в среде Arduino IDE. На плате установлена Flash-память объемом
4Мб, из которых 1Мб выделяется для программы и 3Мб для файловой системы, предназначенной для сохранения настроект, файлов HTTP-сервера и т.п.

![Электрическая схема.](https://bitbucket.org/lartiot/wifi-bot-code/downloads/wifi-car-schematic.pdf)

### Подключение ###

![WiFi-Bot-View.png](https://bitbucket.org/repo/pkapBE/images/2052293262-WiFi-Bot-View.png)

### Начало работы ###

Откройте ino-файл в среде Arduino IDE и выполните действия, отмеченные  описанные в начале файла 


```
#!c++

// 
// TODO!!!:
// http://arduino.esp8266.com/stable/package_esp8266com_index.json         - add to board manager
// https://github.com/Links2004/arduinoWebSockets/blob/master/library.json - add to library wifisocket
// https://github.com/esp8266/arduino-esp8266fs-plugin                     - Read for upload filesystem with WEB-interface
// 

```

```
#!c++

// TODO!!!!:
// Input name and password for you AP
const char* ssid     = "********";
const char* password = "********";
```

![2016-05-13_04-31-33.png](https://bitbucket.org/repo/pkapBE/images/2119624233-2016-05-13_04-31-33.png)