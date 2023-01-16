// Role do webserver
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>

using namespace std;

bool isPressed = "";
int nivel = 0;

const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
    <style>
        /* TITULO */

        #tudo {
            padding-top: 3%;
            padding-left: 5%;
            padding-bottom: 10%;
            padding-right: 5%;
            font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
        }

        #header {
            border-width: 5px;
            border-style: solid;
            border-color: #523312;
            border-radius: 35px;
            padding: 20px;
            background-color: #86EB97;
            display: flex;
            justify-content: space-evenly;
        }

        #titulo {
            font-size: 37px;
        }

        img {
            height: 180;
            width: 205;
        }

        /*

==============================================================================================================================================

INTERAÇÕES
*/


        #CxInterações {
            padding-top: 3%;
            padding-left: 5%;
            padding-bottom: 10%;
            padding-right: 5%;
            font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
            display: flex;
            justify-content: space-around;
        }

        #CaixaDagua {
            border-width: 5px;
            border-style: solid;
            border-color: #523312;
            border-radius: 35px;
            padding: 20px;
            background-color: #86EB97;
            display: grid;
        }

        #Email {
            border-width: 5px;
            border-style: solid;
            border-color: #523312;
            border-radius: 35px;
            padding: 20px;
            background-color: #86EB97;
            display: grid;
            text-align: center;
        }

        #TXTcaixa {
            text-align: center;
        }

        #Rodape {
            background-color: #383838;
        }

        #TXTrodape {
            padding-top: 3%;
            padding-left: 5%;
            padding-bottom: 3%;
            padding-right: 5%;
            color: rgb(165, 165, 165);
            text-align: center;
        }

        #TituloCX {
            font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
            text-align: center;
        }
    </style>
    <link rel="stylesheet" href="styles.css">
    <title>IF Resources</title>
    <meta charset="utf-8">
    <link rel="shortcut icon" href="https://upload.wikimedia.org/wikipedia/commons/5/54/Instituto_Federal_Marca_2015.svg">
</head>

<body>
    <div>
        <div id="tudo">
            <div id="header">
                <div id="titulo">
                    <h1>
                        IF Resources
                    </h1>
                </div>
                <div id="IF">
                    <br />
                    <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/bd/Instituto_Federal_do_Rio_de_Janeiro_-_Marca_Vertical_2015.svg/200px-Instituto_Federal_do_Rio_de_Janeiro_-_Marca_Vertical_2015.svg.png">
                </div>
            </div>
        </div>
        <div id="CxInterações">
            <div id="CaixaDagua">
                <div id="TXTcaixa">
                    <h1>
                        Veja o nível da
                        <br />
                        Caixa D'água
                    </h1>
                    <a href="/caixa">
                        <img src="https://www.uberlandia.mg.gov.br/wp-content/uploads/2020/11/1_Prancheta-1-150x150.png">
                    </a>
                </div>
            </div>
            <div>
                <div id="Email">
                    <h1>
                        Envie-nos
                        <br />
                        um E-mail
                    </h1>
                    <a href="https://form.jotform.com/223453415694661">
                        <img src="https://www.pngmart.com/files/15/Email-Symbol-PNG-Transparent-Picture.png" alt="Image" height="150" width="150">
                    </a>
                </div>
            </div>
        </div>
        <div id="Rodape">
            <div id="TXTrodape">
                <h1>
                    Thomas o trem LTDA.
                </h1>
                <h3>
                    Gabriel Sales </br> Michael Monteiro de Lima </br></br>2020.1 / 2023.1 (se Deus quiser)
                </h3>
            </div>
        </div>
    </div>
</body>

</html>
)=====";

const char CAIXA_page[] PROGMEM = R"=====(
<html>

<head>
    <style>
        #tudo {
            padding-top: 3%;
            padding-left: 5%;
            padding-bottom: 10%;
            padding-right: 5%;
            font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
        }

        #header {
            border-width: 5px;
            border-style: solid;
            border-color: #523312;
            border-radius: 35px;
            padding: 20px;
            background-color: #86EB97;
            display: flex;
            justify-content: space-evenly;
        }

        #titulo {
            font-size: 37px;
        }

        #TituloCX {
            font-family: 'Lucida Sans', 'Lucida Sans Regular', 'Lucida Grande', 'Lucida Sans Unicode', Geneva, Verdana, sans-serif;
            text-align: center;
        }
    </style>
    <link rel="stylesheet" href="styles.css">
    <meta charset="utf-8">
    <title>Caixa D'agua</title>
    <link rel="shortcut icon" href="https://upload.wikimedia.org/wikipedia/commons/5/54/Instituto_Federal_Marca_2015.svg">
</head>

<body>
    <div>
        <div id="tudo">
            <div id="header">
                <div id="titulo">
                    <h1>
                        IF Resources
                    </h1>
                </div>
                <div id="IF">
                    <br />
                    <img
                        src="https://upload.wikimedia.org/wikipedia/commons/thumb/b/bd/Instituto_Federal_do_Rio_de_Janeiro_-_Marca_Vertical_2015.svg/200px-Instituto_Federal_do_Rio_de_Janeiro_-_Marca_Vertical_2015.svg.png">
                    <br />
                </div>
            </div>
        </div>
        <div id="TituloCX">
            <h1>
                O nível da caixa d'água é: WATER_STATUS
            </h1>
        </div>

    </div>
</body>

</html>
)=====";
//---------------------------------------------------------------

// SSID and Password of your WiFi router
const char *ssid = "Familia SRM";
const char *password = "srm011633";
int buttonState = 0;

// Declare a global object variable from the ESP8266WebServer class.
WebServer server(80);

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot()
{
    Serial.println("You called root page");
    server.send(200, "text/html", MAIN_page);
}

void handleCaixa()
{
    pinMode(2, INPUT);
    pinMode(4, INPUT);
    pinMode(5, INPUT);

    if (digitalRead(2) == 1)
    {
        nivel = 3;
    }

    else if (digitalRead(4) == 1)
    {
        nivel = 2;
    }

    else if (digitalRead(5) == 1)
    {
        nivel = 1;
    }
    else
    {
        nivel = 0;
    }

    Serial.println("You called caixa page");

    Serial.println(nivel);

    // Codigo que substitui dentro da string CAIXA_page a palavra chave WATER_STATUS pelo conteúdo desejado
    String html = CAIXA_page;
    html.replace("WATER_STATUS", (String)nivel);


    server.send(200, "text/html", html);
}


//==============================================================
//                   SETUP
//==============================================================
void setup(void)
{
    Serial.begin(115200);

    WiFi.begin(ssid, password); // Connect to your WiFi router
    Serial.println("");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }

    // If connection successful show IP address in serial monitor
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); // IP address assigned to your ESP

    server.on("/", handleRoot); // Which routine to handle at root location. This is display page
    server.on("/caixa", handleCaixa);

    server.begin(); // Start server
    Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================

void loop(void)
{
    server.handleClient();
    delay(2); // allow the cpu to switch to other tasks

}
