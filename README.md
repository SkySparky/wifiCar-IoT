# WiFi-Bot #

Конструктор WiFi-Bot предназначена для использования на различных подвижных платформ, с возможностью беспроводного подключения к сети Internet сети через 
локальные точки достпупа WiFi (AP) и/или выполнять роль AP. В основе конструктора используется модуль с радиоинтерфесом WiFi, построенный на микропроцессоре ESP8266 компании [Espressif](https://espressif.com). 

Разработку программного обеспечения для платы удобно осваивать среде Arduino IDE, а при использовании [Platform.io](http://platform.io) и во многих других средах с использованием большого количества разнообразных библиотек (в т.ч. и Arduino). По мимо этого компания Espressif предоставляет наборы стандартных библиотек, а так же существуют сторонние разработки такие как [Sming SDK](https://github.com/SmingHub/Sming). 

Примеры программ для WiFi-Bot представленные здесь разработаны либо в Arduino IDE, либо в среде Eclipse при использовании библиотеки SmingRTOS.

# Основные характеристики #

* Процессор: ESP8266; 
* Объем ПЗУ: 8Мбит (раздел для хранения кода программ) и 32Мбит (раздел для файловой системы SPIFFS);
* Объем ОЗУ;
* Максимальный суммарный ток потребления 
* Максимальное входное напряжение;
* Максимальный выходной ток моторов;
* Максимальный выходной ток встроенных стабилизаторов (3.3В и 5В);
* Максимальная скорость передачи данных через USB-UART мост: 2Мбит/с
* Максимальная скорость передачи данных через UART: 5Мбит/с
* Максимальная скорость передачи данных через интерфейс WiFi: 56Мбит/с 

[Электрическая схема](https://bitbucket.org/lartiot/wifi-bot-code/downloads/wifi-car-schematic.pdf)

[Внешний вид платы и назначение разъемов, индикаторов и перемычек](https://bitbucket.org/repo/pkapBE/images/2795471447-2016-05-27_22-01-25.png)

[Подробное описание](https://bitbucket.org/lartiot/wifi-bot-code/wiki/Home)

[Начало работы с WiFi-Bot]()

[Различные варианты применения WiFi-Bot]()