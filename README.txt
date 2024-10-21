L'OBJECTIF :

l'objectif de ce projet était de surveiller et de contrôler un stock de médicaments afin de respecter quelques normes ISO 13485 et les bonnes pratiques IDMP.
Pour ce faire, nous avons dans un premier lieu visualisé les mesures des capteurs d’humidité et de température sur la Plate-forme ThingSpeak, puisque ces derniers paramètres sont indispensables pour assurer la qualité de médicament. 
Par la suite, on exploite le modèle RFID afin de lutter contre la contrefaçon et éviter l'expiration de la date de validité de médicamet.


Montage de simulation 1:
On a fait  ce montage électronique sur une plaque d'essai (breadboard). On branche la carte ESP32 dans la plaque d'essai. 
Puis, on ajoute un capteur de température et d'humidité DHT11, également connecté à la plaque d'essai.
On a utilisé plusieurs fils de connexion pour relier les composants :
- Un fil rouge connecte la broche VCC du capteur DHT11 au rail d'alimentation de 3,3V.
- Un fil noir connecte la broche GND du capteur DHT11 au rail de masse.
- Un fil jaune connecte la broche de données du capteur DHT11 à l'une des broches GPIO du module ESP8266.
Les mesures sont ensuite envoyées au platforme thingSpeak via protocole MQTT.


Montage de simulation 2:
Le matériel nécessaire pour  le montage RFID est le suivant :
-Arduino mega.
-Rfid reader et tags.
-Module RTC.
-Fils et breadboard.